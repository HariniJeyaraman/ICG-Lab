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

void drawFigure(){
    //equilateral triangle
    setcolor(BLUE);
    //Coordinates of traingle are (100,200), (200,200), (150,200-50*3^1/2)
    line(150,113.39745,100,200);
    line(100,200,200,200);
    line(200,200,150,113.39745);
    setcolor(LIGHTGREEN);
    //centre of circles : (150, 200-50/3^(1/2))
    //radius : 50/3^(1/2)
    circle(150,171.132486,28.8675134595);
    //radius : 100/3^(1/2)
    circle(150,171.132486,57.735026919);
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