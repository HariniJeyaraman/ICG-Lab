#include<GL/glut.h>
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<cmath>
using namespace std;

float x[5] = {450, 112.5, 250, 650, 787.5};
float y[5] = {100, 500, 600,600, 500};

void rotate(float A){
    glColor3f(0.0f,1.0f,0.0f);
    glBegin(GL_POLYGON);
    
    for(int i=0;i<5;i++){
        glVertex2f(x[i]*cos(A)-y[i]*sin(A), x[i]*sin(A)+y[i]*cos(A));
    }
    glEnd();
    glFlush();
}

void scale(float s){
    glColor3f(0.0f,1.0f,1.0f);
    glBegin(GL_POLYGON);
    for(int i=0;i<5;i++){
        glVertex2f(x[i]*s, y[i]*s);
    }
    glEnd();
    glFlush();
}

void translate(int a, int b){
   
    glColor3f(0.0f,0.0f,1.0f);
    glBegin(GL_POLYGON);
     for(int i=0;i<5;i++){
        glVertex2f(x[i]+a, y[i]+b);
    }
    glEnd();
    glFlush();
}
void drawPolygon(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    for(int i=0;i<5;i++){
        glVertex2f(x[i], y[i]);
    }
    glEnd();
    glFlush();
}
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
     int ch;
    do{
       
    cout<<"Enter your choice : \n 1) Translate 2) Rotate 3) Scale 4) Exit\n";
    cin>>ch;
    switch(ch){
        case 1 : drawPolygon();
                 translate(-600,-700);
                 glFlush();break;
        case 2 : drawPolygon();
                 rotate(0.261799);
                 glFlush();break;
        case 3 : drawPolygon();
                 scale(0.5);
                 glFlush();break;
        case 4 : break;
    }
    }while(ch!=4);
    
}

void myInit(void)
{
    glClearColor(0.0,0.0,0.0,0.0); //clear values for RGBA
    glColor3f(1.0f,0.0f,0.0f); //set current color - RGB
    glPointSize(2.0); //diameters of rasterized points
    glMatrixMode(GL_PROJECTION); // specifies current matrix
    glLoadIdentity();
    gluOrtho2D(-780, 1000, -820, 1200); //left, right, top, bottom
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Polygon");
    // readInput();
    glutDisplayFunc(Display);
    myInit();
    glutMainLoop();
    return 0;
}

//g++ Q1.cpp -lGL -lGLU -lglut