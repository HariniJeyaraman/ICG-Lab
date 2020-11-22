#include "graphics.h"
#include<stdio.h>
void wait_for_char()
{
    //Wait for a key press
    int in = 0;
    while (in == 0) {
        in = getchar();
    }
}
void BoundaryFill_4_Connected(int x,int y,int f_color,int b_color)
{
    int current = getpixel(x,y);
    // setbkcolor(WHITE);
    if(current != b_color && current != f_color)
    {
        putpixel(x,y,f_color);
        BoundaryFill_4_Connected( x+1, y, f_color, b_color);
        BoundaryFill_4_Connected( x-1, y, f_color, b_color);
        BoundaryFill_4_Connected( x, y+1, f_color, b_color);
        BoundaryFill_4_Connected( x, y-1, f_color, b_color);
    }
}
void drawFigure(){
    
    // setfillstyle(1, YELLOW);
    //  floodfill(200,200,BLACK);
   
   circle(200,200,115);
   
   circle(200,200,100);
   circle(240,160,15);
   circle(160,160,15);
//    rectangle(160, 210, 250, 240);
   rectangle(250,220,160,210);
   BoundaryFill_4_Connected( 200, 200, BLACK, YELLOW);
   BoundaryFill_4_Connected( 200, 200, YELLOW, WHITE);
   BoundaryFill_4_Connected( 240, 160, BLACK, WHITE);
   BoundaryFill_4_Connected( 160, 160, BLACK, WHITE);
   BoundaryFill_4_Connected( 250, 220, BLACK, WHITE);
   
}

int main()
{
    //gm is a Graphics mode which is a computer display mode that generates images using pixels
    //DETECT is a macro defined in "graphics.h" header file
    int gd = DETECT, gm;
    //initgraph initilizes the graphics system by loading a graphics driver from disk
    initgraph(&gd, &gm, NULL);
    drawFigure();
    wait_for_char();
    closegraph();
    
    return 0;
}
//gcc -o Q3 Q3.c -lgraph




/*https://programmingcliff.blogspot.com/2018/10/smile-emoji-using-graphics.html*/