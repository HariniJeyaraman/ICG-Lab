#include <GL/glut.h>
 
void displayMe(void)
{
    //clearing the frame buffer 
    //setting bg to white
    glClearColor(1.0,1.0,1.0,1.0); 
    glClear(GL_COLOR_BUFFER_BIT); 
    //triangle
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.4f, 0.4f);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.0, 1, 0.0);
        glVertex3f(-0.5, 0.0, 0.0);
    glEnd();
    glFlush();

    //outer rectangle
        glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.7f, 1.0f);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(-0.5, 0.0, 0.0);
        glVertex3f(-0.5,-5.5, 0.0);
        glVertex3f(0.5, -5.5, 0.0);
    glEnd();
    glFlush();

    //Inner Rectangle
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.12,-0.4);
        glVertex2f(0.12, -0.4);
        glVertex2f(0.12, -1.0);
        glVertex2f(-0.12, -1.0);
        
                    
    glEnd();
    glFlush();

    //inner square left
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.36,-0.4);
        glVertex2f(-0.22, -0.4);
        glVertex2f(-0.22, -0.54);
        glVertex2f(-0.36, -0.54);
    glEnd();
    glFlush();
    
 

    //inner square right
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(0.36,-0.4);
        glVertex2f(0.22, -0.4);
        glVertex2f(0.22, -0.54);
        glVertex2f(0.36, -0.54);
        
                    
    glEnd();
    glFlush();

    //giving outline for triangle
     glLineWidth(2.5);
     glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
     glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.0, 1, 0.0);
        glVertex3f(-0.5, 0.0, 0.0);
    glEnd();
    glFlush();

    //outline to left inner square
    glLineWidth(2.5);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.36,-0.4);
        glVertex2f(-0.22, -0.4);
        glVertex2f(-0.22, -0.54);
        glVertex2f(-0.36, -0.54);
    glEnd();
    glFlush();

    //outline to right inner square
    glLineWidth(2.5);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.36,-0.4);
    glVertex2f(0.22, -0.4);
    glVertex2f(0.22, -0.54);
    glVertex2f(0.36, -0.54);
    glEnd();
    glFlush();

    //outline for inner rectangle
    glLineWidth(2.5);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.12,-0.4);
        glVertex2f(0.12, -0.4);
        glVertex2f(0.12, -1.0);
        glVertex2f(-0.12, -1.0);
    glEnd();
    glFlush();

    //outline for outer rectangle
    glLineWidth(2.5);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(-0.5, 0.0, 0.0);
        glVertex3f(-0.5,-5.5, 0.0);
        glVertex3f(0.5, -5.5, 0.0);
    glEnd();
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
