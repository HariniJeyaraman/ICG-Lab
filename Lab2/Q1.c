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

void drawPoint(){
putpixel(100,150,10);
}

void drawRectangle(){
    //location of left,top,right, bottom
    int left=50, top = 50;
    int right=250, bottom=250;
    rectangle(left,top,right, bottom);
    getch();
    
}

void drawCircle(){
    //circle(x,y,radius)
   circle(140, 150, 80);
    getch();
   
}

void drawLine(){
    line(250,200,350,350);
}

void drawEllipse(){
    int x=250,y=200;
    int start_angle=0, end_angle=360;
    int x_rad=100, y_rad=50;
    ellipse(x,y,start_angle,end_angle,x_rad,y_rad);
}
void drawTriangle(){
    line(300,100,200,200);
    line(300,100,400,200);
    line(200,200,400,200);
}

int main()
{
    int ch;
    
    //gm is a Graphics mode which is a computer display mode that generates images using pixels
    //DETECT is a macro defined in "graphics.h" header file
    int gd = DETECT, gm;
    //initgraph initilizes the graphics system by loading a graphics driver from disk
    initgraph(&gd, &gm, NULL);
    //while(1){
    printf("Graphics Menu : \n");
    printf("1) Point\t2) Line\t3) Circle\t4) Ellipse\t5) Triangle\t6) Rectangle\n");
    printf("Choose an option : \n");
    scanf("%d",&ch);
    //if(ch==7) break;
    switch(ch)
    {
        case 1: drawPoint();break;
        case 2 : drawLine();break;
        case 3 : drawCircle();break;
        case 4 : drawEllipse();break;
        case 5 : drawTriangle();break;
        case 6 : drawRectangle();break;
       
    }
    //}
    wait_for_char();
    closegraph();
    
    return 0;
}

//Compile using
//gcc -o Q1 Q1.c -lgraph
