#include "compatibility.h"
#include "command.h"
#include "getkey.h"
#include "graphics.h"
#include "manager.h"
#include "structs.h"
#include "text.h"

int old_command_line(int command_ID, struct WindowInfo window, uint8_t *heap_ptr)
{
    //char *input=heap_alloc(MAX_COMMAND_LINE);
    int index=0;
    //input[0]=0;
    int green=COL_MAX;

    while (true)
    {
        //TODO: redo
        int key;
        while ((key=getkey_wrapper(true)))
        {
            switch (key)
            {
                case VKEY_EXIT:
                    //Exit if on PC
                    wrapper_exit();
                    break;
                case VKEY_MENU:
                    //Save here if necessary
                    gint_osmenu();
                    break;
                case VKEY_ACON:
                    //Save here too to be safe
                    gint_poweroff(true);
                    break;
                /*
                case VKEY_DEL:
                    if (input_index)
                    {
                        input_index--;
                        input[input_index]=0;
                    }
                    break;
                default:
                    if (key_printable[key])
                    {
                        input[input_index]=key_printable[key];
                        input_index++;
                        input[input_index]=0;
                    }
                    break;
                */
            }
        }

        //Graphics

        //Update screen
        dupdate();

        //Limit FPS
        delay();
    }
}

