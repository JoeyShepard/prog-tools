#include <stdlib.h>

#include "console.h"
#include "forth-compatibility.h"
#include "key-remap.h"
#include "manager.h"
#include "structs.h"

struct ConsoleInfo *forth_console;
  
void forth_print(const char *text)
{
    console_text_default(text,forth_console);
}

void forth_print_color(const char *text,color_t color)
{
    console_text(text,color,forth_console->text_col_bg,forth_console);
}

//Function must perform address wrapping on any characters written!
int32_t forth_input(int32_t text_address,char *text_base,int32_t max_chars,uint32_t data_mask)
{
    //text_address  offset relative to beginning of data area where target text begins
    //text_base     beginning of memory where text is found. mask writes to wrap around here.
    //max_chars     maximum number of characters to accept
    //mask          mask to wrap writes with

    if (max_chars<0)
    {
        //No characters written - return 0
        //IMPORTANT - no need to jump to restore_exit below to restore console input since haven't diverted input yet
        return 0;
    }

    //Return value
    int32_t bytes_written;

    //Save state for input line for Forth console and reuse for input here
    struct ConsoleInput input_copy=forth_console->input;
    int input_text_max_copy=forth_console->input_text_max;

    //Limit size of input buffer
    if (max_chars>FORTH_ACCEPT_MAX) forth_console->input_text_max=FORTH_ACCEPT_MAX;
    else forth_console->input_text_max=max_chars;

    //Add space for zero terminator - not used by Forth but expected by input line functions
    forth_console->input_text_max++;

    //Allocate new text buffer for input line
    //+1 for zero terminator - not used by Forth but required by console input functions
    struct ConsoleChar *text_buffer=malloc(sizeof(struct ConsoleChar)*forth_console->input_text_max);
    if (text_buffer==NULL) goto restore_exit;

    //Write new values to existing input line
    struct ConsoleInput *input_line=&forth_console->input;
    input_line->text=text_buffer;
    input_line->text[0].character=0;
    input_line->len=0;
    input_line->cursor=0;
    input_line->visible=true;
     
    //Input loop
    int32_t char_count=0;
    bool redraw_console=true;
    bool redraw_modifier=false;
    while(1)
    {
        //Redraw modifiers (shift, alpha) as necessary even if rest of screen not redrawn
        if (redraw_modifier) draw_modifier(forth_console->modifier);

        //Redraw console if text has changed
        if (redraw_console) draw_console(forth_console);

        //Copy updates to screen if modifier keys or text have changed
        if ((redraw_console)||(redraw_modifier)) dupdate();
        redraw_console=true;

        //Get key
        int old_modifier=forth_console->modifier;
        int key=getkey_text(true,&forth_console->modifier,forth_keys);

        //Remap keys for Forth
        key=forth_key_remap(key);

        //Redraw modifiers (shift, alpha) next time through if they have changed
        if (old_modifier!=forth_console->modifier) redraw_modifier=true;
        else redraw_modifier=false;

        //If key is printable, add to output
        char character=vkey_printable[key];
        if (character!=0)
        {
            //Printable character - add to input line
            add_input_char(character,forth_console->input_col_fg,forth_console->input_col_bg,forth_console);
        }   
        else
        {
            switch (key)
            {
                //case VKEY_UP:     //Don't add input here to history
                //case VKEY_DOWN:   //Don't add input here to history
                case VKEY_LEFT:
                case VKEY_RIGHT:
                case VKEY_SHIFT_LEFT:
                case VKEY_SHIFT_RIGHT:
                case VKEY_UNDO:
                    //DEL with alpha active - treat as DEL so don't need to remove alpha to delete
                    //Fallthrough!
                case VKEY_DEL:
                    console_key(forth_console,key);
                    break;
                case VKEY_EXE:
                    //Copy input to console
                    for (int i=0;i<forth_console->input.len;i++)
                    {
                        console_char(forth_console->input.text[i].character,forth_console->input.text[i].fg,forth_console->input.text[i].bg,forth_console);
                    }
                    //Write input to memory
                    for (int i=0;i<forth_console->input.len;i++)
                    {
                        //Mask address
                        text_address&=data_mask;
                        //Write data
                        *(text_base+text_address)=input_line->text[i].character;
                        text_address++;
                    }
                    bytes_written=forth_console->input.len;
                    goto restore_exit;
                    break;
                default:
                    redraw_console=false;
            }
        }
    }

    //All exit paths MUST restore Forth console input so jump here to return
    restore_exit:
        //Restore Forth console
        free(text_buffer);
        forth_console->input=input_copy;
        forth_console->input_text_max=input_text_max_copy;

    return bytes_written;
}

int32_t forth_getkey(bool blocking)
{
    int key=getkey_text(blocking,&forth_console->modifier,forth_keys);
    return forth_key_remap(key);
}

int32_t forth_printable(int32_t key)
{
    if ((key<0)||(key>=vkey_printable_len))
    {
        //Key out of range - return 0
        return 0;
    }
    else
    {
        //Return printable equivalent to key
        return vkey_printable[key];
    }
}

void forth_update_screen()
{
    draw_console(forth_console);
    dupdate();
}

void forth_update_modifiers()
{
    draw_modifier(forth_console->modifier);
    dupdate();
}

void forth_clear_console()
{
    reset_console(forth_console); 
}
