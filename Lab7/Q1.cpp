//Mid-point Circle Algorithm
#include<GL/glut.h>
#include<stdio.h>
#include<cstdlib>
#include<iostream>
using namespace std;
GLint xc,yc,r;

void setPixel(GLint xcoordinate, GLint ycoordinate)
{
    glBegin(GL_POINTS);
    glVertex2i(xcoordinate,ycoordinate);
    glEnd();
    glFlush();
}

void draw_in_each_oct(GLint xk,GLint yk, GLint xc,GLint yc)
{
    setPixel(xc+xk,yc+yk);
    setPixel(xc+yk,yc+xk);
    setPixel(xc-yk,yc+xk);
    setPixel(xc-xk,yc+yk);
    setPixel(xc-xk,yc-yk);
    setPixel(xc-yk,yc-xk);
    setPixel(xc+yk,yc-xk);
    setPixel(xc+xk,yc-yk);
}
/*
void draw_in_each_oct(GLint x,GLint y)
{
        setPixel(x, y);
		setPixel(x, -1*y);
		setPixel(-1*x, y);
		setPixel(-1*x, -1*y);
		setPixel(y, x);
		setPixel(-1*y, x);
		setPixel(y, -1*x);
		setPixel(-1*y, -1*x);
}*/

void midPtCircle(GLint xc,GLint yc,GLint r)
{
   GLint d,xk,yk;
    d=1-r;
    xk=0;
    yk=r;
    draw_in_each_oct(xk,yk,xc,yc);
    while(xk<=yk)
    {
        //east
        if(d<0)
        {
            d=d+(2*xk)+3;
        }
        //south east
        else
        {
            d+=2*(xk-yk)+5;
            yk=yk-1;
        }
        xk=xk+1;
        draw_in_each_oct(xk,yk,xc,yc);
    }

}


void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    xc=50,yc=20,r=100;
    midPtCircle(xc,yc,r);
}

void myInit(void)
{
    glClearColor(0.0,0.0,0.0,0.0); //clear values for RGBA
    glColor3f(1.0f,0.0f,0.0f); //set current color - RGB
    glPointSize(2.0); //diameters of rasterized points
    glMatrixMode(GL_PROJECTION); // specifies current matrix
    glLoadIdentity();
    gluOrtho2D(-580, 580, -320, 320); //left, right, top, bottom
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Mid Point Circle");
    // readInput();
    glutDisplayFunc(Display);
    myInit();
    glutMainLoop();
    return 0;
}

//g++ Q1.cpp -lGL -lGLU -lglut