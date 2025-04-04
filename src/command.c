//placeholder functions for menu
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


//TODO: remove???
#include <sys/stat.h>


#include "command.h"
#include "compatibility.h"
#include "debug.h"
#include "getkey.h"
#include "graphics.h"
#include "text.h"
#include "dummy.h"
#include "manager.h"
#include "mem.h"
#include "structs.h"


//Functions
static void console_char(const char character, color_t fg, color_t bg, struct ConsoleInfo *console)
{
    if (console->text_len<CMD_BUFFER_SIZE)
    {
        //Text buffer not full yet
        console->text_len++;
    }
    else
    {
        //Buffer full - keep track of number of characters overwritten
        if (console->text[console->buffer_index].character=='\n')
        {
            //New line overwritten - reset count
            console->overflow_count=0;
        }
        else
        {
            //Add character overwritten to count for alignment when printing
            console->overflow_count++;
        }
    }
    console->text[console->buffer_index].character=character;
    console->text[console->buffer_index].fg=fg;
    console->text[console->buffer_index].bg=bg;
    console->buffer_index++;
    if (console->buffer_index==CMD_BUFFER_SIZE) console->buffer_index=0;
}

static void console_text(const char *text, color_t fg, color_t bg, struct ConsoleInfo *console)
{
    while (*text)
    {
        console_char(*text,fg,bg,console);
        text++;
    }
}

static void console_text_default(const char *text, struct ConsoleInfo *console)
{
    console_text(text,CMD_COL_FG,CMD_COL_BG,console);
}

static void console_ntext(const char *text, int text_len, color_t fg, color_t bg, struct ConsoleInfo *console)
{
    for (int i=0;i<text_len;i++)
        console_char(text[i],fg,bg,console);
}

static void add_input_text(const char *text,color_t fg,color_t bg,bool add_to_start,struct ConsoleInfo *console)
{
    int text_len=strlen(text);
    if (console->input.len+text_len>=CMD_INPUT_MAX-1)
    {
        //Shorten text to be added if longer than space available
        text_len=CMD_INPUT_MAX-1-console->input.len;
    }

    int text_index;
    if (add_to_start)
    {
        //Add text to display text at the beginning
        text_index=console->input.len;
    }
    else
    {
        //Add text to input
        text_index=console->input.cursor;
    }

    //Move existing text right if inserting text in middle of string
    for (int i=console->input.len;i>=text_index;i--)
    {
        console->input.text[i+text_len]=console->input.text[i];
    }

    //Copy in new text
    for (int i=0;i<text_len;i++)
    {
        console->input.text[text_index+i].character=text[i];
        console->input.text[text_index+i].fg=fg;
        console->input.text[text_index+i].bg=bg;
    }

    if (add_to_start)
    {
        //Text added to display text at beginning
        console->input.start+=text_len;
    }
    console->input.cursor+=text_len;
    console->input.len+=text_len;
}

static void add_input_char(char character,color_t fg,color_t bg,bool add_to_start,struct ConsoleInfo *console)
{
    char buffer[2];
    buffer[0]=character;
    buffer[1]=0;
    add_input_text(buffer,fg,bg,add_to_start,console);
}

static void draw_input_line(struct ConsoleInfo *console,struct point pos,int console_width,int input_height)
{
    int starting_x=pos.x;
    int char_index=0;
    bool cursor_drawn=false;
    bool invert;
    for (int row=0;row<input_height;row++)
    {
        for (int col=0;col<console_width;col++)
        {
            char character;
            int color_fg, color_bg;
            if (console->input.text[char_index].character!=0)
            {
                //Draw character of input
                character=console->input.text[char_index].character;
                color_fg=console->input.text[char_index].fg;
                color_bg=console->input.text[char_index].bg;
                if (char_index==console->input.cursor)
                {
                    //Cursor character - invert
                    invert=true;
                    cursor_drawn=true;
                }
                else invert=false;
                char_index++;
            }
            else
            {
                character=' ';
                color_fg=CMD_COL_FG;
                color_bg=CMD_COL_BG;
                if (cursor_drawn==false)
                {
                    //Cursor not drawn yet - draw cursor
                    invert=true;
                    cursor_drawn=true;
                }
                else
                {
                    //Draw spaces for rest of line
                    invert=false;
                }
            }
            pos=draw_char(character,pos,color_fg,color_bg,invert,FONT_5x8);
        }
        pos.x=starting_x;
        pos.y+=CMD_ROW_HEIGHT;
    }
}

static void draw_console(struct ConsoleInfo *console,int console_x,int console_y,int console_width,int console_height)
{
    //Adjust console_height to make room for input line
    int input_height=((console->input.len)/console_width)+1;
    console_height-=(input_height-1);

    //Find starting point in circular screen buffer for printing characters
    int line_length=0;
    int line_count=0;
    int buffer_counter=console->buffer_index;
    int buffer_start=buffer_counter;
    for (int i=0;i<console->text_len;i++)
    {
        //Loop backwords through screen buffer until enough lines are generated to fill screen
        buffer_counter--;
        if (buffer_counter<0)
        {
            //Wrap index - buffer is circular
            buffer_counter=CMD_BUFFER_SIZE-1;
        }

        if (console->text[buffer_counter].character=='\n')
        {
            //Newline character - calculate number of lines generated by text on this line
            line_count++;
            buffer_start-=line_length%console_width;
            int line_length_copy=line_length;
            line_length=0;
            if (line_count==console_height)
            {
                //Found enough lines of text to fill the screen - stop looping
                break;
            }
            int new_lines=line_length_copy/console_width;
            if (line_count+new_lines<console_height)
            {
                //Add remaining lines to output
                buffer_start-=new_lines*console_width;
                buffer_start--;
                line_count+=new_lines;
            }
            else
            {
                //More than enough lines found so only add enough to fill the screen
                new_lines=console_height-line_count;
                buffer_start-=new_lines*console_width;
                line_count+=new_lines;
                break;
            }
        }
        else
        {
            //Character other than newline in buffer. Just count then make adjustment later.
            line_length++;
        }
    }
    
    if (line_length>0)
    {
        //Process characters left over from searching output buffer
        if (line_count<console_height)
        {
            //Still room left on screen for more lines
            if ((console->overflow_count+line_length)%console_width!=0)
            {
                //Align text accounting for characters that have scrolled out of the buffer
                buffer_start-=(console->overflow_count+line_length)%console_width;
                line_count++;
            }
        }
        int new_lines=line_length/console_width;
        if (line_count+new_lines<console_height)
        {
            //Add more lines if room left
            buffer_start-=new_lines*console_width;
        }
        else
        {
            //More than enough lines left. Add enough to fill screen.
            new_lines=console_height-line_count;
            buffer_start-=new_lines*console_width;
        }
    }

    bool draw_once=false;
    while (buffer_start<0)
    {
        //Code above starts at end of output and moves buffer_start back until it finds where to start
        //to output the correct number of characters. Screen buffer is circular so buffer_start may
        //become negative. It seems that adding CMD_BUFFER_SIZE once would account for all cases of
        //wrapping but looping here in case once isn't enough.
        buffer_start+=CMD_BUFFER_SIZE;
        //Make sure loop below draws a character at least once since buffer_start may be equal to
        //-CMD_BUFFER_SIZE then becomes 0 with line above which signals no more characters whereas
        //exactly CMD_BUFFER_SIZE characters should be drawn.
        draw_once=true;
    }

    //Draw screen output
    struct point text_pos={console_x,console_y};
    int blank_count=0;
    int row=0,col=0;
    bool input_drawn=false;
    while(row<console_height-1)
    {
        if ((blank_count>0)||((buffer_start==console->buffer_index)&&(draw_once==false)))
        {
            //Draw blanks if no more text
            text_pos=draw_char(' ',text_pos,CMD_COL_FG,CMD_COL_BG,false,FONT_5x8);
            if (blank_count>0) blank_count--;
        }
        else
        {
            char character=console->text[buffer_start].character;
            if (character=='\n')
            {
                //Newline character - fill rest of line with blanks
                blank_count=console_width-col;
                //Draw one character less so no blank character for newline
                col--;
            }
            else
            {
                //Draw character
                color_t fg=console->text[buffer_start].fg;
                color_t bg=console->text[buffer_start].bg;
                text_pos=draw_char(character,text_pos,fg,bg,false,FONT_5x8);
            }

            //Advance to next character in buffer
            buffer_start++;
            if (buffer_start==CMD_BUFFER_SIZE) buffer_start=0;
            draw_once=false;
        }

        //Advance to next character on screen
        col++;
        if (col==console_width)
        {
            //Reached end of line on screen - go to next line
            col=0;
            row++;
            text_pos.x=console_x;
            text_pos.y+=CMD_ROW_HEIGHT;
            if ((buffer_start==console->buffer_index)&&(input_drawn==false))
            {
                //Draw input line
                draw_input_line(console,text_pos,console_width,input_height);
                text_pos.y+=CMD_ROW_HEIGHT*input_height;
                input_drawn=true;
            }
        }
    }
}
static void reset_console(struct ConsoleInfo *console)
{
    console->overflow_count=0;
    console->buffer_index=0;
    console->text_len=0;
    console->input.text[0].character=0;
    console->input.start=0;
    console->input.cursor=0;
    console->input.len=0;
}

static void add_history(struct ConsoleInfo *console)
{
    console->history[console->history_index]=console->input;
    console->history_index++;
    if (console->history_index==CMD_HIST_COUNT)
        console->history_index=0;
    if (console->history_count<CMD_HIST_COUNT)
        console->history_count++;
}

static void copy_console_text(struct ConsoleInput *input,char *input_buffer,int offset)
{
    //Copy all characters excluding color data
    for (int i=offset;i<CMD_INPUT_MAX;i++)
        input_buffer[i-offset]=input->text[i].character;

    //Loop above copies 0 terminator but add here just in case
    input_buffer[CMD_INPUT_MAX-1]=0;
}

static void console_nerror(const char *text,int text_len,struct ConsoleInfo *console)
{
    for (int i=0;i<text_len;i++)
        console_char(text[i],CMD_COL_ERR_FG,CMD_COL_ERR_BG,console);
}

static int add_path(const char *path, const char *addition, char *result)
{
    if (addition[0]=='/')
    {
        //Directory is absolute
        if (strlen(addition)>CMD_PATH_MAX-1)
        {
            return CMD_ERROR_PATH_TOO_LONG;
        }
        else
        {
            strcpy(result,addition);
        }
    }
    else
    {
        //Directory is relative
        //-2 for terminating 0 and added / between directories
        if (strlen(path)+strlen(addition)>CMD_PATH_MAX-2)
        {
            return CMD_ERROR_PATH_TOO_LONG;
        }
        strcpy(result,path);
        int path_len=strlen(result);
        strcpy(result+path_len,"/");
        path_len+=strlen("/");
        strcpy(result+path_len,addition);
    }

    return CMD_ERROR_NONE;
}

static int create_path(const char *path, const char *addition, char *result)
{

    int result_code=add_path(path,addition,result);
    if (result_code!=CMD_ERROR_NONE)
    {
        return result_code;
    }

    char *normal_path=fs_path_normalize(result);
    if (normal_path==NULL)
    {
        return CMD_ERROR_NORMALIZE_PATH;
    }
    strcpy(result,normal_path);
    free(normal_path);

    return CMD_ERROR_NONE;
}

static void command_error(const char *command,int error,struct ConsoleInfo *console)
{
    console_text(command,CMD_COL_ERR_FG,CMD_COL_ERR_BG,console);
    console_text(": ",CMD_COL_ERR_FG,CMD_COL_ERR_BG,console);

    const char *error_msg=NULL;

    switch (error)
    {
        case CMD_ERROR_PATH_TOO_LONG:
            error_msg="path too long\n";
            break;
        case CMD_ERROR_NORMALIZE_PATH:
            error_msg="could not normalize path\n";
            break;
        case CMD_ERROR_PATH_NOT_FOUND:
            error_msg="path not found\n";
            break;
        case CMD_ERROR_CANT_ACCESS:
            error_msg="cannot access file/directory\n";
            break;
        case CMD_ERROR_ARG_COUNT:
            error_msg="wrong number of arguments\n";
            break;
        case CMD_ERROR_ARG_MEM:
            //Triggered before any command run so doesn't have xxx: beginning so should be upper case
            error_msg="Out of argument memory\n";
            break;
        case CMD_ERROR_NOT_FOUND:
            error_msg="command not found\n";
            break;
        case CMD_ERROR_NOT_DIRECTORY:
            error_msg="not a directory\n";
            break;
        default:
            error_msg="unknown\n";
    }
    console_text(error_msg,CMD_COL_ERR_FG,CMD_COL_ERR_BG,console);
}

static struct CommandInfo
{
    const char *name;
    const int command;
    const int arg_count;
}commands[]=
{
    {"exit",    CMD_CMD_EXIT,   0},
    {"cd",      CMD_CMD_CD,     -1},
    {"ls",      CMD_CMD_LS,     -1},
    {"ll",      CMD_CMD_LL,     -1},
    {"test",    CMD_CMD_TEST,   0}
};

#define COMMANDS_SIZE ((int)(sizeof(commands)/sizeof(commands[0])))

static color_t file_color(const char *path, int file_type)
{
    const char *exec_endings[]=
    {
        ".f"
    };

    switch (file_type)
    {
        case FILE_TYPE_DIR:
            return CMD_COL_DIR;
        case FILE_TYPE_REG:
            //Check if any files end in executable ending
            int path_len=strlen(path);
            for (int i=0;i<(sizeof(exec_endings)/sizeof(exec_endings[0]));i++)
            {
                //Skip ending if larger than path
                int ending_len=strlen(exec_endings[i]);
                if (path_len<ending_len) continue;

                //Compare ending to ending of file in path
                bool found=true;
                for (int j=0;j<ending_len;j++)
                {
                    if (exec_endings[i][j]!=path[path_len-ending_len+j])
                    {
                        //Found mistmatched character - not a match
                        found=false;
                        break;
                    }
                }

                //Last ending was a match - file name is executable
                if (found) return CMD_COL_EXEC;
            }
            return CMD_COL_FILE;
        case FILE_TYPE_UNKNOWN:
            return CMD_COL_UNKNOWN;
        default:
            return CMD_COL_UNKNOWN;
    }
}

static int path_type(const char *path, int *result)
{
    //Fetch info on path
    struct stat stat_buffer;
    if (stat(path,&stat_buffer)) return CMD_ERROR_CANT_ACCESS;

    //Determine whether target path is to file or directory
    switch (stat_buffer.st_mode&S_IFMT)
    {
        case S_IFDIR:
            //Directory
            *result=FILE_TYPE_DIR;
            break;
        case S_IFREG:
            //Normal file
            *result=FILE_TYPE_REG;
            break;
        default:
            *result-FILE_TYPE_UNKNOWN;
    }
    return CMD_ERROR_NONE;
}

int console_strlen(struct ConsoleChar *text)
{
    int size=0;
    while(text->character)
    {
        text++;
        size++;
    }
    return size;
}

static int process_input(char *input_buffer,struct ConsoleInfo *console)
{
    struct Parse
    {
        int start,len;
    } args[CMD_ARG_MAX];

    int parse_state=CMD_PARSE_NONE;
    int arg_index=0;
    int text_index=0;
    int arg_count=0;

    for (int i=0;i<CMD_ARG_MAX;i++)
        args[i].len=0;

    while(input_buffer[text_index])
    {
        if (input_buffer[text_index]==' ')
        {
            if (parse_state==CMD_PARSE_WORD)
            {
                parse_state=CMD_PARSE_NONE;
                arg_index++;
            }
        }
        else
        {
            if (parse_state==CMD_PARSE_NONE) 
            {
                if (arg_index>=CMD_ARG_MAX)
                {
                    command_error(NULL,CMD_ERROR_ARG_MEM,console);
                    return COMMAND_NONE;
                }
                args[arg_index].start=text_index;
                args[arg_index].len=1;
                parse_state=CMD_PARSE_WORD;
            }
            else if (parse_state==CMD_PARSE_WORD) 
            {
                args[arg_index].len++;
            }
        }
        text_index++;
    }

    //Count number of arguments
    for (int i=0;i<CMD_ARG_MAX;i++)
    {
        if (args[i].len>0)
            arg_count++;
        else break;
    }

    //Nothing to process - return
    if (arg_count==0) return COMMAND_NONE;

    //Match to commands
    int command_id=CMD_CMD_NONE;
    for (int i=0;i<COMMANDS_SIZE;i++)
    {
        bool command_found=true;
        int j;
        for (j=0;j<args[0].len;j++)
        {
            if (input_buffer[args[0].start+j]!=commands[i].name[j])
            {
                command_found=false;
                break;
            }
        }
        if (commands[i].name[j]!=0)
        {
            //Make sure command ends in 0 and not just matching on first letters
            command_found=false;
        }

        if (command_found==true)
        {
            //If command doesn't have unlimited arguments
            if (commands[i].arg_count!=-1)
            {
                if (commands[i].arg_count!=arg_count-1)
                {
                    command_error(commands[i].name,CMD_ERROR_ARG_COUNT,console);
                    return COMMAND_NONE;
                }
            }
            command_id=commands[i].command;
            break;
        }
    }

    char human_buffer[TEXT_INT32_SIZE];

    switch (command_id)
    {
        case CMD_CMD_NONE:
            char command_name[CMD_PATH_MAX];
            strncpy(command_name,input_buffer+args[0].start,args[0].len);
            command_name[args[0].len]=0;
            command_error(command_name,CMD_ERROR_NOT_FOUND,console);
            break;
        case CMD_CMD_EXIT:
            return COMMAND_EXIT;
        case CMD_CMD_CD:
            //Anonymous block - reuse variable names
            {
                if (arg_count==1)
                {
                    //No arguments - "cd" is first argument. Change path to root.
                    strcpy(console->path,"/");
                }
                else if (arg_count==2)
                {
                    //One argument - use argument as path

                    //Normalize path
                    char arg_path[CMD_PATH_MAX];
                    char new_path[CMD_PATH_MAX];
                    strncpy(arg_path,input_buffer+args[1].start,args[1].len+1);
                    int result=create_path(console->path,arg_path,new_path);
                    if (result!=CMD_ERROR_NONE)
                    {
                        command_error("cd",result,console);
                        break;
                    }

                    //Fetch info on path
                    struct stat stat_buffer;
                    if (stat(new_path,&stat_buffer))
                    {
                        command_error("cd",CMD_ERROR_PATH_NOT_FOUND,console); 
                        break;
                    }

                    //Make sure target path is directory
                    if ((stat_buffer.st_mode&S_IFMT)!=S_IFDIR)
                    {
                        command_error("cd",CMD_ERROR_NOT_DIRECTORY,console); 
                        break;
                    }

                    //Set current path to new path 
                    strcpy(console->path,new_path);
                }
                else
                {
                    //Either one argument or no arguments allowed
                    command_error("cd",CMD_ERROR_ARG_COUNT,console);
                    break;
                }
                break;
            }
        case CMD_CMD_LL:
        case CMD_CMD_LS:
            //Anonymous block - reuse variable names between cases
            {
                const char *command_name;
                if (command_id==CMD_CMD_LL) command_name="ll";
                else command_name="ls";

                color_t color_fg;
                int file_type;
                char new_path[CMD_PATH_MAX];
                if (arg_count==1)
                {
                    //No arguments - first argument is "ll"/"ls" itself. Use path as directory.
                    strcpy(new_path,console->path);
                    file_type=FILE_TYPE_DIR;
                }
                else if (arg_count==2)
                {
                    //One argument - use argument as path
                    char arg_path[CMD_PATH_MAX];
                    strncpy(arg_path,input_buffer+args[1].start,args[1].len+1);

                    //Add argument to current path if partial or use argument as path if full
                    int result=add_path(console->path,arg_path,new_path);
                    if (result!=CMD_ERROR_NONE)
                    {
                        command_error(command_name,result,console);
                        break;
                    }

                    //Fetch info on path
                    strncpy(arg_path,input_buffer+args[1].start,args[1].len+1);
                    result=path_type(new_path,&file_type);
                    if (result!=CMD_ERROR_NONE)
                    {
                        command_error(command_name,result,console); 
                        break;
                    }
                }
                else
                {
                    //Only one argument or no arguments allowed
                    command_error(command_name,CMD_ERROR_ARG_COUNT,console);
                    break;
                }

                if (file_type==FILE_TYPE_DIR)
                {
                    //Target path is directory - show contents
                    DIR *directory=opendir(new_path);
                    if (directory==NULL)
                    {
                        command_error(command_name,CMD_ERROR_CANT_ACCESS,console);
                        break;
                    }

                    //Print all files and directories
                    struct dirent *dir;
                    int print_width=0;
                    bool file_printed=false;
                    while ((dir=readdir(directory)))
                    {
                        //Don't print . or ..
                        if (strcmp(dir->d_name,".")&&strcmp(dir->d_name,".."))
                        {
                            //Color code output
                            if (dir->d_type==DT_DIR)        file_type=FILE_TYPE_DIR;
                            else if (dir->d_type==DT_REG)   file_type=FILE_TYPE_REG;
                            else                            file_type=FILE_TYPE_UNKNOWN;
                            color_fg=file_color(dir->d_name,file_type);

                            if (command_id==CMD_CMD_LS)
                            {
                                //ls - print filename and prevent name from wrapping at screen edge
                                if (file_printed)
                                {
                                    if (print_width+strlen(CMD_LS_SEPARATOR)>=CMD_WHOLE_WIDTH)
                                    {
                                        console_text_default("\n",console);
                                        print_width=0;
                                    }
                                    else
                                    {
                                        console_text_default(CMD_LS_SEPARATOR,console);
                                        print_width+=strlen(CMD_LS_SEPARATOR);
                                    }
                                }

                                console_text(dir->d_name,color_fg,CMD_COL_BG,console);
                                print_width+=strlen(dir->d_name);
                                file_printed=true;
                            }
                            else if (command_id==CMD_CMD_LL)
                            {
                                //TODO
                                /*
                                if (stat(paths[i],&stat_buffer))
                                {
                                    command_error(command_name,CMD_ERROR_CANT_ACCESS,console);
                                    console_
                                    break;
                                }
                                */

                                if (strlen(dir->d_name)>CMD_LL_WIDTH)
                                {
                                    //Screen not wide enough for filename and size so print size without alignment
                                    console_text_default(" ",console);
                                    console_text_default("\n",console);
                                }
                            }

                        }

                    }
                    console_text_default("\n",console);
                    closedir(directory);
                }
                else
                {
                    //Target path points to file - print name
                    char *basename=strrchr(new_path,'/');
                    if (basename==NULL)
                    {
                        //Forward slash not found in path - should never happen but just in case
                        command_error(command_name,CMD_ERROR_CANT_ACCESS,console);
                        break;
                    }

                    //Skip preceding /
                    basename++;
                    
                    //Print name depending on type - file_type set above after stat
                    color_fg=file_color(basename,file_type);
                    console_text(basename,color_fg,CMD_COL_BG,console);
                    console_text_default("\n",console);
                }
                break;
            }
        case CMD_CMD_TEST:
            console_text_default("Test\n",console);

            const char *paths[]=
            {
                "/home/druzyek/temp",
                "/home/druzyek/temp/test.txt",
                "/home/druzyek/temp/test2k.txt",
                "/ROBOTS",
                "/ROBOTS/main.py"
            };
            for (int i=0;i<5;i++)
            {
                console_text_default(paths[i],console);
                struct stat stat_buffer;
                if (stat(paths[i],&stat_buffer))
                    console_text_default(" - stat error\n",console);
                else
                {
                    console_text_default(" - no stat error!\n",console);

                    console_text_default("- size: ",console);
                    text_int32_human(stat_buffer.st_size,human_buffer);
                    console_text_default(human_buffer,console);
                    console_text_default("\n",console);

                    console_text_default("- type: ",console);
                    text_int32(stat_buffer.st_mode & S_IFMT,human_buffer);
                    console_text_default(human_buffer,console);
                    console_text_default("\n",console);
                }
            }
            break;
        default:
            //TODO: remove - should never reach here
            console_ntext(input_buffer+args[0].start,args[0].len,CMD_COL_FG,CMD_COL_BG,console);
            console_text_default(": command found",console);
            console_text_default("\n",console);
            return COMMAND_NONE;
    }
    return COMMAND_NONE;
}

int command_line(int command_ID, struct WindowInfo *windows, int selected_window)
{
    struct WindowInfo window=windows[selected_window];
    int width=window_width(window);
    int height=window_height(window);
    struct point pos;
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

    //Heap memory
    select_heap(window.tab_index,drawn_split);
    uint8_t *heap_ptr=get_split_heap();
    struct ConsoleInfo *console;

    if (command_ID==COMMAND_START) 
    {
        //Start - allocate memory for and initialize console
        console=(struct ConsoleInfo *)add_object(sizeof(struct ConsoleInfo),heap_ptr);

        //TODO: check if allocation succeeded

        //Init console
        reset_console(console);

        //Init input
        console_text_default("Calculator shell for fx-CG50\nType 'help' for more info.\n",console);
        console->reset_input=true;
        console->modifier=MODIFIER_ALPHA_LOWER_LOCK;
        console->input_copied=false;

        //Init history
        for (int i=0;i<CMD_HIST_COUNT;i++)
        {
            console->history[i].text[0].character=0;
            console->history[i].len=0;
        }
        console->history_index=0;
        console->history_count=0;

        //Init file system path
        strcpy(console->path,"/");
    }
    else
    {
        //Resume or Redraw - reuse existing memory for console
        console=(struct ConsoleInfo *)object_address(CMD_ID_CONSOLE,heap_ptr);
    }

    //Redraw screen but only spare pixels on edges. Letters redrawn below.
    draw_rect(pos.x,pos.y,width,height,CMD_COL_BG,CMD_COL_BG);

    //Set coordinates, width, and height based on window state
    int console_width,console_x;
    if (window.split_state==WINDOW_HSPLIT)
    {
        //Split horizontally - half width
        console_x=pos.x+CMD_HALF_X;
        console_width=CMD_HALF_WIDTH;
    }
    else
    {
        //Whole screen or split vertically - full width
        console_x=pos.x+CMD_WHOLE_X;
        console_width=CMD_WHOLE_WIDTH;
    }
    
    int console_height,console_y;
    if (window.split_state==WINDOW_VSPLIT)
    {
        //Split vertically - half height
        console_y=pos.y+CMD_HALF_Y;
        console_height=CMD_HALF_HEIGHT;
    }
    else
    {
        //Whole screen or split horizontally - full height
        console_y=pos.y+CMD_WHOLE_Y;
        console_height=CMD_WHOLE_HEIGHT;
    }

    //Main loop
    bool redraw_screen=true;
    bool redraw_modifier=true;
    bool redraw_input=true;
    while (1)
    {
        //Set text for input line
        if (console->reset_input)
        {
            console->input.text[0].character=0;
            console->input.start=0;
            console->input.cursor=0;
            console->input.len=0;
            add_input_text("CG50",CMD_COL_HOST,CMD_COL_BG,true,console);
            add_input_char(':',CMD_COL_FG,CMD_COL_BG,true,console);
            add_input_text(console->path,CMD_COL_DIR,CMD_COL_BG,true,console);
            add_input_char(' ',CMD_COL_FG,CMD_COL_BG,true,console);
            console->input_copied=false;
        }
        console->reset_input=false;

        //Redraw modifiers (shift, alpha) as necessary even if rest of screen not redrawn
        if (redraw_modifier) draw_modifier(console->modifier);

        if (redraw_screen)
        {
            //Always redraw screen whether START, RESUME, or REDRAW
            draw_console(console,console_x,console_y,console_width,console_height);
                
            //Return if Redraw only
            if (command_ID==COMMAND_REDRAW) return COMMAND_DONE;
        }

        //TODO
        //if (redraw_input)

        //Copy updates to screen if modifier keys or text have changed
        if ((redraw_screen)||(redraw_modifier)||(redraw_input)) dupdate();
        redraw_screen=true;
        
        //Get key
        int old_modifier=console->modifier;
        int key=getkey_text(true,&console->modifier);

        //Redraw modifiers (shift, alpha) next time through if they have changed
        if (old_modifier!=console->modifier) redraw_modifier=true;
        else redraw_modifier=false;

        //Look for keys before sys_key_handler below in case need to handle any sys_keys differently
        char character=vkey_printable[key];
        if (character!=0)
        {
            //Printable character - add to input line
            add_input_char(character,CMD_COL_FG,CMD_COL_BG,false,console);
        }
        else
        {
            switch (key)
            {
                case VKEY_QUIT:
                    //shift+EXIT
                    return COMMAND_EXIT;
                    break;
                case VKEY_EXIT:
                    //Clear line but do not exit program
                    //Handle here so not picked up by sys_key_handler below which would exit program
                    if (console->input.len==console->input.start)
                    {
                        //No input on line - don't cancel
                        break;
                    }
                    
                    //Append ^C to show input cancelled
                    const char *cancel_text="^C";
                    if (console->input.len>=CMD_INPUT_MAX-(int)strlen(cancel_text))
                    {
                        //Not enough room to append ^C so drop characters from end of input to make room
                        console->input.len=CMD_INPUT_MAX-strlen(cancel_text)-1;
                        console->input.cursor=CMD_INPUT_MAX-strlen(cancel_text)-1;
                    }
                    add_input_text(cancel_text,CMD_COL_FG,CMD_COL_BG,false,console);

                    //Fallthrough
                case VKEY_EXE:
                    //Copy input text to console
                    for (int i=0;i<console->input.len;i++)
                    {
                        console_char(console->input.text[i].character,console->input.text[i].fg,console->input.text[i].bg,console);
                    }
                    console_char('\n',0,0,console);
                    console->reset_input=true;

                    //Process input if EXE pressed (just copy input if ESC)
                    if (key==VKEY_EXE)
                    {
                        //Add input to history
                        add_history(console);
                        
                        //Process input
                        char input_buffer[CMD_INPUT_MAX];
                        copy_console_text(&console->input,input_buffer,console->input.start);
                        int return_code=process_input(input_buffer,console);
                        if (return_code!=COMMAND_NONE)
                            return return_code;
                    }
                    break;
                case VKEY_UP:
                    if (console->history_count>0)
                    {
                        //Scroll up in history if there are history lines
                        if (console->input_copied==false)
                        {
                            //First time up pressed - save current input
                            console->input_copy=console->input;
                            console->input_copied=true;
                            console->history_read_count=console->history_count;
                        }

                        if (console->history_read_count>0)
                        {
                            //Items left to scroll back to
                            if (console->history_count==console->history_read_count)
                            {
                                //Current line edited is copy of input when up was pressed meaning input
                                //scrolled up then back to original input. Save that input including changes
                                //in case scroll back to that.
                                console->input_copy=console->input;
                            }

                            //Scroll up one line and copy line from history to input
                            console->history_read_count--;
                            int read_index=console->history_index;
                            read_index-=console->history_count;
                            read_index+=console->history_read_count;
                            if (read_index<0) read_index+=CMD_HIST_COUNT;
                            console->input=console->history[read_index];
                        }
                    }
                    break;
                case VKEY_DOWN:
                    if (console->input_copied)
                    {
                        //Only scroll down in history if previously scrolled up
                        if (console->history_read_count==console->history_count)
                        {
                            //Already scrolled all the way down - nothing to do
                            break;
                        }
                        
                        //Advance to next history line
                        console->history_read_count++;
                        if (console->history_read_count==console->history_count)
                        {
                            //Advanced past last line so use copy of original input from before
                            //scrolling up. This way, scrolling up, scrolling down, modifying 
                            //original input then scrolling up then back down to original input
                            //doesn't lose changes.
                            console->input=console->input_copy;    
                        }
                        else
                        {
                            //Copy line from history to input
                            int read_index=console->history_index;
                            read_index-=console->history_count;
                            read_index+=console->history_read_count;
                            if (read_index<0) read_index+=CMD_HIST_COUNT;
                            console->input=console->history[read_index];
                        }
                    }
                    break;
                case VKEY_LEFT:
                    if (console->input.cursor>console->input.start)
                        console->input.cursor--; 
                    break;
                case VKEY_RIGHT:
                    if (console->input.cursor<console->input.len)
                        console->input.cursor++;
                    break;
                case VKEY_SHIFT_LEFT:
                    console->input.cursor=console->input.start;
                    break;
                case VKEY_SHIFT_RIGHT:
                    console->input.cursor=console_strlen(console->input.text);
                    break;
                case VKEY_UNDO:
                    //DEL with alpha active - treat as DEL so don't need to remove alpha to delete
                    //Fallthrough!
                case VKEY_DEL:
                    if (console->input.cursor>console->input.start)
                    {
                        console->input.cursor--;
                        for (int i=console->input.cursor;i<console->input.len;i++)
                        {
                            console->input.text[i]=console->input.text[i+1];
                        }
                        console->input.len--;
                    }
                    break;
                default:
                    //Check for sys_keys like MENU, OFF, etc
                    int return_command=sys_key_handler(key);
                    if (return_command!=COMMAND_NONE)
                    {
                        //System key - return to window manager to handle key
                        return return_command;
                    }
                    else
                    {
                        //No key found - don't redraw screen
                        redraw_screen=false;
                    }
            }
        }
    }

    //Shouldn't reach here - added to silence warning
    return COMMAND_DONE;
}

