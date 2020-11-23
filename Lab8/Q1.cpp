#include<GL/glut.h>
#include<stdio.h>
#include<cstdlib>
#include <unistd.h>
#include<iostream>
using namespace std;
//global counter to count the number of clicks
int c=0;
float fillColor[3] = {0.0, 0.0, 0.3};
float fillColor2[3] = {2.0, 2.0, 0.0};
float borderColor[3] = {4.0, 0.0, 0.0};
int xi, yi;
int ww = 600, wh = 400;

void putPixel(int x, int y, float f[3]) {
	glBegin(GL_POINTS); 
		glColor3fv(f);
		glVertex2i(x, y);
	glEnd();
	glFlush();
}

void getPixel(int x, int y, float pixels[3]) {
	glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, pixels);
}

//4 neighbors
void boundaryFill(int x, int y, float fillColor[3], float borderColor[3]) {
	float interiorColor[3];
	getPixel(x, y, interiorColor);
	if((interiorColor[0] != borderColor[0]) && (interiorColor[1] != borderColor[1]) && (interiorColor[2] != borderColor[2]) && 
		(interiorColor[0] != fillColor[0]) && (interiorColor[1] != fillColor[1]) && (interiorColor[2] != fillColor[2])) {
			putPixel(x, y, fillColor);
			boundaryFill(x+1, y, fillColor, borderColor);
			boundaryFill(x-1, y, fillColor, borderColor);
			boundaryFill(x, y+1, fillColor, borderColor);
			boundaryFill(x, y-1, fillColor, borderColor);
		}
}

//glutMouseFunc sets the mouse callback for the current window.
//When a user presses and releases mouse buttons in the window, each press and each release generates a mouse callback
//The x and y callback parameters indicate the window relative coordinates when the mouse button state changed
//OpenGL uses a world coordinate system with origin at the bottom left
//Therefore you must invert  the y coordinate returned by callback by the height of window:
//y = h – y;

void mouse1(int btn, int state, int x, int y) {
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		xi = x;
		yi= wh - y;
        //if its the first click, call boundary fill algo with blue color
        //else call boundary fill algo with yellow color
        if(c==0){
		boundaryFill(xi, yi, fillColor, borderColor);
        c++;
        }
        else
        boundaryFill(xi, yi, fillColor2, borderColor);
	}
}

void drawRectangle(int x1, int y1, int x2, int y2) {
	glColor3fv(borderColor);
	glBegin(GL_LINES);
		glVertex2i(x1, y1);
		glVertex2i(x1, y2);

		glVertex2i(x2, y1);
		glVertex2i(x2, y2);

		glVertex2i(x1, y1);
		glVertex2i(x2, y1);

		glVertex2i(x1, y2);
		glVertex2i(x2, y2);
	glEnd();
	glFlush();
}

void drawTriangle()//int x1, int y1, int x2, int y2, int x3, int y3)
{
  glColor3fv(borderColor);
  glBegin(GL_LINES);			
  glVertex2i(400,125);			
  glVertex2i(450,200);

  glVertex2i(450,200);
  glVertex2i(500,125);

  glVertex2i(500,125);
  glVertex2i(400,125);
  glEnd();	
  glFlush();

}

void display() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawRectangle(150, 250, 200, 300);
    glFlush();
    drawTriangle();
    glFlush();   
}

void myinit()  {  
	glViewport(0,0,ww,wh);  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
    gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);  
    glMatrixMode(GL_MODELVIEW);  
 }  

int main(int argc,char** argv)  {  
	glutInit(&argc,argv);  
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    glutInitWindowSize(ww,wh);  
	glutCreateWindow("Boundary-Fill");  
    glutDisplayFunc(display); ; 
	myinit();  
    glutMouseFunc(mouse1);
    glutMainLoop();
    return 0;  
 } 

 //g++ Q1.cpp -lGL -lGLU -lglut