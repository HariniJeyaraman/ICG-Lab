#include <GL/glut.h>
#include<math.h> 
#define PI 3.142857 

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int triangleAmount = 120; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}

void displayMe()
{
    //clearing the frame buffer 
    //setting bg to white
    glClearColor(1.0,1.0,1.0,1.0); 
    glClear(GL_COLOR_BUFFER_BIT); 
    glLineWidth(2.5);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.20,0);
        glVertex2f(-0.20,0.30);
        glVertex2f(0.80,0.30);
        glVertex2f(0.80,0);
    glEnd();
    glLineWidth(2.5);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0,0.3);
    glVertex2f(0.1,0.7);
    // glVertex2f(0.7,0.5);
    glEnd();
    glFlush();

    glLineWidth(2.5);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.1,0.7);
    glVertex2f(0.7,0.7);
    // glVertex2f(0.7,0.5);
    glEnd();

    glLineWidth(2.5);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.80,0.30);
    glVertex2f(0.7,0.7);
    // glVertex2f(0.7,0.5);
    glEnd();

    glLineWidth(2.5);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.03,0.32);
    glVertex2f(0.12,0.68);
    glEnd();

    glLineWidth(2.5);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.12,0.67);
    glVertex2f(0.3,0.67);
    glEnd();

    glLineWidth(2.5);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.3,0.67);
    glVertex2f(0.3,0.32);
    glEnd();

     glLineWidth(2.5);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.34,0.67);
    glVertex2f(0.68,0.67);
    glEnd();

    glLineWidth(2.5);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.03,0.32);
    glVertex2f(0.3,0.32);
    glEnd();

    glLineWidth(2.5);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.34,0.67);
    glVertex2f(0.34,0.32);
    glEnd();

    glLineWidth(2.5);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.77,0.32);
    glVertex2f(0.68,0.67);
    glEnd();

    glLineWidth(2.5);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.77,0.32);
    glVertex2f(0.34,0.32);
    glEnd();


    //Outer thick circle
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(0.1,0.0,0.135);
    glFlush();

    glColor3f(0.6f, 0.6f, 0.6f);
    drawFilledCircle(0.1,0.0,0.12);
    glFlush();
    
    //Outer thick circle
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(0.6,0.0,0.135);
    glFlush();

    glColor3f(0.6f, 0.6f, 0.6f);
    drawFilledCircle(0.6,0.0,0.12);
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