#ifndef __GUARD_PROG_TOOLS_FORTH_PROCESS
    #define __GUARD_PROG_TOOLS_FORTH_PROCESS

    #include <stdint.h>

    #include "forth-engine.h"

    //enums
    //=====
    enum ForthCharClass
    {
        FORTH_CHAR_MINUS,
        FORTH_CHAR_0,
        FORTH_CHAR_1_9,
        FORTH_CHAR_A_F,
        FORTH_CHAR_G_Z,
        FORTH_CHAR_x,
        FORTH_CHAR_OTHER,
    };

    enum ForthTextType
    {
        //Full types
        FORTH_PARSE_NUMBER,
        FORTH_PARSE_HEX,
        FORTH_PARSE_PRIMITIVE,
        FORTH_PARSE_SECONDARY,
        FORTH_PARSE_NOT_FOUND,
        //Partial types used only for parsing
        FORTH_PARSE_NONE,
        FORTH_PARSE_MINUS,
        FORTH_PARSE_0,
        FORTH_PARSE_0x,
        FORTH_PARSE_OTHER,
    };

    enum ForthControlType
    {
        FORTH_CONTROL_IF,
        FORTH_CONTROL_ELSE,
    };

    int classify_char(char c);
    int classify_word(const char *word);
    int find_primitive(const char *word);
    struct ForthWordHeader *find_secondary(const char *word,struct ForthWordHeaderInfo *words);
    int classify_other(const char *word,struct ForthCompileInfo *compile);
    uint32_t next_word(struct ConsoleInfo *console,uint32_t *start);
    uint32_t next_word_source(const char *source,uint32_t *start);
    int32_t int32_text(const char *word_buffer);
    int32_t hex32_text(const char *word_buffer);
    int expand_definitions(uint32_t size,struct ForthCompileInfo *compile);
    int write_definition_primitive(void (*word)(struct ForthEngine *engine),struct ForthCompileInfo *compile);
    int write_definition_u8(uint8_t value,struct ForthCompileInfo *compile);
    int write_definition_i32(int32_t value,struct ForthCompileInfo *compile);
    int write_definition_u32(uint32_t value,struct ForthCompileInfo *compile);
    int execute_secondary(struct ForthEngine *engine,struct ForthCompileInfo *compile);
    int new_secondary(const char *word_buffer,uint8_t word_type,struct ForthCompileInfo *compile);
    int process_source(struct ForthEngine *engine,const char *source,struct ForthCompileInfo *compile);
    void update_compile_pointers(struct ForthCompileInfo *compile);

#endif
