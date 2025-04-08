#ifndef __GUARD_PROG_TOOLS_COMMAND
    #define __GUARD_PROG_TOOLS_COMMAND

    #include <stdint.h>

    #include "compatibility.h"
    #include "console.h"
    #include "structs.h"

    //Shell colors
    #define SHELL_COL_FG        COL_WHITE
    #define SHELL_COL_BG        COL_BLACK
   
    #define SHELL_COL_ERR_FG    SHELL_COL_FG
    #define SHELL_COL_ERR_BG    SHELL_COL_BG

    #define SHELL_COL_HOST      C_RGB(COL_1_4,COL_MAX,COL_1_4)
    #define SHELL_COL_DIR       C_RGB(COL_1_4,COL_1_4,COL_MAX)
    #define SHELL_COL_FILE      COL_WHITE
    #define SHELL_COL_EXEC      C_RGB(COL_1_4,COL_MAX,COL_1_4)
    #define SHELL_COL_RO        C_RGB(COL_MAX,COL_1_4,COL_1_4)
    #define SHELL_COL_UNKNOWN   C_RGB(COL_MAX,COL_1_4,COL_MAX)

    //Heap memory
    #define SHELL_ID_CONSOLE    0

    //Console
    #define SHELL_INPUT_MAX         124     //Four full lines of text input if hsplit
    #define SHELL_CONSOLE_STRING    "Calculator shell for fx-CG50\nType 'help' for more info.\n" 
    
    //History
    #define SHELL_HIST_COUNT    10

    //Argument processing
    #define SHELL_ARG_MAX       10
    #define SHELL_PARSE_NONE    0
    #define SHELL_PARSE_WORD    1

    //File system
    #define SHELL_PATH_MAX      128     //Should be at least as long as SHELL_INPUT_MAX

    //Commands
    #define SHELL_LS_WIDTH      CONS_WHOLE_WIDTH
    #define SHELL_LS_SEPARATOR  "  "    //Printed between filenames by ls
    #define SHELL_LL_WIDTH      (TEXT_INT32_HUMAN_SIZE-1)
    #define SHELL_LL_SEPARATOR  "  "    //Printed between file size and filename by ll
    #define SHELL_CAT_SIZE      1024
    #define SHELL_CP_SIZE       1024
    //TODO: matters on calculator? needed on linux
    #define SHELL_MKDIR_FLAGS   0755

    //enums
    //=====
    enum ShellCommands
    {
        SHELL_CMD_NONE,
        SHELL_CMD_CAT,
        SHELL_CMD_CD,
        SHELL_CMD_CLEAR,
        SHELL_CMD_CP,
        SHELL_CMD_EXIT,
        SHELL_CMD_HELP,
        SHELL_CMD_LL,
        SHELL_CMD_LS,
        SHELL_CMD_MKDIR,
        SHELL_CMD_MV,
        SHELL_CMD_RM,
        SHELL_CMD_RMDIR,
        SHELL_CMD_TOUCH,
    };

    enum ShellErrors
    {
        SHELL_ERROR_NONE,
        SHELL_ERROR_PATH_TOO_LONG,
        SHELL_ERROR_NORMALIZE_PATH,
        SHELL_ERROR_PATH_NOT_FOUND,
        SHELL_ERROR_CANT_ACCESS,
        SHELL_ERROR_ARG_COUNT,
        SHELL_ERROR_ARG_MEM,
        SHELL_ERROR_NOT_FOUND,
        SHELL_ERROR_NOT_DIRECTORY,
        SHELL_ERROR_TARGET_FILE,
        SHELL_ERROR_TARGET_DIR,
        SHELL_ERROR_CP_SOURCE_NOT_FILE,
        SHELL_ERROR_CP_DEST_EXISTS,
        SHELL_ERROR_CP_SOURCE,
        SHELL_ERROR_CP_DEST,
        SHELL_ERROR_CP_COPYING,
        SHELL_ERROR_CANT_ACCESS_SOURCE,
        SHELL_ERROR_CANT_ACCESS_DEST,
        SHELL_ERROR_READ_ONLY,
        SHELL_ERROR_MKDIR_FILE,
        SHELL_ERROR_MKDIR_DIR,
        SHELL_ERROR_MKDIR,
        SHELL_ERROR_PATH_INVALID,
        SHELL_ERROR_MV_DEST_EXISTS,
        SHELL_ERROR_MV,
        SHELL_ERROR_TOUCH
    };

    enum FileTypes
    {
        FILE_TYPE_DIR,
        FILE_TYPE_REG,
        FILE_TYPE_UNKNOWN
    };

    enum FileSpecialTypes
    {
        FILE_SPECIAL_NONE,
        FILE_SPECIAL_EXEC,
        FILE_SPECIAL_RO
    };

    //For passing args to process_input which requires gint world switch
    struct ProcessInput
    {
        char *input_buffer;
        struct ConsoleInfo *console;
        char *path;
    };

    //Custom struct to save everything to heap
    struct ShellInfo
    {
        struct ConsoleInfo console; 
        
        //Custom size memory used by console above
        struct ConsoleChar input_text[SHELL_INPUT_MAX];
        struct ConsoleChar input_copy_text[SHELL_INPUT_MAX];
        struct ConsoleInput history[SHELL_HIST_COUNT];
        struct ConsoleChar history_texts[SHELL_HIST_COUNT*SHELL_INPUT_MAX];

        //Current directory of shell
        char path[SHELL_PATH_MAX];
    };


    //Functions
    //=========
    int command_line(int command_ID, struct WindowInfo *windows, int selected_window);

#endif
