#ifndef __GUARD_PROG_TOOLS_ERROR
    #define __GUARD_PROG_TOOLS_ERROR

    enum ErrorNumbers
    {
        ERROR_NONE,
        ERROR_FONT_NOT_FOUND,
        ERROR_MENU_TEXT_TOO_LONG,
        ERROR_UNALIGNED_WRITE
    };

    void error_exit(int error);

#endif
