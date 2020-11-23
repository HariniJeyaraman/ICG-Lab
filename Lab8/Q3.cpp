#include<GL/glut.h>
#include<stdio.h>
#include<cstdlib>
#include <unistd.h>
#include<iostream>
using namespace std;
float borderColor[3] = {1.0, 0.0, 0.0};
float fillColor[3] = {0.0, 1.0, 0.0};
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

void drawRectangle(int x1, int y1, int x2, int y2) {
	glColor3fv(borderColor);
	glBegin(GL_POLYGON);
		glVertex2i(x1, y1);
		glVertex2i(x1, y2);
        glVertex2i(x2, y2);
		glVertex2i(x2, y1);
	glEnd();
	glFlush();
}

void floodFill(int x, int y, float fillColor[3], float borderColor[3]) {
	float interiorColor[3];
	getPixel(x, y, interiorColor);
    // cout<<interiorColor[0]<<" "<<interiorColor[1]<<" "<<interiorColor[2]<<"\n";
	if((interiorColor[0] == borderColor[0]) && (interiorColor[1] == borderColor[1]) && (interiorColor[2] == borderColor[2])) {
			putPixel(x, y, fillColor);
			floodFill(x+1, y, fillColor, borderColor);
			floodFill(x-1, y, fillColor, borderColor);
			floodFill(x, y+1, fillColor, borderColor);
			floodFill(x, y-1, fillColor, borderColor);
		}
}
void mouse(int btn, int state, int x, int y) {
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        cout<<"Mouse\n";
		xi = x;
		yi= wh - y;
		floodFill(xi, yi, fillColor, borderColor);
	}
}

void display() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawRectangle(150, 250, 300, 350);
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
	glutCreateWindow("flood-Fill");  
    glutDisplayFunc(display);  
	myinit();  
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;  
 } 

 //g++ Q3.cpp -lGL -lGLU -lglut