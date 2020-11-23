#include <GL/glut.h>
#include<cstdlib>
#include<math.h>
#include<iostream> 
using namespace std;
#define PI 3.142857 

void drawLine(GLint x1, GLint y1, GLint x2, GLint y2){
	///calculating slope
    if(x2-x1==0){
        for(float i=y1;i<=y2;i++){
            glBegin(GL_POINTS);
            // glColor3f(0.6f, 0.6f, 0.6f);
            glVertex2i(x1,i);
        }
        glEnd();
        return;
    }
    float m = (y2-y1)/(x2-x1);
    cout<<"Slope : "<<m<<"\n";
    float b = -x1 * m + y1;
    cout<<"Intercept : "<<b<<"\n";
    
    if(m<1){
        for(float i = x1;i<=x2;i+=2){
        // cout<<i<<"\n";
        int y = m*i + b;
        glBegin(GL_POINTS);
        // glColor3f(0.6f, 0.6f, 0.6f);
        glVertex2i(i,y);
    }
	glEnd();
    }
    else{
        glBegin(GL_POINTS);
        cout<<"Entered";
        for(float i=y1;i<=y2;i+=1){
            float x = (i-b)/m;
            
            // glColor3f(0.6f, 0.6f, 0.6f);
            glVertex2i(round(x),i);
        }
        glEnd();
    }
    
}

void myInit (void) 
{ 
    // making background color black as first  
    // 3 arguments all are 0.0 
    glClearColor(0.0, 0.0, 0.0, 1.0); 
      
    // making picture color green (in RGB mode), as middle argument is 1.0 
    glColor3f(1.0, 1.0, 1.0); 
      
    // breadth of picture boundary is 1 pixel 
    glPointSize(1.0); 
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
      
    // setting window dimension in X- and Y- direction 
    gluOrtho2D(-580, 580, -320, 320); 
} 


void displayMe()
{
    
    glColor3f(0.6f, 0.6f, 0.6f);
    //m>1
    // drawLine(10,50,30,90);
    //m<1
    // drawLine(300,50,330,250);
    //horizontal line
    drawLine(300,0,500,0);
    //Vertical line
    // drawLine(0,100,0,300);
    glFlush();
}

int main(int argc, char** argv)
{
    //glutInit is used to initialize the GLUT library. 
      glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
      
    // giving window size in X- and Y- direction 
    glutInitWindowSize(1366, 768); 
    glutInitWindowPosition(0, 0); 
      
    // Giving name to window 
    glutCreateWindow("Line"); 
    myInit(); 
      
    glutDisplayFunc(displayMe); 
    glutMainLoop();
   
    return 0;
}

//g++ Q1.cpp -lGL -lGLU -lglut 