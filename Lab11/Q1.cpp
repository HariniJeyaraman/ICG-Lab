//Point Clipping
#include<GL/glut.h>
#include<stdio.h>
#include<cstdlib>
#include <unistd.h>
#include<iostream>
using namespace std;
int ww = 1000, wh = 800;
float fillColor[3] = {1.0, 0.0, 0.0};
float fillColor2[3] = {0.0, 0.0, 1.0};

void putPixel(int x, int y, float f[3]) {
    glPointSize(10.0f);
	glBegin(GL_POINTS); 
		glColor3fv(f);
		glVertex2i(x, y);
	glEnd();
	glFlush();
}

void getPixel(int x, int y, float pixels[3]) {
	glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, pixels);
}

void pointClip(int XY[][2], int n, int Xmin, int Ymin, int Xmax, int Ymax)  
{  
    // cout << "Point inside the viewing pane:" << endl;  
    for (int i = 0; i < n; i++)  
    {  
        if ((XY[i][0] >= Xmin) && (XY[i][0] <= Xmax))  
        {  
            if ((XY[i][1] >= Ymin) && (XY[i][1] <= Ymax)){
                cout <<"[" << XY[i][0] <<","<<XY[i][1]<<"] ";  
                putPixel(XY[i][0], XY[i][1], fillColor);
            }
        }  
    }  
  
}  

void drawRectangle(int x1, int y1, int x2, int y2) {
	glColor3fv(fillColor2);
    glPointSize(4.0f);
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

void display(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    int XY[6][2] = {{10, 10}, {-10, 10}, {400, 100},  
                    {100, 400}, {400, 400}, {100, 40}};  
    int Xmin = 0;  
    int Xmax = 350;  
    int Ymin = 0;  
    int Ymax = 350;  
    pointClip(XY, 6, Xmin, Ymin, Xmax, Ymax);  
    drawRectangle(0,350, 350,0);
}


void myinit()  {  
	glViewport(0,0,ww,wh);  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
    gluOrtho2D(-300,(GLdouble)ww,-200,(GLdouble)wh);  
    glMatrixMode(GL_MODELVIEW);  
 }  

int main(int argc,char** argv)  {  
	glutInit(&argc,argv);  
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    glutInitWindowSize(ww,wh);  
	glutCreateWindow("Point Clipping");  
    glutDisplayFunc(display); ; 
	myinit();  
    glutMainLoop();
    return 0;  
 } 

 //g++ Q1.cpp -lGL -lGLU -lglut