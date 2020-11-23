#include<stdio.h> 
#include<GL/glut.h>
#include<math.h>

void myInit (void) 
{ 
    // making background color black as first  
    // 3 arguments all are 0.0 
    glClearColor(0.0, 0.0, 0.0, 1.0); 
    // breadth of picture boundary is 1 pixel 
    glPointSize(1.0); 
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
    // setting window dimension in X- and Y- direction 
    gluOrtho2D(-780, 780, -420, 420); 
} 

void drawellipse (float x1, float y1, float a,float b,float step_size) {

    float x2,y2;
    float angle;
    glBegin(GL_POINTS);
    for (angle=1.0f;angle<361.0f;angle+=step_size)
    {
        x2 = x1+sin(angle)*a;
        y2 = y1+cos(angle)*b;
        glVertex2i(round(x2),round(y2));
    }

    glEnd();    
}


void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,1,0);
    drawellipse(50,300,95,50,0.2);//a>b

    glColor3f(1,1,0);
    drawellipse(300,120,50,50,0.5);//circle (a=b)

    glColor3f(0,1,1);
    drawellipse(500,320,50,85,0.5);//b>a

    glColor3f(0,1,0);
    drawellipse(50,90,95,50,3);

    glFlush();

}

int main (int argc, char** argv) 
{ 
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
      
    // giving window size in X- and Y- direction 
    glutInitWindowSize(1366, 768);

    glutInitWindowPosition(0, 0); 
      
    // Giving name to window 
    glutCreateWindow("Line segment"); 
    myInit(); 
      
    glutDisplayFunc(myDisplay); 
    glutMainLoop(); 
    return 1;
} 

//gcc ques2.c -lGL -lGLU -lglut -lm 