#include <GL/glut.h>
#include<math.h> 
#define PI 3.142857 

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int triangleAmount = 600; //# of segments
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_POINTS);
		// glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            x + ((radius+0.5) * cos(i *  twicePi / triangleAmount)), 
			    y + ((radius-0.5) * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
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
    gluOrtho2D(-780, 780, -420, 420); 
} 

void displayMe()
{
    glColor3f(0.6f, 0.6f, 0.6f);
    drawFilledCircle(0.1,0.0,0.12);
    glFlush();
}

int main(int argc, char** argv)
{
    //glutInit is used to initialize the GLUT library. 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("LAB3");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}