#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "debug.h"
#include "forth.h"
#include "forth-process.h"
#include "getkey.h"
#include "graphics.h"
#include "key-remap.h"
#include "logging.h"
#include "text.h"
#include "manager.h"
#include "mem.h"

static void color_input(struct ConsoleInfo *console,bool color_highlighted,struct ForthWordHeaderInfo *words)
{
    const char *quote_words[]=
    {
        ".\"",
        "S\"",
        "S\\\""
    };

    uint32_t start=0;
    uint32_t word_len=0;
    bool in_quote=false;
    bool in_word=false;
    bool colon_last=false;
    bool colon_current=false;
    while(1)
    {
        //Get next word in input
        start+=word_len;
        word_len=next_word(console,&start);

        //Stop looping if no words left
        if (word_len==0) break;

        //Figure out what color to use for word
        color_t word_color;
        if (in_quote)
        {
            //In quote like s" or ."
            word_color=FORTH_COL_STRING;
            if (console->input.text[start+word_len-1].character=='"') in_quote=false;
        }
        else
        {
            if (word_len>FORTH_WORD_MAX)
            {
                //Word too long - color but do not check if primitive or secondary
                word_color=FORTH_COL_ERROR;   
            }
            else
            {
                //Copy word to buffer for classification
                char word_buffer[FORTH_WORD_MAX+1];
                for (uint32_t j=start;j<start+word_len;j++)
                {
                    word_buffer[j-start]=console->input.text[j].character;
                    word_buffer[j-start+1]=0;
                }

                //Classify word
                int word_type=classify_word(word_buffer);
                if ((word_type!=FORTH_TYPE_OTHER)&&(colon_last==true))
                {
                    //Name in colon definition can't be number 
                    word_color=FORTH_COL_ERROR;
                }
                else if (word_type==FORTH_TYPE_NUMBER) word_color=FORTH_COL_NUMBER;
                else if (word_type==FORTH_TYPE_HEX) word_color=FORTH_COL_HEX;
                else if (word_type==FORTH_TYPE_OTHER)
                {
                    if (!strcmp(word_buffer,":"))
                    {
                        //Handle : different from other primitives
                        if (in_word)
                        {
                            //Not allowed in definition
                            word_color=FORTH_COL_ERROR;
                        }
                        else
                        {
                            in_word=true;
                            word_color=FORTH_COL_DEF;
                            colon_current=true;
                        }
                    }
                    else if (!strcmp(word_buffer,";"))
                    {
                        //Handle ; different from other primitives
                        if (in_word)
                        {
                            in_word=false;
                            word_color=FORTH_COL_DEF;
                        }
                        else
                        {
                            //Not allowed outside of definition
                            word_color=FORTH_COL_ERROR;
                        }
                    }
                    else if (find_primitive(word_buffer)!=FORTH_PRIM_NOT_FOUND)
                    {
                        //Always color primitives
                        if (colon_last)
                        {
                            //Primitive can't be word name after colon
                            word_color=FORTH_COL_ERROR;
                        }
                        else
                        {
                            //Default color for primitives
                            word_color=FORTH_COL_PRIMITIVE;

                            //Start quoted string if word found
                            for (int i=0;i<ARRAY_SIZE(quote_words);i++)
                            {
                                if (!strcasecmp(word_buffer,quote_words[i]))
                                {
                                    in_quote=true;
                                    word_color=FORTH_COL_STRING;
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        //Word is not primitive
                        bool cursor_on_word=(console->input.cursor>=start)&&(console->input.cursor<=start+word_len);
                        if ((cursor_on_word)&&(color_highlighted==false))
                        {
                            //Cursor is on secondary word - don't color as unknown since still typing
                            word_color=FORTH_COL_TYPING;
                        }
                        else 
                        {
                            if (find_secondary(word_buffer,words)!=NULL)
                            {
                                //Secondary found
                                word_color=FORTH_COL_SECONDARY;
                            }
                            else
                            {
                                if (colon_last)
                                {
                                    //Name of word definition;
                                    word_color=FORTH_COL_NEW_WORD;
                                }
                                else
                                {
                                    //Unknown word
                                    word_color=FORTH_COL_NOT_FOUND;
                                }
                            }
                        }
                    }
                }
                else if (word_type==FORTH_TYPE_NONE)
                {
                    //Should never happen but just in case
                    word_color=FORTH_COL_NONE;
                }
            }
        }

        //Logic to color definition name after colon
        colon_last=colon_current;
        colon_current=false;
    
        //Apply color to word
        for (uint32_t j=start;j<start+word_len;j++)
        {
            console->input.text[j].fg=word_color;
        }
    }
}

static void draw_forth_stack(struct ForthEngine *engine,int x,int y,int text_x,int text_y,int height,int window_state)
{
    //Text buffer to output stack count and stack values (ie "0:12345678")
    char text_buffer[sizeof("x:xxxxxxxx")];

    //Gray background to left of console window
    draw_rect(x,y,FORTH_STACK_WIDTH,height,FORTH_STACK_BORDER,FORTH_STACK_BG);

    //Print out Stack title and stack count
    struct Point pos={text_x,text_y};
    pos=draw_text("Stack[",pos,FORTH_STACK_FG,COL_TRANS,false,FONT_5x8);

    //Stack count should always be less than 256 but limit anyway since only space for three characters on screen
    uint8_t stack_count=forth_stack_count(engine);
    text_int32(stack_count,text_buffer);
    pos=draw_text(text_buffer,pos,FORTH_STACK_FG,COL_TRANS,false,FONT_5x8);
    pos=draw_text("]",pos,FORTH_STACK_FG,COL_TRANS,false,FONT_5x8);

    //Print stack values
    pos.x=text_x;
    pos.y+=CONS_ROW_HEIGHT;
    text_buffer[1]=':';
    for (int i=0;i<FORTH_STACK_SHOW_COUNT;i++)
    {
        int index=FORTH_STACK_SHOW_COUNT-i-1;
        text_buffer[0]=index+'0';
        if (index<stack_count)
        {
            //Stack value to print
            text_hex32_padded(*(engine->stack+index+1),text_buffer+2,8);
        }
        else
        {
            //Out of stack values - print placeholder instead
            strcpy(text_buffer+2," --     ");
        }

        //Color every other row of stack values slightly darker
        color_t color;
        if ((i&1)==0) color=FORTH_STACK_BG;
        else color=FORTH_STACK_BG2;
        pos=draw_text(text_buffer,pos,FORTH_STACK_FG,color,false,FONT_5x8);

        //Advance to next stack value
        pos.y+=CONS_ROW_HEIGHT;
        pos.x=text_x;
    }

    //Bottom line of last stack value is one pixel too tall so overwrite to match the others.
    draw_line_horz(x,x+FORTH_STACK_WIDTH-1,pos.y,FORTH_STACK_BG);

    //If full screen, fill remaining space with key legend and typing suggestion
    if (window_state==WINDOW_WHOLE)
    {
        //Small gap after stack display so easier to see
        pos.y+=FORTH_LEGEND_OFFSET_Y;
        
        //Key legend
        struct KeyText
        {
            const char *key;
            const char *remapped_key;
            const char *remapped_key_shift;
            const color_t fg_color;
            const color_t bg_color;
        };

        const char x_theta_t[]={'X',CHAR_CUSTOM_THETA,'T',0};
        const char exponent[]={'1','0',CHAR_CUSTOM_SUPER_X,0};
        const struct KeyText key_texts[]={
        {x_theta_t,"@","#",COL_WHITE,COL_BLACK},
        {"log","!","$",COL_WHITE,COL_BLACK},
        {"ln",":","%",COL_WHITE,COL_BLACK},
        {"sin",";","&",COL_WHITE,COL_BLACK},
        {"cos","\'","|",COL_WHITE,COL_BLACK},
        {"tan","?","\\",COL_WHITE,COL_BLACK},
        {" 0 "," ","<",COL_BLACK,COL_WHITE},
        {exponent," ",">",COL_BLACK,COL_WHITE}
        };
        
        const int legend_row_height=CONS_ROW_HEIGHT+2;
        for (int i=0;i<ARRAY_SIZE(key_texts);i++)
        {
            //Print out key
            pos.x=text_x+FORTH_LEGEND_OFFSET_X;
            if (strlen(key_texts[i].key)==2)
            {
                //Print key centered if name is only 2 long
                struct Point temp_pos=pos;
                pos=draw_text("   ",pos,key_texts[i].fg_color,key_texts[i].bg_color,false,FONT_5x8);
                temp_pos.x+=font_width(FONT_5x8)/2+1;
                draw_text(key_texts[i].key,temp_pos,key_texts[i].fg_color,-1,false,FONT_5x8);
            }
            else
            {
                //No special handling
                pos=draw_text(key_texts[i].key,pos,key_texts[i].fg_color,key_texts[i].bg_color,false,FONT_5x8);
            }

            //Print out remapped key
            pos.x+=font_width(FONT_5x8)*2;
            pos=draw_text(key_texts[i].remapped_key,pos,FORTH_STACK_FG,-1,false,FONT_5x8);
            
            //Print out remapped shifted key
            pos.x+=font_width(FONT_5x8)*2;
            pos=draw_text(key_texts[i].remapped_key_shift,pos,COL_SHIFT,-1,false,FONT_5x8);
            pos.y+=legend_row_height;
        }

        //Typing suggestion
        pos.x=text_x;
        pos.y+=FORTH_SUGGESTION_OFFSET_Y;
        draw_text("ACCEPT",pos,FORTH_COL_PRIMITIVE,FORTH_STACK_BG,true,FONT_5x8);
        pos.y+=FORTH_SUGGESTION_ROW_HEIGHT;
        pos.x=text_x;
        draw_text("ALIGN",pos,FORTH_COL_PRIMITIVE,COL_GREEN,false,FONT_5x8);
        pos.y+=FORTH_SUGGESTION_ROW_HEIGHT;
        pos.x=text_x;
        draw_text("ALIGNED",pos,FORTH_COL_PRIMITIVE,COL_GREEN,false,FONT_5x8);
    }
}

static int handle_VKEY_EXE(struct ForthInfo *forth,struct ConsoleInfo *console,struct ForthCompileInfo *compile)
{
    //Only process if text exists
    if (console->input.len==0) return COMMAND_NONE;

    int return_command=COMMAND_NONE;

    //Color input before copying to console since secondaries previously not colored if cursor is on them
    color_input(console,true,compile->words);

    //Copy input text to console
    for (uint32_t i=0;i<console->input.len;i++)
    {
        console_char(console->input.text[i].character,console->input.text[i].fg,console->input.text[i].bg,console);
    }
    console->reset_input=true;

    //Add input to history
    add_history(console);
    
    //Hide input line since program may output to console
    console_text_default(" ",console);
    console->input.visible=false;
    draw_console(console);
    dupdate();

    //Process input
    char input_buffer[FORTH_INPUT_MAX];
    copy_console_text(&console->input,input_buffer,FORTH_INPUT_MAX,0);
    int process_result=process_source(forth->engine,input_buffer,compile);

    //Exit if word like BYE requested program exit
    if (forth->engine->exit_program)
    {
        return_command=COMMAND_EXIT;
    }

    //Show input line again
    console_text_default("\n",console);
    console->input.visible=true;

    //Process errors from processing source
    switch (process_result)
    {
        case FORTH_ERROR_NONE:
            //No error - nothing to do
            break;
        case FORTH_ERROR_INVALID_NAME:
        case FORTH_ERROR_MISSING_QUOTE:
        case FORTH_ERROR_NO_WORD:
        case FORTH_ERROR_NOT_BETWEEN_BRACKETS:
        case FORTH_ERROR_NOT_FOUND:
        case FORTH_ERROR_TOO_LONG:
            //All of these errors share code for printing out word that caused error
            if (process_result==FORTH_ERROR_INVALID_NAME)
                console_text_default("Invalid word for operation: ",console);
            else if (process_result==FORTH_ERROR_MISSING_QUOTE)
                console_text_default("Missing \" after ",console);
            else if (process_result==FORTH_ERROR_NO_WORD)
                console_text_default("Missing word after ",console);
            else if (process_result==FORTH_ERROR_NOT_BETWEEN_BRACKETS)
                console_text_default("Word not allowed between [ and ]: ",console);
            else if (process_result==FORTH_ERROR_NOT_FOUND)
                //Word not found by outer interpreter. For secondary calling undefined word, see FORTH_ENGINE_ERROR_UNDEFINED.
                console_text_default("Word not defined: ",console);
            else if (process_result==FORTH_ERROR_TOO_LONG)
                console_text_default("Word too long: ",console);

            //Output word causing error
            uint32_t start=0;
            uint32_t word_len=next_word_source(compile->error_word,&start);
            for (uint32_t i=0;i<word_len;i++)
                console_char_default(compile->error_word[i],console);
            console_text_default("\n",console);
            break;
        case FORTH_ERROR_ENGINE:
            //Error set in Forth engine - ie inside of primitive
            switch (forth->engine->error)
            {
                case FORTH_ENGINE_ERROR_NONE:
                    //Should never happen but just in case
                    console_text_default("Engine error but code not set\n",console);
                    break;
                case FORTH_ENGINE_ERROR_INTERPRET_ONLY:
                case FORTH_ENGINE_ERROR_COMPILE_ONLY:
                    if (forth->engine->error==FORTH_ENGINE_ERROR_INTERPRET_ONLY)
                        console_text_default("Word is interpret only: ",console);
                    else if (forth->engine->error==FORTH_ENGINE_ERROR_COMPILE_ONLY)
                        console_text_default("Word is compile only: ",console);
                    //All of these errors share code for printing out word that caused error
                    uint32_t start=0;
                    uint32_t word_len=next_word_source(compile->error_word,&start);
                    for (uint32_t i=0;i<word_len;i++)
                        console_char_default(compile->error_word[i],console);
                    console_text_default("\n",console);
                    break;
                case FORTH_ENGINE_ERROR_RSTACK_FULL:
                    console_text_default("Out of R-stack space - aborting\n",console);
                    break;
                case FORTH_ENGINE_ERROR_UNDEFINED:
                    console_text_default("Word not defined: ",console);
                    console_text_default(forth->engine->error_word,console);
                    console_text_default("\n",console);
                    break;
                case FORTH_ENGINE_ERROR_RIGHT_BRACKET:
                    console_text_default("Word must occur in definition: ]\n",console);
                    break;
                case FORTH_ENGINE_ERROR_SECONDARY_IN_BRACKET:
                    console_text_default("Word is still being defined: ",console);
                    console_text_default(forth->engine->error_word,console);
                    console_text_default("\n",console);
                    break;
                default:
                    //No error message for error - should never reach here unless forgot to add error message
                    console_text_default("Unhandled engine error: ",console);
                    char num_buffer[TEXT_INT32_SIZE];
                    text_int32(forth->engine->error,num_buffer);
                    console_text_default(num_buffer,console);
                    console_text_default("\n",console);
                    break;
            }
            break;
        case FORTH_ERROR_MEMORY_OTHER:
            console_text_default("Memory allocation error such as alignment\n",console);
            break;
        case FORTH_ERROR_OUT_OF_MEMORY:
            console_text_default("Out of memory\n",console);
            break;
        default:
            //No error message for error - should never reach here unless forgot to add error message
            console_text_default("Unhandled error: ",console);
            char num_buffer[TEXT_INT32_SIZE];
            text_int32(process_result,num_buffer);
            console_text_default(num_buffer,console);
            console_text_default("\n",console);
            break;
    }

    //Check compile state - definition can't be left open
    if ((forth->engine->state==FORTH_STATE_COMPILE)||((forth->engine->state==FORTH_STATE_INTERPRET)&&(forth->engine->in_bracket==true)))
    {
        //Definition left open - cancel word
        struct ForthWordHeader *secondary=compile->words->header;

        //Cancel new words headers and recover memory
        uint32_t rewind_header_bytes=0;
        uint32_t rewind_name_bytes=0;
        uint32_t header_count=0;
        bool looping=true;
        while(looping==true)
        {
            //Check if at end of list first since ->done not valid unless ->last is false
            if (secondary->last==false)
            {
                //Still looping through headers
                if (secondary->done==false)
                {
                    //Reached unfinished header - mark as end of list of headers
                    //(Marking end only useful for first marked header but doesn't hurt to mark all)
                    secondary->last=true;
                    rewind_header_bytes+=sizeof(*secondary);
                    rewind_name_bytes+=secondary->name_len+1;
                    header_count++;
                }
                else
                {
                    //Header was not created while defining this word so nothing to do. This happens because
                    //the header refers to something else or the definition redefined an existing word that
                    //already had a header.
                }
            }
            else
            {
                //Reached end of list - done looping
                looping=false;
            }

            //Advance to next word header
            secondary++;
        }

        //Restore header information to state before aborted word began
        compile->words->index-=header_count;
        compile->words->bytes_left+=rewind_header_bytes;
        compile->word_names->index-=rewind_name_bytes;
        compile->word_names->bytes_left+=rewind_name_bytes;

        //Restore target address pointer of word if it existed before
        if (compile->colon_word_exists==true)
        {
            if (compile->save_type!=FORTH_SECONDARY_UNDEFINED) 
                compile->colon_word->address=(void(**)(struct ForthEngine *))(compile->definitions->data+compile->save_offset);
            else compile->colon_word->address=NULL;
            compile->colon_word->offset=compile->save_offset;
            compile->colon_word->definition_size=compile->save_definition_size;
            compile->colon_word->type=compile->save_type;
        }

        if (process_result==FORTH_ERROR_NONE)
        {
            //Only warn of unterminated word if no other error
            console_text_default("Unterminated word: ",console);
            console_text_default(compile->colon_word->name,console);
            console_text_default("\n",console);
        }

        //Back to interpret mode
        forth->engine->state=FORTH_STATE_INTERPRET;
        forth->engine->in_bracket=false;
    }

    //Return value set above
    return return_command;
}

int forth(int command_ID, struct WindowInfo *windows, int selected_window)
{
    struct WindowInfo window=windows[selected_window];
    int width=window_width(window);
    int height=window_height(window);
    struct Point pos;
    int drawn_split;
    if (command_ID==COMMAND_REDRAW)
    {
        //Split being drawn for REDRAW is the split that isn't selected so invert split number
        drawn_split=window.selected_split^1;
        pos=window_pos(window,false);
    }
    else
    {
        drawn_split=window.selected_split;
        pos=window_pos(window,true);
    }

    //Pointers to data on heap
    struct ForthInfo *forth;
    struct ConsoleInfo *console;
    uint8_t *forth_data;

    //struct to hold arguments to compile functions. No need to preserve on heap.
    struct ForthCompileInfo compile;

    //Heap memory
    select_heap(window.tab_index,drawn_split);
    compile.heap_ptr=get_split_heap();

    if (command_ID==COMMAND_START) 
    {
        //Allocate memory for console and Forth system
        forth=(struct ForthInfo *)add_object(sizeof(struct ForthInfo),compile.heap_ptr);

        //Make sure allocation succeeded
        if (forth==NULL)
        {
            error_screen(ERROR_OUT_OF_MEMORY,pos,width,height);
            return COMMAND_EXIT;
        }

        //Allocate space for Forth data memory
        forth_data=add_object(FORTH_MEM_DATA,compile.heap_ptr);

        //Make sure allocation succeeded
        if (forth_data==NULL)
        {
            error_screen(ERROR_OUT_OF_MEMORY,pos,width,height);
            return COMMAND_EXIT;
        }

        //Allocate space for Forth word definitions
        compile.definitions=(struct ForthDefinitionsInfo *)add_object(FORTH_MEM_DATA,compile.heap_ptr);

        //Make sure allocation succeeded
        if (compile.definitions==NULL)
        {
            error_screen(ERROR_OUT_OF_MEMORY,pos,width,height);
            return COMMAND_EXIT;
        }

        //Initialize empty definition list
        compile.definitions->index=0;
        compile.definitions->bytes_left=FORTH_MEM_DEFINITIONS-sizeof(struct ForthDefinitionsInfo);

        //Allocate space for Forth word headers
        compile.words=(struct ForthWordHeaderInfo *)add_object(FORTH_MEM_WORD_HEADERS,compile.heap_ptr);

        //Make sure allocation succeeded
        if (compile.words==NULL)
        {
            error_screen(ERROR_OUT_OF_MEMORY,pos,width,height);
            return COMMAND_EXIT;
        }

        //Initialize empty Forth word header list
        compile.words->index=0;
        compile.words->bytes_left=FORTH_MEM_WORD_HEADERS-sizeof(struct ForthWordHeaderInfo);

        //First header is empty marking end of header list
        compile.words->header[0].last=true;

        //Allocate space for Forth word names 
        compile.word_names=(struct ForthWordNameInfo *)add_object(FORTH_MEM_WORD_NAMES,compile.heap_ptr);

        //Make sure allocation succeeded
        if (compile.word_names==NULL)
        {
            error_screen(ERROR_OUT_OF_MEMORY,pos,width,height);
            return COMMAND_EXIT;
        }

        //Initialize empty Forth word names
        compile.word_names->index=0;
        compile.word_names->bytes_left=FORTH_MEM_WORD_NAMES-sizeof(struct ForthWordNameInfo);

        //Allocate space for control stack
        compile.control_stack=(struct ForthControlElement *)add_object(FORTH_MEM_CONTROL_STACK,compile.heap_ptr);

        //Make sure allocation succeeded
        if (compile.control_stack==NULL)
        {
            error_screen(ERROR_OUT_OF_MEMORY,pos,width,height);
            return COMMAND_EXIT;
        }

        //TODO: remove
        *(uint32_t *)compile.control_stack=0x12345678;


        //Init console
        console=&forth->console;
        init_console(
            //Console
            console,
            FORTH_COL_FG,
            FORTH_COL_BG,
            //Input
            forth->input_text,
            forth->input_copy_text,
            FORTH_INPUT_MAX,
            FORTH_COL_FG,
            FORTH_COL_BG,
            //History
            forth->history,
            forth->history_texts,
            FORTH_HIST_COUNT);
        reset_console_pointers(console);
        reset_console(console);

        //Init input
        console_text_default(FORTH_CONSOLE_STRING,console);
        console->reset_input=true;
        console->modifier=MODIFIER_ALPHA_LOWER_LOCK;
        console->input_copied=false;

        //Init history
        init_history(console);

        //Init Forth window
        forth->draw_stack=true;

        //Init Forth engine 
        forth->engine=(struct ForthEngine *)FORTH_ENGINE_ADDRESS;
        forth_init_engine(forth->engine,
            FORTH_STACK_ADDRESS,
            FORTH_RSTACK_ADDRESS,
            FORTH_STACK_ELEMENTS,
            FORTH_RSTACK_ELEMENTS,
            FORTH_MEM_DATA,
            forth_print,
            forth_print_color,
            forth_input,
            forth_getkey,
            forth_printable,
            forth_update_screen,
            forth_update_modifiers,
            forth_clear_console,
            FORTH_MAX_SPACES,
            CONS_WHOLE_WIDTH-FORTH_STACK_CHAR_WIDTH,
            CONS_WHOLE_HEIGHT);
    }
    else
    {
        //Resume or Redraw - reuse existing memory for console
        forth=(struct ForthInfo *)object_address(FORTH_ID_CONSOLE,compile.heap_ptr);
        console=&forth->console;
        reset_console_pointers(console);

        //Restore Forth engine 
        *forth->engine=forth->engine_copy;

        //Restore pointers to word definitions, list of word headers, and control stack
        forth_data=object_address(FORTH_ID_DATA,compile.heap_ptr);
        compile.definitions=(struct ForthDefinitionsInfo *)object_address(FORTH_ID_DEFINITIONS,compile.heap_ptr);
        compile.words=(struct ForthWordHeaderInfo *)object_address(FORTH_ID_WORD_HEADERS,compile.heap_ptr);
        compile.word_names=(struct ForthWordNameInfo *)object_address(FORTH_ID_WORD_NAMES,compile.heap_ptr);
        compile.control_stack=(struct ForthControlElement *)object_address(FORTH_ID_CONTROL_STACK,compile.heap_ptr);

        //Recalculate pointers in word header
        struct ForthWordHeader *secondary=compile.words->header;
        while (secondary->last==false)
        {
            //Recalculate execution pointer
            secondary->address=(void (**)(struct ForthEngine *engine))(compile.definitions->data+secondary->offset);

            //Recalculate word name pointer
            secondary->name=compile.word_names->names+secondary->name_offset;

            //Advance to next word header
            secondary++;
        }

        //Restore stack memory
        memcpy(FORTH_STACK_ADDRESS,forth->stack_copy,FORTH_STACK_SIZE);
        memcpy(FORTH_RSTACK_ADDRESS,forth->rstack_copy,FORTH_RSTACK_SIZE);
    }

    //Compatibility layer settings
    forth_console=console;

    //Reset pointers in Forth engine
    forth_reload_engine(forth->engine,forth_data);

    //Redraw screen but only spare pixels on edges. Letters redrawn below.
    draw_rect(pos.x,pos.y,width,height,FORTH_COL_BG,FORTH_COL_BG);

    //Set position based on split location
    init_position(console,pos,window.split_state);

    //Display stack if split vertically or no split but not if split horizontally
    bool draw_stack;
    int stack_x,stack_y;
    int stack_text_x;
    int stack_text_y;
    if (((window.split_state==WINDOW_VSPLIT)||(window.split_state==WINDOW_WHOLE))&&(forth->draw_stack))
    {
        stack_x=pos.x;
        stack_y=pos.y;
        stack_text_x=pos.x;
        stack_text_y=console->y;
        console->x+=FORTH_STACK_WIDTH+FORTH_STACK_CONSOLE_X_OFFSET;
        console->width-=FORTH_STACK_CHAR_WIDTH;
        draw_stack=true;
    }
    else draw_stack=false;


    //TODO: delete
    //const char *debug_keys=": a 4 ;\n: b 5 ;\n: c a b ;\n: d c + c * * ;\n: e d d * ;\ne .\na\n: a\na\n";
    //const char *debug_keys=": a 4 ;\n: b 5 ;\n: c a b ;\n: d c + c * * ;\n: e d d * ;\ne .\na\n: a\na\n: a g\na\n";
    //const char *debug_keys=": a 4 ;\n: b 5 ;\n: c a b ;\n: d c + c * * ;\n: e d d * ;\ne .\na\n: a\na\n: a g\na\n: a x ;\n: x\n";
    //const char *debug_keys=": asdfasdfasdf a b c d e f ;\n: a b ;\n: b 1 ;\na\nb\n: c d 1 + ;\n: d e 1 + ;\n: e f 1 + ;\n: f 3 ;\nc";
    //const char *debug_keys=": asdf a b c d e f ;\n: a b ;\n: b 1 ;\n: c d 1 + ;\n: d e 1 + ;\n: e f 1 + ;\n: f 3 ;\n";
    //const char *debug_keys=": x a 5 x.r ; var a 0x123 a ! : x a @ 5 x.r ; x";
    //const char *debug_keys=": foo s\\\" \\a\\b \\c \\e\\f\\l \\m \\n\\q\\r\\t\\v\\z\\\" \\x12\\xAB\\xcd\\x1A\\x2b \\\\ \\x00 abc\" ; foo" ;
    //const char *debug_keys=": foo .\" abc\" ; foo\n";
    const char *debug_keys="";

    //Main loop
    bool redraw_screen=true;
    bool redraw_modifier=true;
    int return_command;
    while (1)
    {
        //Set text for input line
        if (console->reset_input)
        {
            console->input.text[0].character=0;
            console->input.cursor=0;
            console->input.len=0;
            console_text(FORTH_PROMPT,FORTH_COL_FG,FORTH_COL_BG,console);
            console->input_copied=false;
        }
        console->reset_input=false;

        //Redraw modifiers (shift, alpha) as necessary even if rest of screen not redrawn
        if (redraw_modifier) draw_modifier(console->modifier);

        if (redraw_screen)
        {
            //Color code input
            color_input(console,false,compile.words);

            //Always redraw screen whether START, RESUME, or REDRAW
            draw_console(console);

            //Redraw stack if visible
            if (draw_stack)
            {
                draw_forth_stack(forth->engine,stack_x,stack_y,stack_text_x,stack_text_y,height,window.split_state);
            }
                
            //Return if Redraw only
            if (command_ID==COMMAND_REDRAW) return COMMAND_DONE;
        }

        //Copy updates to screen if modifier keys or text have changed
        if ((redraw_screen)||(redraw_modifier)) dupdate();
        redraw_screen=true;
        
        //Whether to save to memory and exit Forth - may be set by key or command so handle outside of key loop
        bool save_exit=false;

        //TODO: comments
        //Get key
        int old_modifier=console->modifier;
        int key;
        char character;
        if (*debug_keys)
        {
            if (*debug_keys=='\n')
            {
                key=VKEY_EXE;
                character=0;
            }
            else character=*debug_keys;
            debug_keys++;
        }
        else
        {
            key=getkey_text(true,&console->modifier,forth_keys);
        
            //Remap keys on keypad for Forth. Also, recognize PC keyboard keys for testing.
            key=forth_key_remap(key);
            
            //Redraw modifiers (shift, alpha) next time through if they have changed
            if (old_modifier!=console->modifier) redraw_modifier=true;
            else redraw_modifier=false;

            //Look for keys before sys_key_handler below in case need to handle any sys_keys differently
            character=vkey_printable[key];
        }

        if (character!=0)
        {
            //Printable character - add to input line
            add_input_char(character,FORTH_COL_FG,FORTH_COL_BG,console);
        }
        else
        {
            //Process keys
            switch (key)
            {
                case VKEY_QUIT: //Shift+EXIT
                    //Exit and return to window manager
                    return_command=COMMAND_EXIT;
                    save_exit=true;
                    break;
                case VKEY_EXIT:
                    //Clear line but do not exit program
                    //Handle here so not picked up by sys_key_handler below which would exit program
                    if (console->input.len==0)
                    {
                        //No input on line - don't cancel
                        break;
                    }
                    
                    //Color line before ^C added
                    color_input(console,true,compile.words);

                    //Append ^C to show input cancelled
                    const char *cancel_text="^C";
                    if (console->input.len>=FORTH_INPUT_MAX-(uint32_t)strlen(cancel_text))
                    {
                        //Not enough room to append ^C so drop characters from end of input to make room
                        console->input.len=FORTH_INPUT_MAX-strlen(cancel_text)-1;
                        console->input.cursor=FORTH_INPUT_MAX-strlen(cancel_text)-1;
                    }
                    add_input_text(cancel_text,FORTH_COL_FG,FORTH_COL_BG,console);

                    //Copy input text to console
                    for (uint32_t i=0;i<console->input.len;i++)
                    {
                        console_char(console->input.text[i].character,console->input.text[i].fg,console->input.text[i].bg,console);
                    }
                    console->reset_input=true;
                    
                    //Newline after cancelled input
                    console_text_default(" \n",console);
                    break;
                case VKEY_EXE:
                    return_command=handle_VKEY_EXE(forth,console,&compile);
                    if (return_command!=COMMAND_NONE)
                    {
                        //Handling EXE above generated request to exit Forth
                        save_exit=true;
                    }
                    break;
                case VKEY_UP:
                case VKEY_DOWN:
                case VKEY_LEFT:
                case VKEY_RIGHT:
                case VKEY_SHIFT_LEFT:
                case VKEY_SHIFT_RIGHT:
                case VKEY_UNDO:
                    //DEL with alpha active - treat as DEL so don't need to remove alpha to delete
                    //Fallthrough!
                case VKEY_DEL:
                    console_key(console,key);
                    break;
                case VKEY_INS:  //Shift+VKEY_DEL
                    //Reset Forth data stack
                    forth->engine->stack=(int32_t*)(forth->engine->stack_base+(forth->engine->stack_count-1)*FORTH_CELL_SIZE);
                    break;
                default:
                    //Check for system keys like MENU, OFF, etc
                    return_command=sys_key_handler(key);
                    if (return_command!=COMMAND_NONE)
                    {
                        //System key - set flag to save and exit so window manager can process key
                        save_exit=true;
                    }
                    else
                    {
                        //No key found - don't redraw screen
                        redraw_screen=false;
                    }
            }
        }
        //If key or command sets exit flag, save stack to memory and exit
        if (save_exit)
        {
            //Save Forth stack memory before returning
            memcpy(forth->stack_copy,FORTH_STACK_ADDRESS,FORTH_STACK_SIZE);
            memcpy(forth->rstack_copy,FORTH_RSTACK_ADDRESS,FORTH_RSTACK_SIZE);

            //Save Forth engine before returning
            forth->engine_copy=*forth->engine;

            //Return to window manager to handle exit function which may be system key (switch window, etc)
            return return_command;
        }
    }

    //Shouldn't reach here - added to silence warning
    return COMMAND_DONE;
}

