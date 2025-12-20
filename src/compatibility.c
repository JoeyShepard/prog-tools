#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "compatibility.h"
#include "macros.h"
#include "sdl2-keys.h"

//TODO: remove here and everywhere if not using
//Common to cg50 and PC
volatile bool *on_key_executing;
volatile bool *on_key_pressed;

#ifdef CG50
//cg50 specific
//=============

    #include <gint/clock.h>
    #include <gint/drivers/keydev.h>
    #include <gint/fs.h>
    #include <gint/gint.h>
    #include <gint/timer.h>

    #include "exceptions.h"


    //2MB of unused space in RAM for heap
    uint8_t *heap=(uint8_t *)0x8c200000;
    uint8_t *xram=(uint8_t *)0xe5007000;
    uint8_t *yram=(uint8_t *)0xe5017000;

    volatile int tick_flag;

    //Called by timer every TICK_MS
    static int timer_callback(volatile int *tick)
    {
        *tick=1;
        return TIMER_CONTINUE;
    }

    static bool on_key_filter(key_event_t event)
    {
        if (event.key==KEY_ACON)
        {
            if (event.type==KEYEV_DOWN)
            {     
                //ON key was pressed - halt interpreter if one is running
                if (on_key_executing!=NULL)
                {
                    *on_key_executing=false;
                    
                    //Also, set flag to tell interpreter ON key was source of halt
                    if (on_key_pressed!=NULL) *on_key_pressed=true;
                }
            }
            return false;
        }

        return true;
    }

    //On CG50, initialize timer and catch unaligned memory accesses
    void setup(int delay_ms)
    {
        //TODO: reenable? added at first but now it may be hiding errors
        //if not enabled, gint has own handler showing address

        //Exception handling for unaligned memory accesses
        //setup_exception_handling();

        //Menu functionality so add-in doesn't crash if calculator left off for too long
        gint_setrestart(1);

        //Interrupt sets target of this pointer to false when ON is pressed to halt interpreter if one is running
        on_key_executing=NULL;

        //Filter for keys to catch ON and halt interpreter if one is running
        keydev_set_async_filter(keydev_std(),on_key_filter);

        //Initialize timer for limiting FPS
        tick_flag=1;
        int t=timer_configure(TIMER_ANY, delay_ms*1000, GINT_CALL(timer_callback,&tick_flag));
        if (t>=0) timer_start(t);

        //Initialize timer for measuring performance
        prof_init();
    }
    
    void delay()
    {
        while (!tick_flag) sleep();
        tick_flag=0;
    }

    void wrapper_exit(UNUSED(int code))
    {
        //Empty function for compatibility
    }

    void wrapper_screenshot()
    {
        //Empty function for compatibility
    }

    int wrapper_pc_key()
    {
        //Empty function for compatibility
        return 0;
    }

    int wrapper_remap_key(UNUSED(int modifier),UNUSED(int key),UNUSED(struct KeyRemap *key_list))
    {
        //No keys to remap on calculator
        return 0;
    }

    char *wrapper_normalize_path(const char *path,UNUSED(int local_path_max))
    {
        return fs_path_normalize(path);
    }

    void wrapper_perf_start(prof_t *time)
    {
        *time=prof_make();
        //prof_enter is macro that assumes time is not pointer so use macro body here
        time->elapsed+=*prof_tcnt;
    }

    uint32_t wrapper_perf_stop(prof_t *time)
    {
        time->elapsed-=*prof_tcnt;
        return prof_time(*time);
    }

#else

//PC specific
//===========

    #include <arpa/inet.h>
    #include <linux/limits.h>
    #include <netinet/in.h>
    #include <poll.h>
    #include <string.h>
    #include <sys/mman.h>
    #include <sys/socket.h>
    #include <unistd.h>

    #include "key-remap-pc.h"
    #include "sdl2-keys.h"

    //Globals
    //=======
    //Calculator
    uint16_t screen[DHEIGHT*DWIDTH];
    uint8_t *heap;
    uint8_t *xram;
    uint8_t *yram;
    uint8_t *xram_base;
    uint8_t *yram_base;
    int global_delay_ms;
    #define KEYS_SIZE 10000
    int keys[KEYS_SIZE];
    int pc_keys[KEYS_SIZE];
    int pc_scancode;
    int keys_start=0,keys_end=0;
    int sockfd;
    bool frame_ready;

    //Static functions only in PC version
    //===================================
    static int wrapper_convert_key(int key)
    {
        //Converts PC keys to calculator keys in a straightforward way since many don't require special treatment.
        //For program specific key remapping of keys on calculator independent of PC, see key-remap.c
        const int key_table[]=
        {
            SDL_SCANCODE_A,             KEY_XOT,
            SDL_SCANCODE_B,             KEY_LOG,
            SDL_SCANCODE_C,             KEY_LN,
            SDL_SCANCODE_D,             KEY_SIN,
            SDL_SCANCODE_E,             KEY_COS,
            SDL_SCANCODE_F,             KEY_TAN,
            SDL_SCANCODE_G,             KEY_FRAC,
            SDL_SCANCODE_H,             KEY_FD,
            SDL_SCANCODE_I,             KEY_LEFTP,
            SDL_SCANCODE_J,             KEY_RIGHTP,
            SDL_SCANCODE_K,             KEY_COMMA,
            SDL_SCANCODE_L,             KEY_ARROW,
            SDL_SCANCODE_M,             KEY_7,
            SDL_SCANCODE_N,             KEY_8,
            SDL_SCANCODE_O,             KEY_9,
            SDL_SCANCODE_P,             KEY_4,
            SDL_SCANCODE_Q,             KEY_5,
            SDL_SCANCODE_R,             KEY_6,
            SDL_SCANCODE_S,             KEY_MUL,
            SDL_SCANCODE_T,             KEY_DIV,
            SDL_SCANCODE_U,             KEY_1,
            SDL_SCANCODE_V,             KEY_2,
            SDL_SCANCODE_W,             KEY_3,
            SDL_SCANCODE_X,             KEY_ADD,
            SDL_SCANCODE_Y,             KEY_SUB,
            SDL_SCANCODE_Z,             KEY_0,

            SDL_SCANCODE_1,             KEY_1,
            SDL_SCANCODE_2,             KEY_2,
            SDL_SCANCODE_3,             KEY_3,
            SDL_SCANCODE_4,             KEY_4,
            SDL_SCANCODE_5,             KEY_5,
            SDL_SCANCODE_6,             KEY_6,
            SDL_SCANCODE_7,             KEY_7,
            SDL_SCANCODE_8,             KEY_8,
            SDL_SCANCODE_9,             KEY_9,
            SDL_SCANCODE_0,             KEY_0,

            SDL_SCANCODE_RETURN,        KEY_EXE,
            SDL_SCANCODE_ESCAPE,        KEY_EXIT,
            SDL_SCANCODE_BACKSPACE,     KEY_DEL,
            SDL_SCANCODE_TAB,           0,
            SDL_SCANCODE_SPACE,         KEY_DOT,

            SDL_SCANCODE_MINUS,         KEY_SUB,
            SDL_SCANCODE_EQUALS,        KEY_DOT,
            SDL_SCANCODE_LEFTBRACKET,   KEY_ADD,
            SDL_SCANCODE_RIGHTBRACKET,  KEY_SUB,
            SDL_SCANCODE_BACKSLASH,     0,

            SDL_SCANCODE_SEMICOLON,     0,
            SDL_SCANCODE_APOSTROPHE,    KEY_EXP,
            SDL_SCANCODE_GRAVE,         0,      //tilde and back tick
            SDL_SCANCODE_COMMA,         KEY_COMMA,
            SDL_SCANCODE_PERIOD,        KEY_DOT,
            SDL_SCANCODE_SLASH,         KEY_DIV,

            SDL_SCANCODE_CAPSLOCK,      KEY_ALPHA,

            SDL_SCANCODE_F1,            KEY_F1,
            SDL_SCANCODE_F2,            KEY_F2,
            SDL_SCANCODE_F3,            KEY_F3,
            SDL_SCANCODE_F4,            KEY_F4,
            SDL_SCANCODE_F5,            KEY_F5,
            SDL_SCANCODE_F6,            KEY_F6,
            SDL_SCANCODE_F7,            0,
            SDL_SCANCODE_F8,            0,
            SDL_SCANCODE_F9,            0,
            SDL_SCANCODE_F10,           0,
            SDL_SCANCODE_F11,           0,
            SDL_SCANCODE_F12,           0,
            SDL_SCANCODE_HOME,          0,
            SDL_SCANCODE_PAGEUP,        0,
            SDL_SCANCODE_DELETE,        KEY_DEL,
            SDL_SCANCODE_END,           0,
            SDL_SCANCODE_PAGEDOWN,      0,
            SDL_SCANCODE_RIGHT,         KEY_RIGHT,
            SDL_SCANCODE_LEFT,          KEY_LEFT,
            SDL_SCANCODE_DOWN,          KEY_DOWN,
            SDL_SCANCODE_UP,            KEY_UP,
            SDL_SCANCODE_KP_DIVIDE,     KEY_DIV,
            SDL_SCANCODE_KP_MULTIPLY,   KEY_MUL,
            SDL_SCANCODE_KP_MINUS,      KEY_SUB,
            SDL_SCANCODE_KP_PLUS,       KEY_ADD,
            SDL_SCANCODE_KP_ENTER,      KEY_EXE,
            SDL_SCANCODE_KP_1,          KEY_1,
            SDL_SCANCODE_KP_2,          KEY_2,
            SDL_SCANCODE_KP_3,          KEY_3,
            SDL_SCANCODE_KP_4,          KEY_4,
            SDL_SCANCODE_KP_5,          KEY_5,
            SDL_SCANCODE_KP_6,          KEY_6,
            SDL_SCANCODE_KP_7,          KEY_7,
            SDL_SCANCODE_KP_8,          KEY_8,
            SDL_SCANCODE_KP_9,          KEY_9,
            SDL_SCANCODE_KP_0,          KEY_0,
            SDL_SCANCODE_KP_PERIOD,     KEY_DOT,

            SDL_SCANCODE_LSHIFT,        KEY_SHIFT,
            SDL_SCANCODE_RSHIFT,        KEY_SHIFT, 

            0,0
        };

        int key_index=0;
        while (key_table[key_index])
        {
            if (key_table[key_index]==key) return key_table[key_index+1];
            key_index+=2;
        }
        return 0;
    }

    static int write_full(int fd,void *data,int size)
    {
        int bytes_sent=0;
        while(size-bytes_sent>0)
        {
            int bytes_written=write(fd,data+bytes_sent,size-bytes_sent);
            if (bytes_written<0) return -1;
            bytes_sent+=bytes_written;
        }
        return size;
    }

    static int read_full(int fd,void *data,int size)
    {
        int bytes_received=0;
        while(size-bytes_received>0)
        {
            int bytes_read=read(fd,data+bytes_received,size-bytes_received);
            if (bytes_read<=0) return bytes_read;
            bytes_received+=bytes_read;
        }
        return size;
    }

    static void wrapper_events()
    {
        //Check TCP for messages
        struct pollfd poll_client;
        poll_client.fd=sockfd;
        poll_client.events=POLLIN;
        int event_count=poll(&poll_client,1,0);
        if (event_count==0)
        {
            //No data from TCP
        }
        else
        {
            if (poll_client.revents&POLLHUP)
            {
                printf("Server disconnected by hang up\n");
                wrapper_exit(EXIT_FAILURE);
            }
            else if (poll_client.revents&POLLIN)
            {
                //Data received from server
                bool first_message=true;
                int messages_left=1;
                int tcp_type;
                uint32_t message;
                while (messages_left>0)
                {
                    int bytes_read=read_full(sockfd,&message,sizeof(message));
                    if (bytes_read==0)
                    {
                        //No error available - just disconnection
                        printf("Server disconnected\n");
                        wrapper_exit(EXIT_FAILURE);
                    }
                    else if (bytes_read<0)
                    {
                        //Error - print error message for errno
                        perror("Server disconnected");
                        wrapper_exit(EXIT_FAILURE);
                        break;
                    }
                    else
                    {
                        message=ntohl(message); 
                        if (first_message==true)
                        {
                            tcp_type=message;
                            switch (tcp_type)
                            {
                                case TCP_FRAME_READY:
                                    frame_ready=true;
                                    break;
                                case TCP_KEYPRESS:
                                    messages_left++;
                                    break;
                                default:
                                    printf("Unknown TCP message type: 0x%X\n",message);    
                                    wrapper_exit(EXIT_FAILURE);
                            }
                            first_message=false;
                        }
                        else
                        {
                            switch (tcp_type)
                            {
                                case TCP_KEYPRESS:
                                    int32_t key=message;
                                    keys[keys_end]=wrapper_convert_key(key);
                                    pc_keys[keys_end]=key;
                                    keys_end=(keys_end+1)%KEYS_SIZE;
                                    break;
                                default:
                                    //Should never reach here unless error in messages_left calculation above
                                    printf("Unexpected data from server 0x%X for message type 0x%X\n",message,tcp_type);
                                    wrapper_exit(EXIT_FAILURE);
                            }
                        }
                    }
                    messages_left--;
                }
            }
        }
    }

    static int remap_key_helper(int modifier,int key,struct KeyRemap *conversions)
    {
        if (conversions==NULL)
        {
            //No list of key conversions to apply
            return 0;
        }

        while (1)
        {
            if ((conversions->key==0)&&(conversions->modifier==0))
            {
                //End of list - no conversion found
                return 0;
            }
            else if ((conversions->key==key)&&(conversions->modifier==modifier))
            {
                //Key conversion found
                return conversions->new_key;
            }
            conversions++;
        }
    }


    //Functions with separate copies for cg50 and PC
    //==============================================
    //On PC, set up TCP connection to SDL2 server
    void setup(int delay_ms)
    {
        //Set pointers to NULL/MAP_FAILED since may be freed by wrapper_exit
        heap=MAP_FAILED;
        xram_base=NULL;
        yram_base=NULL;

        //Set socket file descriptor to error so wrapper_exit doesn't close until assigned
        sockfd=-1;

        //Ready to send frame of screen. Set to false after transmission then back to true when client signals ready
        frame_ready=true;

        //Allocate 2MB heap to use like 2MB RAM on calculator and make it executable
        heap=mmap(NULL,HEAP_SIZE,PROT_EXEC|PROT_WRITE|PROT_READ,MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
        if (heap==MAP_FAILED)
        {
            printf("Error: failed to allocate memory for calculator heap.\n");
            wrapper_exit(EXIT_FAILURE);
        }

        //Allocate 8K for XRAM memory on calculator plus padding so 8K can be aligned
        xram_base=malloc(XRAM_SIZE*2);
        if (xram_base==NULL)
        {
            printf("Error: failed to allocate memory for calculator XRAM.\n");
            wrapper_exit(EXIT_FAILURE);
        }

        //Round up xram to nearest 8K boundary keeping xram_base to pass to free later
        uintptr_t xram_diff=XRAM_SIZE-((uintptr_t)(xram_base))%XRAM_SIZE;
        xram=xram_base+xram_diff;

        //Allocate 8K for YRAM memory on calculator plus 8K for padding so 8K can be aligned
        yram_base=malloc(YRAM_SIZE*2);
        if (yram_base==NULL)
        {
            printf("Error: failed to allocate memory for calculator YRAM.\n");
            exit(1);
        }

        //Round up yram to nearest 8K boundary keeping yram_base to pass to free later
        uintptr_t yram_diff=YRAM_SIZE-((uintptr_t)(yram_base))%YRAM_SIZE;
        yram=yram_base+yram_diff;

        //Save ms to delay between frames
        global_delay_ms=delay_ms;

        //Scancode of last key pressed
        pc_scancode=0;

        //Open TCP socket
        sockfd=socket(AF_INET,SOCK_STREAM,0);
        if (sockfd==-1)
        {
            perror("Unable to open socket");
            wrapper_exit(EXIT_FAILURE);
        }
        else printf("Socket opened\n");

        //Connect to server
        struct sockaddr_in server;
        memset(&server,0,sizeof(server));
        server.sin_family=AF_INET;
        server.sin_addr.s_addr=inet_addr("127.0.0.1");
        server.sin_port=htons(PORT);
        int connect_result=connect(sockfd,(struct sockaddr *)&server,sizeof(server));
        if (connect_result==-1) 
        {
            perror("Unable to connect to server");
            wrapper_exit(EXIT_FAILURE);
        }
        else printf("Connected to server\n");

        //Notify server of endianness
        int endian_test=1;
        int32_t message;
        if (*((char *)&endian_test)==1) message=htonl(TCP_CLIENT_LITTLE_ENDIAN);
        else message=htonl(TCP_CLIENT_BIG_ENDIAN);
        int result=write_full(sockfd,&message,sizeof(message));
        if (result<0)
        {
            perror("Unable to send endianness");
            exit(EXIT_FAILURE);
        }
    }

    void delay()
    {
        wrapper_events();
        usleep(global_delay_ms*1000);
    }

    void wrapper_exit(int code)
    {
        //Free allocated memory
        if (heap!=MAP_FAILED)
            munmap(heap,HEAP_SIZE);
        free(xram_base);
        free(yram_base);

        //Disconnect from server if connection exists
        if (sockfd!=-1)
        {
            shutdown(sockfd,SHUT_RDWR);
            close(sockfd);
        }
        printf("Disconnected from server\n");

        exit(code);
    }

    void wrapper_screenshot()
    {
        //None of the examples with SDL_RenderReadPixels worked even when adjusted for 16bit format so output raw data
        FILE *fptr=fopen("screenshot/screenshot.raw","w");
        fwrite(screen,2,DWIDTH*DHEIGHT,fptr);
        fclose(fptr);
    }

    int wrapper_pc_key()
    {
        //Return PC scancode of last returned by getkey_opt
        return pc_scancode;
    }

    int wrapper_remap_key(int modifier,int key,struct KeyRemap *conversions)
    {
        //First, apply key conversions passed in as argument if they exist
        int return_key=remap_key_helper(modifier,key,conversions);
        if (return_key!=0)
        {
            //Conversion found - done searching
            return return_key;
        }

        //Next, apply default key conversions that apply to all programs
        //Do second to provide default behavior here that conversions above can overwrite
        return remap_key_helper(modifier,key,remapped_keys_all);
    }

    char *wrapper_normalize_path(const char *path,int local_path_max)
    {
        char result_path[PATH_MAX+1];
        char *ptr=realpath(path,result_path);
        if (ptr==NULL) return NULL;
        if (strlen(result_path)>local_path_max-1) return NULL;
        char *return_path=malloc(local_path_max);
        strcpy(return_path,result_path);
        return return_path;
    }

    void wrapper_perf_start(prof_t *time)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW,time);
    }

    uint32_t wrapper_perf_stop(prof_t *time)
    {
        prof_t stop;
        clock_gettime(CLOCK_MONOTONIC_RAW,&stop);
        return (stop.tv_sec-time->tv_sec)*1000000+(stop.tv_nsec-time->tv_nsec)/1000;
    }

    //Replacements for gint functions
    //===============================
    void dgetvram(uint16_t **main, uint16_t **secondary)
    {
        //No equivalent of main for SDL2 so set main to screen instead of NULL in case used for calculating 
        *main=screen;
        *secondary=screen;
    }

    void dclear(uint16_t color)
    {
        uint16_t *ptr=screen;
        for (int i=0;i<DHEIGHT*DWIDTH;i++)
        {
            *ptr=color;
            ptr++;
        }
    }

    void dupdate(void)
    {
        //Send screen data over TCP
        uint32_t message=htonl(TCP_FRAME_DATA);
        int result=write_full(sockfd,&message,sizeof(message));
        if (result<0)
        {
            perror("Error while writing screen data message");
            wrapper_exit(EXIT_FAILURE);
        }
        result=write_full(sockfd,(char *)screen,sizeof(screen));
        if (result<0)
        {
            perror("Error while writing screen data");
            wrapper_exit(EXIT_FAILURE);
        }

        //Wait for client to acknowedge receipt of screen data
        while(frame_ready==false)
        {
            //Check for TCP_FRAME message from server
            wrapper_events();

            //TODO: probably smarter way
            //Wait 1ms between checking 
            usleep(1000);
        }
    }

    key_event_t getkey_opt(int options, volatile int *timeout)
    {
        key_event_t ret_val;

        //Check for SDL_QUIT and new keypresses
        wrapper_events(); 
        
        //Function on calculator monitors *timeout for change since may be modified in interrupt but check only once here
        if ((timeout==NULL)||(*timeout==0))
        {
            //Loop until key is pressed
            while(true)
            {
                wrapper_events();

                if (keys_start!=keys_end)
                {
                    ret_val.type=KEYEV_DOWN;
                    ret_val.key=keys[keys_start];
                    pc_scancode=pc_keys[keys_start];
                    keys_start=(keys_start+1)%KEYS_SIZE;

                    return ret_val;
                }
            }
        }
        else
        {
            //Check for key and exit immediately
            if (keys_start!=keys_end)
            {
                ret_val.type=KEYEV_DOWN;
                ret_val.key=keys[keys_start];
                pc_scancode=pc_keys[keys_start];
                keys_start=(keys_start+1)%KEYS_SIZE;
            }
            else ret_val.type=KEYEV_NONE;

            return ret_val;
        }
    }

    void gint_osmenu()
    {
        //Empty function for compatibility
    }

    void gint_poweroff(bool show_logo)
    {
        //Empty function for compatibility
    }

#endif

