#include<GL/glut.h>
#include<stdio.h>
#include<cstdlib>
#include <unistd.h>
#include<iostream>
using namespace std;
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

//Using 8 neighbors
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
            boundaryFill(x+1, y+1, fillColor, borderColor);
            boundaryFill(x-1, y-1, fillColor, borderColor);
            boundaryFill(x+1, y-1, fillColor, borderColor);
            boundaryFill(x-1, y+1, fillColor, borderColor);
		}
       
}

//to thicken the border of the polyon, to prevent leaking
void DDA(int X1, int Y1, int X2, int Y2) {
  int I;
  float Length;
  float X, Y, Xinc, Yinc;
  //Length is the step size
  Length = abs(X2 - X1);
  if (abs(Y2 - Y1) > Length)
    Length = abs(Y2 - Y1);
  Xinc = (X2 - X1) / (Length);
  Yinc = (Y2 - Y1) / (Length);
  X = X1;
  Y = Y1;
  for (I = 0; I < Length; I++) {
    putPixel((X+1),(Y),borderColor);
    putPixel((X-1),(Y),borderColor);
    putPixel((X),(Y+1),borderColor);
    putPixel((X),(Y-1),borderColor);
    X = X + Xinc;
    Y = Y + Yinc;
  }
}


void mouse(int btn, int state, int x, int y) {
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		xi = x;
		yi= wh - y;
        DDA(400,125,450,200);
        DDA(450,200,500,125);
        DDA(500,125,400,125);
		boundaryFill(xi, yi, fillColor, borderColor);
	}
}

void drawTriangle()//int x1, int y1, int x2, int y2, int x3, int y3)
{
  glColor3fv(borderColor);
//We can uncomment the below line to prevent leaking (thickening the border of the polygon)
//   glLineWidth(3);
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
    drawTriangle();       
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
    glutDisplayFunc(display);  
	myinit();  
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;  
 } 

 //g++ Q2.cpp -lGL -lGLU -lglut