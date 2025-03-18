#include <stdint.h>
#include <string.h>

#include "error.h"
#include "graphics.h"
#include "text.h"
#include "compatibility.h"

//Font data
static uint8_t font_5x8[]=
{
    //Custom characters
    0xFF,0xFF,0xFF,0xFF,0xFF,             // solid block cursor

    //Normal characters
    0,0,0,0,0,                            // space
    0x0,0x6F,0x6F,0x0,0x0,                // !
    5,3,0,5,3,                            // "
    0x14,0x3E,0x14,0x3E,0x14,             // #
    0x2E,0x2A,0x7F,0x2A,0x3A,             // $
    0x43,0x33,0x8,0x66,0x61,              // %
    0x36,0x49,0x55,0x22,0x58,             // &
    0x0,0x5,0x3,0x0,0x0,                  // '
    0x0,0x3C,0x42,0x81,0x0,               // (
    0x0,0x81,0x42,0x3C,0x0,               // )
    0x28,0x10,0x7C,0x10,0x28,             // *
    0x08,0x08,0x3E,0x08,0x08,             // +
    0x0,0xA0,0x60,0x0,0x0,                // ,
    0x08,0x08,0x08,0x08,0x08,             // -
    0x0,0x60,0x60,0x0,0x0,                // .
    0xC0,0x30,0xC,0x3,0x0,                // /
    0x3E,0x51,0x49,0x45,0x3E,             // 0
    0x44,0x42,0x7F,0x40,0x40,             // 1
    0x42,0x61,0x51,0x49,0x46,             // 2
    0x22,0x41,0x49,0x49,0x36,             // 3
    0xF,0x8,0x8,0x8,0x7F,                 // 4
    0x27,0x45,0x45,0x45,0x39,             // 5
    0x3E,0x49,0x49,0x49,0x32,             // 6
    0x1,0x1,0x61,0x19,0x7,                // 7
    0x36,0x49,0x49,0x49,0x36,             // 8
    0x26,0x49,0x49,0x49,0x3E,             // 9
    0x0,0x36,0x36,0x0,0x0,                // :
    0x0,0x56,0x36,0x0,0x0,                // ;
    0x8,0x14,0x22,0x41,0x0,               // <
    0x14,0x14,0x14,0x14,0x14,             // =
    0x41,0x22,0x14,0x8,0x0,               // >
    0x2,0x1,0x51,0x9,0x6,                 // ?
    0x3C,0x42,0x5A,0x52,0x4C,             // @
    0x7E,0x9,0x9,0x9,0x7E,                // A
    0x7F,0x49,0x49,0x49,0x36,             // B
    0x3E,0x41,0x41,0x41,0x22,             // C
    0x7F,0x41,0x41,0x22,0x1C,             // D
    0x7F,0x49,0x49,0x49,0x49,             // E
    0x7F,0x9,0x9,0x9,0x9,                 // F
    0x3E,0x41,0x49,0x49,0x3A,             // G
    0x7F,0x8,0x8,0x8,0x7F,                // H
    0x41,0x41,0x7F,0x41,0x41,             // I
    0x31,0x41,0x41,0x3F,0x1,              // J
    0x7F,0x8,0x14,0x22,0x41,              // K
    0x7F,0x40,0x40,0x40,0x40,             // L
    0x7F,0x2,0x4,0x2,0x7F,                // M
    0x7F,0x2,0x4,0x8,0x7F,                // N
    0x3E,0x41,0x41,0x41,0x3E,             // O
    0x7F,0x9,0x9,0x9,0x6,                 // P
    0x3E,0x41,0x51,0x21,0x5E,             // Q
    0x7F,0x9,0x19,0x29,0x46,              // R
    0x26,0x49,0x49,0x49,0x32,             // S
    0x1,0x1,0x7F,0x1,0x1,                 // T
    0x3F,0x40,0x40,0x40,0x3F,             // U
    0xF,0x30,0x40,0x30,0xF,               // V
    0x1F,0x60,0x1C,0x60,0x1F,             // W
    0x63,0x14,0x8,0x14,0x63,              // X
    0x3,0x4,0x78,0x4,0x3,                 // Y
    0x61,0x51,0x49,0x45,0x43,             // Z
    0x0,0xFF,0x81,0x81,0x0,               // [
    0x3,0xC,0x30,0xC0,0x0,                // back slash
    0x0,0x81,0x81,0xFF,0x0,               // ]
    0x4,0x2,0x1,0x2,0x4,                  // ^
    0x40,0x40,0x40,0x40,0x40,             // _
    0x0,0x1,0x2,0x4,0x0,                  // `
    0x38,0x44,0x44,0x24,0x78,             // a
    0x7F,0x48,0x44,0x44,0x38,             // b
    0x38,0x44,0x44,0x44,0x44,             // c
    0x38,0x44,0x44,0x48,0x7F,             // d
    0x38,0x54,0x54,0x54,0x18,             // e
    0x8,0x8,0x7E,0x9,0x9,                 // f
    0x18,0xA4,0xA4,0xA4,0x78,             // g
    0x7F,0x8,0x4,0x4,0x78,                // h
    0x0,0x44,0x7D,0x40,0x0,               // i
    0x40,0x80,0x80,0x7D,0x0,              // j
    0x7F,0x10,0x28,0x44,0x0,              // k
    0x0,0x41,0x7F,0x40,0x0,               // l
    0x7C,0x4,0x78,0x4,0x78,               // m
    0x7C,0x8,0x4,0x4,0x78,                // n
    0x38,0x44,0x44,0x44,0x38,             // o
    0xFC,0x24,0x24,0x24,0x18,             // p
    0x18,0x24,0x24,0x24,0xF8,             // q
    0x7C,0x8,0x4,0x4,0x8,                 // r
    0x48,0x54,0x54,0x54,0x24,             // s
    0x4,0x4,0x3E,0x44,0x44,               // t
    0x3C,0x40,0x40,0x20,0x7C,             // u
    0x1C,0x20,0x40,0x20,0x1C,             // v
    0x1C,0x60,0x1C,0x60,0x1C,             // w
    0x44,0x28,0x10,0x28,0x44,             // x
    0x1C,0xA0,0xA0,0xA0,0x7C,             // y
    0x44,0x64,0x54,0x4C,0x44,             // z
    0x0,0x8,0x76,0x81,0x0,                // {
    0x0,0x0,0xFF,0x0,0x0,                 // |
    0x0,0x81,0x76,0x8,0x0,                // }
    0x8,0x4,0x8,0x10,0x8,                 // ~
};

uint8_t *font_data(int font)
{
    switch (font)
    {
        case FONT_5x8: return font_5x8;
        default: return NULL;
    }
}

int font_width(int font)
{
    switch (font)
    {
        case FONT_5x8: return 5;
    }
    return 0;
}

int font_height(int font)
{
    switch (font)
    {
        case FONT_5x8: return 8;
    }
    return 0;
}

int text_width(const char *text, int font)
{
    int width=font_width(font);

    //Fixed spacing for now though may change in the future
    int horz_spacing=1;

    //Return if font not found
    if (width==0) return 0;

    //Find length of string
    int len=0;
    while (*text)
    {
        len++;
        text++;
    }

    //Calculate width in pixels
    return len*(width+horz_spacing)+horz_spacing;
}

bool text_printable(char text)
{
    return ((text>=CHAR_PRINTABLE_MIN)&&(text<=CHAR_PRINTABLE_MAX));
}

struct point draw_char(char text, struct point pos, int32_t fg, int32_t bg, bool invert, int font)
{
    char buffer[2];
    buffer[0]=text;
    buffer[1]=0;
    return draw_text(buffer,pos,fg,bg,invert,font);
}

struct point draw_text(const char *text, struct point pos, int32_t fg, int32_t bg, bool invert, int font)
{ 
    //Copy of pointer to video memory
     uint16_t *screen=vram_buffer;

    //Look up values for selected font
    uint8_t *data=font_data(font);
    if (data==NULL)
    {
        error_exit(ERROR_FONT_NOT_FOUND);
    }
    int width=font_width(font);
    int height=font_height(font);
    
    //Spacing could vary by font but ok to set manually for now
    int horz_spacing=1;
    int vert_spacing=1;
    
    //Don't draw outside bounds of screen
    if ((pos.x>=DWIDTH)||(pos.y>=DHEIGHT)||(pos.y+height>=DHEIGHT)) return pos;

    //Calculate offset into screen buffer
    screen+=pos.x;
    screen+=pos.y*DWIDTH;

    //Swap fg and bg colors if inverted
    if (invert)
    {
        int32_t swap_temp=fg;
        fg=bg;
        bg=swap_temp;
    }

    if (*text==0)
    {
        //Exit early and don't draw spacing-wide vertical column if no characters to draw
        return pos;
    }

    //Draw one spacing-wide vertical column before first character
    for (int j=0;j<height+vert_spacing*2;j++)
    {
        for (int i=0;i<horz_spacing;i++)
        {
            //Draw background pixel
            if (bg!=-1)
            {
                //Don't draw if transparent
                *screen=bg;
            }

            //Advance to next pixel in video buffer
            screen++;
        }

        //Reset to next line
        screen+=DWIDTH-horz_spacing;
    }

    //Reset drawing for first character
    screen-=(height+vert_spacing*2)*DWIDTH;
    screen+=horz_spacing;

    //Loop through characters
    while (*text)
    {
        //TODO: separate loops for transparency if need performance

        //Stop drawing if go off screen
        if (pos.x+width+horz_spacing>=DWIDTH) return pos;

        //Draw ? if character out of range
        char draw_char=*text;
        if (text_printable(draw_char)==false) draw_char='?';

        //Calculate table offset
        draw_char-=CHAR_PRINTABLE_MIN;  
        uint8_t *char_data=data+draw_char*width;

        //Draw character data
        for (int j=0;j<height+vert_spacing*2;j++)
        {
            for (int i=0;i<width;i++)
            {
                bool draw;
                if ((j>=vert_spacing)&&(j<height+vert_spacing))
                {
                    //Look up pixel in font data table since not spacing row
                    draw=char_data[i]&(1<<(j-vert_spacing));
                }
                else
                {
                    //Spacing row so draw bg color
                    draw=false;
                }

                if (draw)
                {
                    //Draw foreground pixel
                    if (fg!=-1)
                    {
                        //Don't draw if transparent
                        *screen=fg;
                    }
                }
                else
                {
                    //Draw background pixel
                    if (bg!=-1)
                    {
                        //Don't draw if transparent
                        *screen=bg;
                    }
                }

                //Advance to next pixel in video buffer
                screen++;
            }

            //Extra pixel for spacing
            if (bg!=-1)
            {
                //Don't draw if transparent
                *screen=bg;
            }

            //Reset to next line
            screen+=DWIDTH-width;
        }

        //Advance to next character
        pos.x+=width+horz_spacing;
        text++;

        //Reset drawing to next character
        screen-=(height+vert_spacing*2)*DWIDTH;
        screen+=width+horz_spacing;
    }

    //Done drawing. Return updated position.
    return pos;
}


struct point outline_text(const char *text, struct point pos, int32_t fg, int32_t bg, int32_t border, bool invert, int font)
{
    int width=text_width(text,font);
    
    //Return without drawing if font not found
    if (width==0) return pos;

    //Draw rectangle
    draw_rect(pos.x,pos.y,width+2,font_height(font)+4,border,COL_TRANS);

    //Offset text from border
    pos.x++;
    pos.y++;

    //Draw text
    draw_text(text,pos,fg,bg,invert,font);

    //Update coordinates for return to show where drawing stopped
    pos.y--;
    pos.x+=width+1;
    return pos;
}

void text_int32(int32_t num, char *text)
{
    int32_t divider=1000000000;
    bool digit_found=false;
    if (num<0)
    {
        *text='-';
        text++;
        num=(~num)+1;
    }
    *text=0;
    while (divider)
    {
        if ((num/divider)||(digit_found))
        {
            *text='0'+num/divider;
            text++;
            *text=0;
            num%=divider;
            digit_found=true;
        }
        divider/=10;
    }
    if (digit_found==false)
    {
        *text='0';
        *(text+1)=0;
    }
}

void text_hex32(uint32_t num, char *text, int digits)
{
    for (int i=(digits-1);i>=0;i--)
    {
        int digit=num&0xF;
        if (digit<10) digit+='0';
        else digit+='A'-10;
        text[i]=digit;
        num/=0x10;
    }
    text[digits]=0;
}

void text_int32_commas(int32_t num, char *text)
{
    char num_buffer[TEXT_INT32_SIZE];
    text_int32(num,num_buffer);
    int comma_counter=strlen(num_buffer);
    for (int i=0;i<strlen(num_buffer);i++)
    {
        *text=num_buffer[i];
        *(text+1)=0;
        text++;
        comma_counter--;
        if ((comma_counter%3==0)&&(comma_counter))
        {
            //Insert comma
            *text=',';
            *(text+1)=0;
            text++;
        }
    }
}

void text_int32_human(int32_t num, char *text)
{
    char num_buffer[TEXT_INT32_SIZE];
    if (num<1024)
    {
        //<1024
        text_int32(num,text);
    }
    else if (num<10*1024)
    {
        //<10K
        text_int32(1000*num/(10*1024),num_buffer);
        text[0]=num_buffer[0];
        text[1]='.';
        text[2]=num_buffer[1];
        text[3]=num_buffer[2];
        text[4]='K';
        text[5]=0;
    }
    else if (num<100*1024)
    {
        //<100K
        text_int32(1000*num/(100*1024),num_buffer);
        text[0]=num_buffer[0];
        text[1]=num_buffer[1];
        text[2]='.';
        text[3]=num_buffer[2];
        text[4]='K';
        text[5]=0;
    }
    else if (num<1000*1024)
    {
        //<1000K
        text_int32(1000*num/(1000*1024),num_buffer);
        text[0]=num_buffer[0];
        text[1]=num_buffer[1];
        text[2]=num_buffer[2];
        text[3]='K';
        text[4]=0;
    }
    else if (num<1024*1024)
    {
        //1000K and <1M as 1023K
        text_int32(1000*num/(1000*1024),num_buffer);
        text[0]=num_buffer[0];
        text[1]=num_buffer[1];
        text[2]=num_buffer[2];
        text[3]=num_buffer[3];
        text[4]='K';
        text[5]=0;
    }
    else if (num<10*1024*1024)
    {
        //>=1M
        text_int32(1000*num/(1024*1024),num_buffer);
        text[0]=num_buffer[0];
        text[1]='.';
        text[2]=num_buffer[1];
        text[3]=num_buffer[2];
        text[4]='M';
        text[5]=0;
    }
    else text[0]=0;
}

