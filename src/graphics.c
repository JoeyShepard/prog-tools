#include <stdint.h>
#include "compatibility.h"
#include "graphics.h"

uint16_t *vram_main, *vram_buffer;

void draw_line_horz(int x0, int x1, int y, int16_t color)
{
    //Don't draw off screen
    if ((x0<0)||(x0>=DWIDTH)||
        (x1<0)||(x1>=DWIDTH)||
        (y<0)||(y>=DHEIGHT)) return;

    //Copy of pointer to video memory
    uint16_t *screen=vram_buffer;

    //x0 should be smaller than x1
    if (x0>x1)
    {
        int swap_temp=x0;
        x0=x1;
        x1=swap_temp;
    }

    //Calculate starting address
    screen+=x0;
    screen+=DWIDTH*y;
    
    //Draw line
    for (int i=x0;i<=x1;i++)
    {
        *screen=color;
        screen++;
    }
}

void draw_line_vert(int x, int y0, int y1, int16_t color)
{
    //Don't draw off screen
    if ((y0<0)||(y0>=DHEIGHT)||
        (y1<0)||(y1>=DHEIGHT)||
        (x<0)||(x>=DWIDTH)) return;

    //Copy of pointer to video memory
    uint16_t *screen=vram_buffer;

    //y0 should be smaller than y1
    if (y0>y1)
    {
        int swap_temp=y0;
        y0=y1;
        y1=swap_temp;
    }

    //Calculate starting address
    screen+=x;
    screen+=DWIDTH*y0;
    
    //Draw line
    for (int i=y0;i<=y1;i++)
    {
        *screen=color;
        screen+=DWIDTH;
    }
}

void draw_rect(int x, int y, int width, int height, int32_t border, int32_t fill)
{
    //Line functions below check coordinates

    //Outer edges if not transparent
    if (border!=-1)
    {
        draw_line_horz(x,x+width-1,y,border);                //Top
        draw_line_horz(x,x+width-1,y+height-1,border);       //Bottom
        draw_line_vert(x,y+1,y+height-2,border);             //Left
        draw_line_vert(x+width-1,y+1,y+height-2,border);     //Right
    }

    //Fill if not transparent
    if (fill!=-1)
    {
        for (int i=y+1;i<y+height-1;i++)
        {
            draw_line_horz(x+1,x+width-2,i,fill);
        }
    }
}
