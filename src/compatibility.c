#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "compatibility.h"
#include "macros.h"

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
    void setup(UNUSED(int scale_factor),int delay_ms)
    {
        //TODO: reenable? added at first but now it may be hiding errors

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

    void wrapper_exit()
    {
        //Empty function for compatibility
    }

    void wrapper_screenshot()
    {
        //Empty function for compatibility
    }

    int wrapper_pc_key()
    {
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

    #include <linux/limits.h>
    #include <pthread.h>
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <unistd.h>

    //Globals
    //=======
    uint16_t screen[DHEIGHT*DWIDTH];
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    int global_scale_factor;
    int global_delay_ms;
    #define KEYS_SIZE 100
    int keys[KEYS_SIZE];
    int pc_keys[KEYS_SIZE];
    int pc_scancode;
    int keys_start=0,keys_end=0;
    uint8_t *heap;
    uint8_t *xram;
    uint8_t *yram;
    uint8_t *xram_base;
    uint8_t *yram_base;
    pthread_mutex_t sdl_mutex;
    pthread_t thread_id;
    volatile bool exit_thread;

    //Static functions only in PC version
    //===================================
    static int wrapper_convert_key(int key)
    {
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
            SDL_SCANCODE_TAB,           KEY_XOT,
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

    static void wrapper_events()
    {
        //Also called by separate thread so lock here with mutex

        pthread_mutex_lock(&sdl_mutex);

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:

                    //Unlock mutex before exiting
                    pthread_mutex_unlock(&sdl_mutex);
                    wrapper_exit();
                    break;
                case SDL_KEYDOWN:
                    keys[keys_end]=wrapper_convert_key(event.key.keysym.scancode);
                    pc_keys[keys_end]=event.key.keysym.scancode;
                    keys_end=(keys_end+1)%KEYS_SIZE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    wrapper_screenshot();
                    printf("screenshot saved to screenshot/screenshot.raw\n");
                    break;
            }
        }
        
        //Unlock mutex protecting SDL_PollEvent
        pthread_mutex_unlock(&sdl_mutex);
    }

    //Thread function mirroring interrupt on cg50 that checks for ON key
    static void *interrupt_thread(UNUSED(void *arg))
    {
        //Run for the life of the program
        while(1)
        {
            //Check for SDL_QUIT and new keypresses
            wrapper_events();

            //End thread if SDL_QUIT
            if (exit_thread) return NULL;

            //Check if ON key (mapped to HOME on PC) is down
            const Uint8 *key_list=SDL_GetKeyboardState(NULL);
            
            if (key_list[SDL_SCANCODE_HOME]!=0)
            {
                //Clear flag pointed to by this pointer if ON down. Halts interpreter if one is running.
                if (on_key_executing!=NULL)
                {
                    *on_key_executing=false;

                    //Also, set flag to tell interpreter ON key was source of halt
                    if (on_key_pressed!=NULL) *on_key_pressed=true;
                }
            }
            
            //Check 5 times per second
            usleep(200000);
        }

        return NULL;
    }

    //Functions with separate copies for cg50 and PC
    //==============================================
    //On PC, start SDL2
    void setup(int scale_factor, int delay_ms)
    {
        //Allocate 2MB heap to use like 2MB RAM on calculator
        heap=malloc(HEAP_SIZE);
        if (heap==NULL)
        {
            printf("Error: failed to allocate memory for calculator heap.\n");
            exit(1);
        }

        //Allocate 8K for XRAM memory on calculator plus padding so 8K can be aligned
        xram_base=malloc(XRAM_SIZE*2);
        if (xram_base==NULL)
        {
            printf("Error: failed to allocate memory for calculator XRAM.\n");
            exit(1);
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

        //Save scale factor for use with dupdate
        global_scale_factor=scale_factor;
        global_delay_ms=delay_ms;

        //Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO)<0)
        {
            printf("Error: SDL2 did not initialize. SDL error: %s\n", SDL_GetError());
            exit(1);
        }
        
        //Create window
        window=SDL_CreateWindow(WINDOW_TITLE,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,DWIDTH*scale_factor,DHEIGHT*scale_factor,SDL_WINDOW_SHOWN);
        if (window==NULL)
        {
            printf("Error: SDL2 could not create window. SDL error: %s\n", SDL_GetError());
            exit(1);
        }

        //Draw to texture
        renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        texture=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGB565,SDL_TEXTUREACCESS_STREAMING,DWIDTH,DHEIGHT);

        //Scancode of last key pressed
        pc_scancode=0;

        //Signal thread to exit when program ends
        exit_thread=false;

        //Create mutex for wrapper_events since it calls SDL_PollEvent and is called by main and second thread
        pthread_mutex_init(&sdl_mutex,NULL);

        //Thread sets target of this pointer to false when ON is pressed to halt interpreter if one is running
        on_key_executing=NULL;

        //Create separate thread to check for ON key (HOME on PC) mirroring interrupt on calculator
        int result=pthread_create(&thread_id,NULL,interrupt_thread,NULL);
    }

    void delay()
    {
        wrapper_events();
        SDL_Delay(global_delay_ms);
    }

    void wrapper_exit()
    {
        //Wait on thread to exit
        pthread_mutex_lock(&sdl_mutex);
        exit_thread=true;
        pthread_mutex_unlock(&sdl_mutex);
        pthread_join(thread_id,NULL);

        //Free allocated memory
        free(heap);
        free(xram_base);
        free(yram_base);

        //Shut down SDL2
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        exit(0);
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
        if (conversions==NULL)
        {
            //No list of conversions
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
        SDL_UpdateTexture(texture,NULL,screen,DWIDTH*sizeof(uint16_t));
        SDL_RenderCopy(renderer,texture,NULL,NULL);
        SDL_RenderPresent(renderer);
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

                //Lock with mutex since second thread also calls wrapper_events which modifies keys_end
                pthread_mutex_lock(&sdl_mutex);

                if (keys_start!=keys_end)
                {
                    ret_val.type=KEYEV_DOWN;
                    ret_val.key=keys[keys_start];
                    pc_scancode=pc_keys[keys_start];
                    keys_start=(keys_start+1)%KEYS_SIZE;

                    //Unlock mutex before returning
                    pthread_mutex_unlock(&sdl_mutex);

                    return ret_val;
                }

                //Unlock mutex if no key found
                pthread_mutex_unlock(&sdl_mutex);
            }
        }
        else
        {
            //Lock with mutex since second thread also calls wrapper_events which modifies keys_end
            pthread_mutex_lock(&sdl_mutex);

            //Check for key and exit immediately
            if (keys_start!=keys_end)
            {
                ret_val.type=KEYEV_DOWN;
                ret_val.key=keys[keys_start];
                pc_scancode=pc_keys[keys_start];
                keys_start=(keys_start+1)%KEYS_SIZE;
            }
            else ret_val.type=KEYEV_NONE;

            //Unlock mutex
            pthread_mutex_unlock(&sdl_mutex);

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

