#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include "compatibility.h"
#include "error.h"
#include "getkey.h"
#include "graphics.h"
#include "text.h"
#include "manager.h"
#include "mem.h"
#include "shell.h"
#include "structs.h"

//Functions
static int add_path(const char *path, const char *addition, char *result)
{
    if (addition[0]=='/')
    {
        //Directory is absolute
        if (strlen(addition)>SHELL_PATH_MAX-1)
        {
            return SHELL_ERROR_PATH_TOO_LONG;
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
        if (strlen(path)+strlen(addition)>SHELL_PATH_MAX-2)
        {
            return SHELL_ERROR_PATH_TOO_LONG;
        }
        strcpy(result,path);
        int path_len=strlen(result);
        strcpy(result+path_len,"/");
        path_len+=strlen("/");
        strcpy(result+path_len,addition);
    }

    return SHELL_ERROR_NONE;
}

static int create_path(const char *path, const char *addition, char *result)
{
    int result_code=add_path(path,addition,result);
    if (result_code!=SHELL_ERROR_NONE)
    {
        return result_code;
    }

    char *normal_path=wrapper_normalize_path(result,SHELL_PATH_MAX);
    if (normal_path==NULL)
    {
        return SHELL_ERROR_NORMALIZE_PATH;
    }
    strcpy(result,normal_path);
    free(normal_path);

    return SHELL_ERROR_NONE;
}

static void command_error(const char *command,int error,struct ConsoleInfo *console)
{
    console_text(command,SHELL_COL_ERR_FG,SHELL_COL_ERR_BG,console);
    console_text(": ",SHELL_COL_ERR_FG,SHELL_COL_ERR_BG,console);

    const char *error_msg=NULL;

    switch (error)
    {
        case SHELL_ERROR_PATH_TOO_LONG:
            error_msg="path too long\n";
            break;
        case SHELL_ERROR_NORMALIZE_PATH:
            error_msg="could not normalize path\n";
            break;
        case SHELL_ERROR_PATH_NOT_FOUND:
            error_msg="path not found\n";
            break;
        case SHELL_ERROR_CANT_ACCESS:
            error_msg="cannot access file/directory\n";
            break;
        case SHELL_ERROR_ARG_COUNT:
            error_msg="wrong number of arguments\n";
            break;
        case SHELL_ERROR_ARG_MEM:
            //Triggered before any command run so doesn't have xxx: beginning so should be upper case
            error_msg="Out of argument memory\n";
            break;
        case SHELL_ERROR_NOT_FOUND:
            error_msg="command not found\n";
            break;
        case SHELL_ERROR_NOT_DIRECTORY:
            error_msg="not a directory\n";
            break;
        case SHELL_ERROR_TARGET_FILE:
            error_msg="target must be file\n";
            break;
        case SHELL_ERROR_TARGET_DIR:
            error_msg="target must be directory\n";
            break;
        case SHELL_ERROR_CP_SOURCE_NOT_FILE:
            error_msg="source must be file\n";
            break;
        case SHELL_ERROR_CP_DEST_EXISTS:
            error_msg="destination exists - delete before copying\n";
            break;
        case SHELL_ERROR_CP_SOURCE:
            error_msg="cannot open source file\n";
            break;
        case SHELL_ERROR_CP_DEST:
            error_msg="cannot open destination file\n";
            break;
        case SHELL_ERROR_CP_COPYING:
            error_msg="error occurred while copying\n";
            break;
        case SHELL_ERROR_CANT_ACCESS_SOURCE:
            error_msg="cannot access source file\n";
            break;
        case SHELL_ERROR_CANT_ACCESS_DEST:
            error_msg="cannot access destination file\n";
            break;
        case SHELL_ERROR_READ_ONLY:
            error_msg="file is read-only\n";
            break;
        case SHELL_ERROR_MKDIR_FILE:
            error_msg="file already exists\n";
            break;
        case SHELL_ERROR_MKDIR_DIR:
            error_msg="directory already exists\n";
            break;
        case SHELL_ERROR_MKDIR:
            error_msg="failed to create directory\n";
            break;
        case SHELL_ERROR_PATH_INVALID:
            error_msg="invalid character in destination path\n";
            break;
        case SHELL_ERROR_MV_DEST_EXISTS:
            error_msg="destination exists - delete before moving\n";
            break;
        case SHELL_ERROR_MV:
            error_msg="failed to move file\n";
            break;
        case SHELL_ERROR_TOUCH:
            error_msg="failed to create file\n";
            break;
        default:
            error_msg="unknown error\n";
    }
    console_text(error_msg,SHELL_COL_ERR_FG,SHELL_COL_ERR_BG,console);
}

static struct CommandInfo
{
    const char *name;
    const int command;
    const int arg_count;
    const char *help_string;
}commands[]=
{
    {"cat",     SHELL_CMD_CAT,    1,  "output contents of file"},
    {"cd",      SHELL_CMD_CD,     -1, "change directory"},
    {"clear",   SHELL_CMD_CLEAR,  0,  "clear the console screen"},
    {"cp",      SHELL_CMD_CP,     2,  "copy file"},
    {"exit",    SHELL_CMD_EXIT,   0,  "exit command line"},
    {"help",    SHELL_CMD_HELP,   -1, "display help on commands"},
    {"ll",      SHELL_CMD_LL,     -1, "list directory contents and sizes"},
    {"ls",      SHELL_CMD_LS,     -1, "list directory contents"},
    {"mkdir",   SHELL_CMD_MKDIR,  1,  "create directory"},
    {"mv",      SHELL_CMD_MV,     2,  "move file or directory"},
    {"rm",      SHELL_CMD_RM,     1,  "remove file"},
    {"rmdir",   SHELL_CMD_RMDIR,  1,  "remove directory"},
    {"touch",   SHELL_CMD_TOUCH,  1,  "create file if it doesn't exist"},
};

static int file_special(const char *path)
{
    struct FileEndings
    {
        const char *text;
        const int type;
    } endings[]=
    {
        {".f",      FILE_SPECIAL_EXEC},
        {".g3a",    FILE_SPECIAL_RO}
    };

    int path_len=strlen(path);
    for (int i=0;i<ARRAY_SIZE(endings);i++)
    {
        //Skip ending if larger than path
        int ending_len=strlen(endings[i].text);
        if (path_len<ending_len) continue;

        //Compare ending to ending of file in path
        bool found=true;
        for (int j=0;j<ending_len;j++)
        {
            if (endings[i].text[j]!=path[path_len-ending_len+j])
            {
                //Found mistmatched character - not a match
                found=false;
                break;
            }
        }

        //Last ending was a match - return special type
        if (found) return endings[i].type;
    }

    //No matches found
    return FILE_SPECIAL_NONE;
}

static color_t file_color(const char *path, int file_type)
{
    switch (file_type)
    {
        case FILE_TYPE_DIR:
            return SHELL_COL_DIR;
        case FILE_TYPE_REG:
            //Check if any files have special status
            int special=file_special(path);
            if (special==FILE_SPECIAL_EXEC)     return SHELL_COL_EXEC;
            else if (special==FILE_SPECIAL_RO)  return SHELL_COL_RO;
            else                                return SHELL_COL_FILE;
        case FILE_TYPE_UNKNOWN:
            return SHELL_COL_UNKNOWN;
        default:
            return SHELL_COL_UNKNOWN;
    }
}

static bool path_valid(const char *path)
{
    const char *allowed_chars="/-_.0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while (*path)
    {
        if (strchr(allowed_chars,*path)==NULL) return false;
        path++;
    }
    return true;
}

static int path_type(const char *path, int *result)
{
    //Exception - can't fetch info on path if root directory on calculator. Handle manually.
    if (!strcmp(path,"/"))
    {
        *result=FILE_TYPE_DIR;
        return SHELL_ERROR_NONE;
    }

    //Fetch info on path
    struct stat stat_buffer;
    if (stat(path,&stat_buffer)) return SHELL_ERROR_CANT_ACCESS;

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
            *result=FILE_TYPE_UNKNOWN;
    }
    return SHELL_ERROR_NONE;
}

static void show_help(const char *command,struct ConsoleInfo *console)
{
    bool command_found=false;
    for (int i=0;i<ARRAY_SIZE(commands);i++)
    {
        //Print help string if it matches search command or if search command is NULL (ie show all)
        bool print_help;
        if (command==NULL) print_help=true;
        else if (!strcmp(command,commands[i].name)) print_help=true;
        else print_help=false;
        if (print_help)
        {
            console_text_default(commands[i].name,console);
            console_text_default(" - ",console);
            console_text_default(commands[i].help_string,console);
            console_text_default("\n",console);
            command_found=true;
        }
    }
    if (command_found==false)
    {
        if (command!=NULL)
            command_error(command,SHELL_ERROR_NOT_FOUND,console);
    }
}

//IMPORTANT! - called on calculator with gint_world_switch so don't call gint functions (dupate, dclear, etc) or will crash!
static int process_input(void *struct_args)
{
    struct Parse
    {
        int start,len;
    } args[SHELL_ARG_MAX];

    //Arguments must be passed as void pointer to struct on calculator for this function
    struct ProcessInput *temp_args=struct_args;
    const char *input_buffer=temp_args->input_buffer;
    struct ConsoleInfo *console=temp_args->console;
    char *shell_path=temp_args->path;

    int parse_state=SHELL_PARSE_NONE;
    int arg_index=0;
    int text_index=0;
    int arg_count=0;

    for (int i=0;i<SHELL_ARG_MAX;i++)
        args[i].len=0;

    while(input_buffer[text_index])
    {
        if (input_buffer[text_index]==' ')
        {
            if (parse_state==SHELL_PARSE_WORD)
            {
                parse_state=SHELL_PARSE_NONE;
                arg_index++;
            }
        }
        else
        {
            if (parse_state==SHELL_PARSE_NONE) 
            {
                if (arg_index>=SHELL_ARG_MAX)
                {
                    command_error(NULL,SHELL_ERROR_ARG_MEM,console);
                    return COMMAND_NONE;
                }
                args[arg_index].start=text_index;
                args[arg_index].len=1;
                parse_state=SHELL_PARSE_WORD;
            }
            else if (parse_state==SHELL_PARSE_WORD) 
            {
                args[arg_index].len++;
            }
        }
        text_index++;
    }

    //Count number of arguments
    for (int i=0;i<SHELL_ARG_MAX;i++)
    {
        if (args[i].len>0)
            arg_count++;
        else break;
    }

    //Nothing to process - return
    if (arg_count==0) return COMMAND_NONE;

    //Match to commands
    int command_id=SHELL_CMD_NONE;
    for (int i=0;i<ARRAY_SIZE(commands);i++)
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
                    command_error(commands[i].name,SHELL_ERROR_ARG_COUNT,console);
                    return COMMAND_NONE;
                }
            }
            command_id=commands[i].command;
            break;
        }
    }

    switch (command_id)
    {
        case SHELL_CMD_NONE:
            {
                char command_name[SHELL_PATH_MAX];
                strncpy(command_name,input_buffer+args[0].start,args[0].len);
                command_name[args[0].len]=0;
                command_error(command_name,SHELL_ERROR_NOT_FOUND,console);
                break;
            }
        case SHELL_CMD_CAT:
            {
                //Command name in case of error message
                const char *command_name="cat";

                //Normalize path
                char arg_path[SHELL_PATH_MAX];
                char new_path[SHELL_PATH_MAX];
                strncpy(arg_path,input_buffer+args[1].start,args[1].len+1);
                arg_path[args[1].len]=0;
                int result=add_path(shell_path,arg_path,new_path);
                if (result!=SHELL_ERROR_NONE)
                {
                    command_error(command_name,result,console);
                    break;
                }

                //Fetch info on path
                if (path_type(new_path,&result)!=SHELL_ERROR_NONE)
                {
                    command_error(command_name,SHELL_ERROR_CANT_ACCESS,console); 
                    break;
                }

                //Make sure target path is file
                if (result!=FILE_TYPE_REG)
                {
                    command_error(command_name,SHELL_ERROR_TARGET_FILE,console); 
                    break;
                }

                //Open file
                FILE *cat_file=fopen(new_path,"r");
                if (cat_file==NULL)
                {
                    command_error(command_name,SHELL_ERROR_CANT_ACCESS,console); 
                    break;
                }

                //Read all bytes from file
                char cat_buffer[SHELL_CAT_SIZE];
                size_t byte_count;
                do
                {
                    //-1 to make room for terminating 0
                    byte_count=fread(cat_buffer,1,SHELL_CAT_SIZE-1,cat_file); 
                    if (byte_count>0)
                    {
                        cat_buffer[byte_count]=0;
                        console_text_default(cat_buffer,console);
                    }
                } while (byte_count);

                //Done reading file
                console_text_default("\n",console);
                fclose(cat_file);
                break;
            }

        case SHELL_CMD_CD:
            {
                //Command name in case of error message
                const char *command_name="cd";

                if (arg_count==1)
                {
                    //No arguments - "cd" is first argument. Change path to root.
                    strcpy(shell_path,"/");
                }
                else if (arg_count==2)
                {
                    //One argument - use argument as path

                    //Normalize path
                    char arg_path[SHELL_PATH_MAX];
                    char new_path[SHELL_PATH_MAX];
                    strncpy(arg_path,input_buffer+args[1].start,args[1].len+1);
                    arg_path[args[1].len]=0;
                    int result=create_path(shell_path,arg_path,new_path);
                    if (result!=SHELL_ERROR_NONE)
                    {
                        command_error(command_name,result,console);
                        break;
                    }

                    //Fetch info on path
                    if (path_type(new_path,&result)!=SHELL_ERROR_NONE)
                    {
                        command_error(command_name,SHELL_ERROR_CANT_ACCESS,console); 
                        break;
                    }

                    //Make sure target path is directory
                    if (result!=FILE_TYPE_DIR)
                    {
                        command_error(command_name,SHELL_ERROR_NOT_DIRECTORY,console); 
                        break;
                    }

                    //Set current path to new path 
                    strcpy(shell_path,new_path);
                }
                else
                {
                    //More than one argument not allowed
                    command_error(command_name,SHELL_ERROR_ARG_COUNT,console);
                    break;
                }
                break;
            }
        case SHELL_CMD_CLEAR:
            reset_console(console);
            console_text_default(SHELL_CONSOLE_STRING,console);
            break;
        case SHELL_CMD_CP:
            {
                //Command name in case of error message
                const char *command_name="cp";

                //Source argument
                char arg_path[SHELL_PATH_MAX];
                char src_path[SHELL_PATH_MAX];
                strncpy(arg_path,input_buffer+args[1].start,args[1].len+1);
                arg_path[args[1].len]=0;

                //Add argument to current path if partial or use argument as path if full path
                int result=add_path(shell_path,arg_path,src_path);
                if (result!=SHELL_ERROR_NONE)
                {
                    command_error(command_name,result,console);
                    break;
                }
                
                //Fetch info on source path
                int source_type;
                result=path_type(src_path,&source_type);
                if (result!=SHELL_ERROR_NONE)
                {
                    //Note error in result from path_type may be different!
                    //Substitue error code so obvious problem is with source
                    command_error(command_name,SHELL_ERROR_CANT_ACCESS_SOURCE,console); 
                    break;
                }

                //Make sure source path is file
                if (source_type!=FILE_TYPE_REG)
                {
                    command_error(command_name,SHELL_ERROR_CP_SOURCE_NOT_FILE,console); 
                    break;
                }

                //Destination argument
                char dest_path[SHELL_PATH_MAX];
                strncpy(arg_path,input_buffer+args[2].start,args[2].len+1);
                arg_path[args[2].len]=0;

                //Add argument to current path if partial or use argument as path if full path
                result=add_path(shell_path,arg_path,dest_path);
                if (result!=SHELL_ERROR_NONE)
                {
                    command_error(command_name,result,console);
                    break;
                }
                
                //Fetch info on destination path
                int dest_type;
                result=path_type(dest_path,&dest_type);
                if (result==SHELL_ERROR_NONE)
                {
                    //Error - destination exists. Delete before copying.
                    command_error(command_name,SHELL_ERROR_CP_DEST_EXISTS,console); 
                    break;
                }

                //Make sure all characters in destination path are valid
                if (path_valid(dest_path)==false)
                {
                    command_error(command_name,SHELL_ERROR_PATH_INVALID,console); 
                    break;
                }

                //Open source file
                FILE *read_ptr=fopen(src_path,"r");
                if (read_ptr==NULL)
                {
                    command_error(command_name,SHELL_ERROR_CP_SOURCE,console); 
                    break;
                }

                //Open destination file
                FILE *write_ptr=fopen(dest_path,"w");
                if (write_ptr==NULL)
                {
                    fclose(read_ptr);
                    command_error(command_name,SHELL_ERROR_CP_DEST,console); 
                    break;
                }

                //Manually copy bytes from source to destination
                uint8_t copy_buffer[SHELL_CP_SIZE];
                size_t bytes_read;
                size_t bytes_written;
                do
                {
                    bytes_read=fread(copy_buffer,1,SHELL_CP_SIZE,read_ptr);
                    bytes_written=fwrite(copy_buffer,1,bytes_read,write_ptr);
                    if (bytes_written!=bytes_read)
                    {
                        //Close files here even though closed below since break here exits loop NOT case statement!
                        fclose(read_ptr);
                        read_ptr=NULL;
                        fclose(write_ptr);
                        write_ptr=NULL;
                        command_error(command_name,SHELL_ERROR_CP_COPYING,console); 
                        break;
                    }
                }while(bytes_read>0);
                
                //Close files. May have been closed during copy operation above so check if still open.
                if (read_ptr!=NULL) fclose(read_ptr);
                if (write_ptr!=NULL) fclose(write_ptr);

                break;
            }
        case SHELL_CMD_EXIT:
            return COMMAND_EXIT;
        case SHELL_CMD_HELP:
            {
                //Command name in case of error message
                const char *command_name="help";

                if (arg_count==1)
                {
                    //No arguments - show help for all commands
                    show_help(NULL,console);
                }
                else if (arg_count==2)
                {
                    //One argument - show help for command
                    char command_name[SHELL_PATH_MAX];
                    strncpy(command_name,input_buffer+args[1].start,args[1].len+1);
                    command_name[args[1].len]=0;
                    show_help(command_name,console);
                }
                else
                {
                    //More than one argument not allowed
                    command_error(command_name,SHELL_ERROR_ARG_COUNT,console);
                    break;
                }
                break;
            }
        case SHELL_CMD_LL:
        case SHELL_CMD_LS:
            {
                //Command name in case of error message
                const char *command_name;
                if (command_id==SHELL_CMD_LL) command_name="ll";
                else command_name="ls";

                color_t color_fg;
                int file_type;
                char new_path[SHELL_PATH_MAX];
                if (arg_count==1)
                {
                    //No arguments - first argument is "ll"/"ls" itself. Use path as directory.
                    strcpy(new_path,shell_path);
                    file_type=FILE_TYPE_DIR;
                }
                else if (arg_count==2)
                {
                    //One argument - use argument as path
                    char arg_path[SHELL_PATH_MAX];
                    strncpy(arg_path,input_buffer+args[1].start,args[1].len+1);
                    arg_path[args[1].len]=0;

                    //Add argument to current path if partial or use argument as path if full path
                    int result=add_path(shell_path,arg_path,new_path);
                    if (result!=SHELL_ERROR_NONE)
                    {
                        command_error(command_name,result,console);
                        break;
                    }

                    //Fetch info on path
                    result=path_type(new_path,&file_type);
                    if (result!=SHELL_ERROR_NONE)
                    {
                        command_error(command_name,result,console); 
                        break;
                    }
                }
                else
                {
                    //More than 1 argument not allowed
                    command_error(command_name,SHELL_ERROR_ARG_COUNT,console);
                    break;
                }

                if (file_type==FILE_TYPE_DIR)
                {
                    //Target path is directory - show contents
                    DIR *directory=opendir(new_path);
                    if (directory==NULL)
                    {
                        command_error(command_name,SHELL_ERROR_CANT_ACCESS,console);
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

                            if (command_id==SHELL_CMD_LS)
                            {
                                //ls - print filename and prevent name from wrapping at screen edge
                                if (file_printed)
                                {
                                    //Only print spacing before filename if not first filename
                                    if (print_width+strlen(SHELL_LS_SEPARATOR)+strlen(dir->d_name)>=SHELL_LS_WIDTH)
                                    {
                                        //If text would wrap, print on new line instead
                                        console_text_default("\n",console);
                                        print_width=0;
                                    }
                                    else
                                    {
                                        //Print separation between files rather than newline
                                        console_text_default(SHELL_LS_SEPARATOR,console);
                                        print_width+=strlen(SHELL_LS_SEPARATOR);
                                    }
                                }
                                
                                //Print directory or file name
                                console_text(dir->d_name,color_fg,SHELL_COL_BG,console);
                                print_width+=strlen(dir->d_name);
                                file_printed=true;
                            }
                            else if (command_id==SHELL_CMD_LL)
                            {
                                //ll - print one file/directory and its size per line

                                int num_len;
                                if (file_type==FILE_TYPE_DIR)
                                {
                                    //Direcotry - no size to print since reads as -1 on calculator
                                    //No digits to print so spaces printed below for alignment
                                    num_len=0;
                                }
                                else
                                {
                                    //File or unknown type - print size 

                                    //Find full path of file
                                    char file_path[SHELL_PATH_MAX];
                                    int result=add_path(new_path,dir->d_name,file_path);
                                    if (result!=SHELL_ERROR_NONE)
                                    {
                                        command_error(command_name,SHELL_ERROR_CANT_ACCESS,console);
                                        break;
                                    }

                                    //Find file size
                                    struct stat stat_buffer;
                                    if (stat(file_path,&stat_buffer))
                                    {
                                        command_error(command_name,SHELL_ERROR_CANT_ACCESS,console);
                                        break;
                                    }
        
                                    //Convert file size to human readable form - ie 1.2M rather than 1234567
                                    char human_buffer[TEXT_INT32_SIZE];
                                    text_int32_human(stat_buffer.st_size,human_buffer);

                                    //Print file size
                                    console_text_default(human_buffer,console);

                                    //Number of spaces to print after file size to align file names
                                    num_len=strlen(human_buffer);
                                }

                                //Blank space for alignment if file size doesn't take full space or no file size if directory
                                if (num_len<SHELL_LL_WIDTH)
                                {
                                    for (int i=0;i<(int)(SHELL_LL_WIDTH-num_len);i++)
                                        console_text_default(" ",console);
                                }

                                //Print separator
                                console_text_default(SHELL_LL_SEPARATOR,console);

                                //Print directory or file name
                                console_text(dir->d_name,color_fg,SHELL_COL_BG,console);
                                console_text_default("\n",console);
                            }
                        }
                    }
                    if (command_id==SHELL_CMD_LS)
                    {
                        //Print newline after done with ls
                        //(not needed for ll which prints newline after every file/directory)
                        if (file_printed==true)
                        {
                            //Only print newline if at least one file printed
                            console_text_default("\n",console);
                        }
                    }
                    
                    //Done searching directory
                    closedir(directory);
                }
                else
                {
                    //Target path points to file - print name
                    char *basename=strrchr(new_path,'/');
                    if (basename==NULL)
                    {
                        //Forward slash not found in path - should never happen but just in case
                        command_error(command_name,SHELL_ERROR_CANT_ACCESS,console);
                        break;
                    }

                    //Skip preceding /
                    basename++;
                    
                    if (command_id==SHELL_CMD_LL)
                    {
                        //ll - print size of file

                        //Find file size
                        struct stat stat_buffer;
                        if (stat(new_path,&stat_buffer))
                        {
                            command_error(command_name,SHELL_ERROR_CANT_ACCESS,console);
                            break;
                        }

                        //Convert file size to human readable form - ie 1.2M rather than 1234567
                        char human_buffer[TEXT_INT32_SIZE];
                        text_int32_human(stat_buffer.st_size,human_buffer);

                        //Print file size
                        console_text_default(human_buffer,console);

                        //Blank space for alignment if file size doesn't take full space
                        int num_len=strlen(human_buffer);
                        if (num_len<SHELL_LL_WIDTH)
                        {
                            for (int i=0;i<(int)(SHELL_LL_WIDTH-num_len);i++)
                                console_text_default(" ",console);
                        }

                        //Print separator
                        console_text_default(SHELL_LL_SEPARATOR,console);
                    }

                    //Print name depending on type - file_type set above after stat
                    color_fg=file_color(basename,file_type);
                    console_text(basename,color_fg,SHELL_COL_BG,console);
                    console_text_default("\n",console);
                }
                break;
            }
        case SHELL_CMD_MKDIR:
            {
                //Command name in case of error message
                const char *command_name="mkdir";

                //Target argument
                char arg_path[SHELL_PATH_MAX];
                char new_path[SHELL_PATH_MAX];
                strncpy(arg_path,input_buffer+args[1].start,args[1].len+1);
                arg_path[args[1].len]=0;

                //Add argument to current path if partial or use argument as path if full path
                int result=add_path(shell_path,arg_path,new_path);
                if (result!=SHELL_ERROR_NONE)
                {
                    command_error(command_name,result,console);
                    break;
                }
                
                //Fetch info on target path
                int target_type;
                result=path_type(new_path,&target_type);
                if (result==SHELL_ERROR_NONE)
                {
                    //Error - target path already exists
                    if (target_type==FILE_TYPE_REG)
                        command_error(command_name,SHELL_ERROR_MKDIR_FILE,console); 
                    else command_error(command_name,SHELL_ERROR_MKDIR_DIR,console); 
                    break;
                }

                //Make sure all characters in path are valid
                if (path_valid(new_path)==false)
                {
                    command_error(command_name,SHELL_ERROR_PATH_INVALID,console); 
                    break;
                }

                //Make directory
                if (mkdir(new_path,SHELL_MKDIR_FLAGS)!=0)
                {
                    command_error(command_name,SHELL_ERROR_MKDIR,console);
                    break;
                }
                break;
            }
        case SHELL_CMD_MV:
            {
                //Command name in case of error message
                const char *command_name="mv";

                //Source argument
                char arg_path[SHELL_PATH_MAX];
                char src_path[SHELL_PATH_MAX];
                strncpy(arg_path,input_buffer+args[1].start,args[1].len+1);
                arg_path[args[1].len]=0;

                //Add argument to current path if partial or use argument as path if full path
                int result=add_path(shell_path,arg_path,src_path);
                if (result!=SHELL_ERROR_NONE)
                {
                    command_error(command_name,result,console);
                    break;
                }
                
                //Fetch info on source path
                int source_type;
                result=path_type(src_path,&source_type);
                if (result!=SHELL_ERROR_NONE)
                {
                    //Note error in result from path_type may be different!
                    //Substitue error code so obvious problem is with source
                    command_error(command_name,SHELL_ERROR_CANT_ACCESS_SOURCE,console); 
                    break;
                }

                //Destination argument
                char dest_path[SHELL_PATH_MAX];
                strncpy(arg_path,input_buffer+args[2].start,args[2].len+1);
                arg_path[args[2].len]=0;

                //Add argument to current path if partial or use argument as path if full path
                result=add_path(shell_path,arg_path,dest_path);
                if (result!=SHELL_ERROR_NONE)
                {
                    command_error(command_name,result,console);
                    break;
                }
                
                //Fetch info on destination path
                int dest_type;
                result=path_type(dest_path,&dest_type);
                if (result==SHELL_ERROR_NONE)
                {
                    //Error - destination exists. Delete before moving.
                    command_error(command_name,SHELL_ERROR_MV_DEST_EXISTS,console); 
                    break;
                }

                //Make sure all characters in destination path are valid
                if (path_valid(dest_path)==false)
                {
                    command_error(command_name,SHELL_ERROR_PATH_INVALID,console); 
                    break;
                }

                //Move file
                if (rename(src_path,dest_path)!=0)
                {
                    command_error(command_name,SHELL_ERROR_MV,console); 
                    break;
                }

                break;
            }
        case SHELL_CMD_RM:
            {
                //Command name in case of error message
                const char *command_name="rm";

                //Source argument
                char arg_path[SHELL_PATH_MAX];
                char new_path[SHELL_PATH_MAX];
                strncpy(arg_path,input_buffer+args[1].start,args[1].len+1);
                arg_path[args[1].len]=0;

                //Add argument to current path if partial or use argument as path if full path
                int result=add_path(shell_path,arg_path,new_path);
                if (result!=SHELL_ERROR_NONE)
                {
                    command_error(command_name,result,console);
                    break;
                }
                
                //Fetch info on target path
                int target_type;
                result=path_type(new_path,&target_type);
                if (result!=SHELL_ERROR_NONE)
                {
                    command_error(command_name,result,console); 
                    break;
                }

                //Make sure target path is file
                if (target_type!=FILE_TYPE_REG)
                {
                    command_error(command_name,SHELL_ERROR_TARGET_FILE,console); 
                    break;
                }

                //Check if file is read-only based on file extension
                if (file_special(new_path)==FILE_SPECIAL_RO)
                {
                    command_error(command_name,SHELL_ERROR_READ_ONLY,console); 
                    break;
                }

                //Delete file
                if (remove(new_path)!=0)
                {
                    command_error(command_name,SHELL_ERROR_CANT_ACCESS,console); 
                    break;
                }
                break;
            }
        case SHELL_CMD_RMDIR:
            {
                //Command name in case of error message
                const char *command_name="rmdir";

                //Source argument
                char arg_path[SHELL_PATH_MAX];
                char new_path[SHELL_PATH_MAX];
                strncpy(arg_path,input_buffer+args[1].start,args[1].len+1);
                arg_path[args[1].len]=0;

                //Add argument to current path if partial or use argument as path if full path
                int result=add_path(shell_path,arg_path,new_path);
                if (result!=SHELL_ERROR_NONE)
                {
                    command_error(command_name,result,console);
                    break;
                }
                
                //Fetch info on target path
                int target_type;
                result=path_type(new_path,&target_type);
                if (result!=SHELL_ERROR_NONE)
                {
                    command_error(command_name,result,console); 
                    break;
                }

                //Make sure target path is directory
                if (target_type!=FILE_TYPE_DIR)
                {
                    command_error(command_name,SHELL_ERROR_TARGET_DIR,console); 
                    break;
                }

                //Delete directory
                if (rmdir(new_path)!=0)
                {
                    command_error(command_name,SHELL_ERROR_CANT_ACCESS,console); 
                    break;
                }
                break;
            }
        case SHELL_CMD_TOUCH:
            {
                //Command name in case of error message
                const char *command_name="touch";

                //Target argument
                char arg_path[SHELL_PATH_MAX];
                char target_path[SHELL_PATH_MAX];
                strncpy(arg_path,input_buffer+args[1].start,args[1].len+1);
                arg_path[args[1].len]=0;

                //Add argument to current path if partial or use argument as path if full path
                int result=add_path(shell_path,arg_path,target_path);
                if (result!=SHELL_ERROR_NONE)
                {
                    command_error(command_name,result,console);
                    break;
                }
                
                //Fetch info on target path
                int target_type;
                result=path_type(target_path,&target_type);
                if (result==SHELL_ERROR_NONE)
                {
                    //Target exists - exit silently without error
                    break;
                }

                //Make sure all characters in target path are valid
                if (path_valid(target_path)==false)
                {
                    command_error(command_name,SHELL_ERROR_PATH_INVALID,console); 
                    break;
                }

                //Create target file
                FILE *write_ptr=fopen(target_path,"w");
                if (write_ptr==NULL)
                {
                    command_error(command_name,SHELL_ERROR_TOUCH,console); 
                    break;
                }
                fclose(write_ptr);
            }
    }
    return COMMAND_NONE;
}

int calc_shell(int command_ID, struct WindowInfo *windows, int selected_window)
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

    //Heap memory
    select_heap(window.tab_index,drawn_split);
    uint8_t *heap_ptr=get_split_heap();

    //Pointers to data on heap
    struct ShellInfo *shell;
    struct ConsoleInfo *console;

    if (command_ID==COMMAND_START) 
    {
        //Allocate memory for and initialize console
        shell=(struct ShellInfo *)add_object(sizeof(struct ShellInfo),heap_ptr);
        
        //Make sure allocation succeeded
        if (shell==NULL)
        {
            error_screen(ERROR_OUT_OF_MEMORY,pos,width,height);
            return COMMAND_EXIT;
        }

        //Init console
        console=&shell->console;
        init_console(
            //Console
            console,
            SHELL_COL_FG,
            SHELL_COL_BG,
            //Input
            shell->input_text,
            shell->input_copy_text,
            SHELL_INPUT_MAX,
            SHELL_COL_FG,
            SHELL_COL_BG,
            //History
            shell->history,
            shell->history_texts,
            SHELL_HIST_COUNT);
        reset_console_pointers(console);
        reset_console(console);

        //Init input
        console_text_default(SHELL_CONSOLE_STRING,console);
        console->reset_input=true;
        console->modifier=MODIFIER_ALPHA_LOWER_LOCK;
        console->input_copied=false;

        //Init history
        init_history(console);

        //Init file system path
        strcpy(shell->path,"/");
    }
    else
    {
        //Resume or Redraw - reuse existing memory for console
        shell=(struct ShellInfo *)object_address(SHELL_ID_CONSOLE,heap_ptr);
        console=&shell->console;
        reset_console_pointers(console);
    }

    //Redraw screen but only spare pixels on edges. Letters redrawn below.
    draw_rect(pos.x,pos.y,width,height,SHELL_COL_BG,SHELL_COL_BG);

    //Set position based on split location
    init_position(console,pos,window.split_state);

    //Main loop
    bool redraw_screen=true;
    bool redraw_modifier=true;
    while (1)
    {
        //Print prompt for input
        if (console->reset_input)
        {
            console->input.text[0].character=0;
            console->input.cursor=0;
            console->input.len=0;
            console_text("CG50",SHELL_COL_HOST,SHELL_COL_BG,console);
            console_text_default(":",console);
            console_text(shell->path,SHELL_COL_DIR,SHELL_COL_BG,console);
            console_text_default(" ",console);
            console->input_copied=false;
        }
        console->reset_input=false;

        //Redraw modifiers (shift, alpha) as necessary even if rest of screen not redrawn
        if (redraw_modifier) draw_modifier(console->modifier);

        if (redraw_screen)
        {
            //Always redraw screen whether START, RESUME, or REDRAW
            draw_console(console);
                
            //Return if Redraw only
            if (command_ID==COMMAND_REDRAW) return COMMAND_DONE;
        }

        //Copy updates to screen if modifier keys or text have changed
        if ((redraw_screen)||(redraw_modifier)) dupdate();
        redraw_screen=true;
        
        //Get key
        int old_modifier=console->modifier;
        int key=getkey_text(true,&console->modifier,NULL);

        //Redraw modifiers (shift, alpha) next time through if they have changed
        if (old_modifier!=console->modifier) redraw_modifier=true;
        else redraw_modifier=false;

        //Look for keys before sys_key_handler below in case need to handle any sys_keys differently
        char character=vkey_printable[key];
        if (character!=0)
        {
            //Printable character - add to input line
            add_input_char(character,SHELL_COL_FG,SHELL_COL_BG,console);
        }
        else
        {
            switch (key)
            {
                case VKEY_QUIT: //Shift+EXIT
                    //Exit and return to window manager
                    return COMMAND_EXIT;
                    break;
                case VKEY_EXIT:
                    //Clear line but do not exit program
                    //Handle here so not picked up by sys_key_handler below which would exit program
                    if (console->input.len==0)
                    {
                        //No input on line - don't cancel
                        break;
                    }
                    
                    //Append ^C to show input cancelled
                    const char *cancel_text="^C";
                    if (console->input.len>=SHELL_INPUT_MAX-(int)strlen(cancel_text))
                    {
                        //Not enough room to append ^C so drop characters from end of input to make room
                        console->input.len=SHELL_INPUT_MAX-strlen(cancel_text)-1;
                        console->input.cursor=SHELL_INPUT_MAX-strlen(cancel_text)-1;
                    }
                    add_input_text(cancel_text,SHELL_COL_FG,SHELL_COL_BG,console);

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
                        char input_buffer[SHELL_INPUT_MAX];
                        copy_console_text(&console->input,input_buffer,SHELL_INPUT_MAX,0);
                        //gint_world_switch here necessary since process_input accesses file system
                        //so need to pass arguments as void pointer to structure
                        struct ProcessInput temp_args={input_buffer,console,shell->path};
                        int return_code=gint_world_switch(GINT_CALL(process_input,(void *)(&temp_args)));
                        if (return_code!=COMMAND_NONE)
                        {
                            //Return to window manager to process any return code such as closing console
                            return return_code;
                        }
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

