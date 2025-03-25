#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "compatibility.h"

#ifdef CG50
//cg50 specific
//=============

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

    //On CG50, initialize timer and catch unaligned memory accesses
    void setup(int scale_factor,int delay_ms)
    {
        //Exception handling for unaligned memory accesses
        setup_exception_handling();

        //Initialize timer for limiting FPS
        tick_flag=1;
        int t=timer_configure(TIMER_ANY, delay_ms*1000, GINT_CALL(timer_callback,&tick_flag));
        if (t>=0) timer_start(t);

        //Scale_factor only used on PC. Silence not used warning.
        scale_factor=scale_factor;
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

#else
//PC specific
//===========

    //Globals
    //=======
    uint16_t screen[DHEIGHT*DWIDTH];
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    int global_scale_factor;
    int global_delay_ms;
    #define KEYS_SIZE 100
    unsigned int keys[KEYS_SIZE];
    int keys_start=0,keys_end=0;
    uint8_t *heap;
    uint8_t *xram;
    uint8_t *yram;

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

        //Allocate 8K for XRAM memory on calculator
        xram=malloc(XRAM_SIZE);
        if (xram==NULL)
        {
            printf("Error: failed to allocate memory for calculator XRAM.\n");
            exit(1);
        }

        //Allocate 8K for YRAM memory on calculator
        yram=malloc(YRAM_SIZE);
        if (yram==NULL)
        {
            printf("Error: failed to allocate memory for calculator XRAM.\n");
            exit(1);
        }

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
    }

    void delay()
    {
        wrapper_events();
        SDL_Delay(global_delay_ms);
    }

    void gint_osmenu()
    {
        //Empty function for compatibility
    }

    void gint_poweroff(bool show_logo)
    {
        //Empty function for compatibility
    }


    //Functions only in PC version
    //============================
    void wrapper_exit()
    {
        //Shut down SDL2
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        exit(0);
    }

    void wrapper_events()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    wrapper_exit();
                    break;
                case SDL_KEYDOWN:
                    keys[keys_end]=wrapper_convert_key(event.key.keysym.scancode);
                    keys_end=(keys_end+1)%KEYS_SIZE;
                    break;
            }
        }
    }

    int wrapper_convert_key(int key)
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
                if (keys_start!=keys_end)
                {
                    ret_val.type=KEYEV_DOWN;
                    ret_val.key=keys[keys_start];
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
                keys_start=(keys_start+1)%KEYS_SIZE;
            }
            else ret_val.type=KEYEV_NONE;

            return ret_val;
        }
    }
#endif

