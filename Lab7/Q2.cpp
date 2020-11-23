//Mid point ellipse algorithm
#include<GL/glut.h>
#include<stdio.h>
#include<cstdlib>
#include<iostream>
using namespace std;

int xc,yc,a,b;
void setPixel(int x,int y)
{
    glBegin(GL_POINTS);
            glVertex2i(x,y);
    glEnd();
}
//drawing 4 points using symmetry
void draw_in_each_quadrant(int x,int y)
{
    setPixel(x,y);
    setPixel(-1*x,y);
    setPixel(-1*x,-1*y);
    setPixel(x,-1*y);
}
/*
void display(){
   glClear(GL_COLOR_BUFFER_BIT);

   int X=0;
   int Y=b;
   int sa=a*a;
   int sb=b*b;
   int d1 = sb-(sa*b)+0.25*sa;
   draw_in_each_quadrant(X,Y);
   //while(sa*(Y-0.5)>sb*(X+1)){
       while(sa*X<=sa*Y){
       draw_in_each_quadrant(X,Y);   
       if(d1<0){
           d1+=sb*((X<<1)+3);
       }
       else{
           d1+=sb*((X<<1)+3)+sa*(-1*(Y<<1)+2);
           Y--;
       }
       X++;
       draw_in_each_quadrant(X,Y);
   }
   int d2=sb*(X+0.5)*(X+0.5)+sa*(Y-1)*(Y-1)-sa*sb;
   while(Y>0){
       if(d2<0){
           d2+=sb*((X<<1)+2)+sa*(-1*(Y<<1)+3);
           X++;
       }
       else{
           d2+=sa*(-1*(Y<<1)+3);
       }
        Y--;
        draw_in_each_quadrant(X,Y);
       
   }
}*/


void display ()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //Initialize starting point of Region 1
    int x=0;
    int y=b;
    int e=a*a; 
    int g=b*b; 
    // int fx=0;
    // int fy=2*e*b;
    int fx=2*b*b*x,fy=2*a*a*y;
    //initial decision parameter
    int p0=g-e*b+0.25*e;  
    //slope<-1 keep iterating. When slope>-1, go to region 2
    while(fx<fy){
        draw_in_each_quadrant(x,y);
        x++;
        fx=fx+2*g;
        //east
        if(p0<0){
            p0=p0+fx+g;
        }
        //south east
        else{
            y--;
            fy=fy-2*e;
            p0=p0+fx+g-fy; 
        }
    }
    draw_in_each_quadrant(x,y);
    //Region 2
    p0=g*(x+0.5)*(x+0.5)+e*(y-1)*(y-1)-e*g;
    while(y>0)
    {
        y--;
        fy=fy-2*e;
        if(p0>=0)
            p0=p0-fy+e;
        else{
            x++;
            fx=fx+2*e;
            p0=p0+fx-fy+e;
        }
        draw_in_each_quadrant(x,y);
    }
    glFlush();
}


void init(void)
{
    glClearColor(0.0,0.0,0.0,0.0); //clear values for RGBA
    glColor3f(1.0f,1.0f,1.0f); //set current color - RGB
    glPointSize(3.0); //diameters of rasterized points
    glMatrixMode(GL_PROJECTION); // specifies current matrix
    glLoadIdentity();
    gluOrtho2D(-580, 580, -320, 320); //left, right, top, bottom
}

int main (int argc, char **argv)
{
    a=100,b=60;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(0,0);
    glutCreateWindow("MidPoint Ellipse Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}

