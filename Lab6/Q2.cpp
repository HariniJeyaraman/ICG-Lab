#include <GL/glut.h>
#include<cstdlib>
#include<math.h>
#include<iostream> 
using namespace std;

int findZone(int x0, int y0, int x1, int y1)
    {
        int dx = x1 - x0, dy = y1 - y0;

        if (abs(dx) >= abs(dy))
        { //zone 0, 3, 4, 7
            if (dy >= 0 && dx >= 0)
                return 0;
            else if (dx < 0 && dy >= 0)
                return 3;
            else if (dx < 0 && dy < 0)
                return 4;
            else return 7;
        } else
        { //zone 1,2,5,6
            if (dy >= 0 && dx >= 0)
                return 1;
            else if (dx < 0 && dy >= 0)
                return 2;
            else if (dx < 0 && dy < 0)
                return 5;
            else return 6;
        }
    }

    

    void drawLine0(int x0, int y0, int x1, int y1, int zone)
    {
        float dx = x1 - x0, dy = y1 - y0;
        float dE = dy;
        float dNE = (dy - dx);
        float d = (dy) - dx/2;
        float x = x0, y = y0;

        glPointSize(2.0f);
        glBegin(GL_POINTS);
        glVertex2f(x, y);

        while (x <= x1)
        {
            if (d < 0)
            {
                //we increment x in every iteration
                x++;
                //dnew = dold + dE
                d = d + dE;

            } else
            {
                x++;
                y++;
                d = d + dNE;
            }
            glVertex2f(x, y);
        }
        glEnd();

    }

    void drawLine1( int x0, int y0, float x1, int y1, int zone)
    {
        float dx = x1 - x0, dy = y1 - y0;
        float dN = -dx;
        float dNE = (dy - dx);
        float d = (dy / 2) - (dx);
        float x = x0, y = y0;

        glPointSize(2.0f);
        glBegin(GL_POINTS);
        glVertex2f(x, y);

        while (y <= y1)
        {
            if (d >= 0)
            {
                y++;
                d = d + dN;

            } else
            {
                y++;
                x++;
                d = d + dNE;

            }
            glVertex2f(x, y);
        }
        glEnd();
    }

    void drawLine2(int x0, int y0, float x1, int y1, int zone)
    {
        float dx = x1 - x0, dy = y1 - y0;
        float dN = -dx;
        float dNW = (-dy - dx);
        float d = (-dy / 2) - (dx);
        float x = x0, y = y0;

        glPointSize(2.0f);
        glBegin(GL_POINTS);
        glVertex2f(x, y);

        while (y <= y1)
        {
            if (d < 0)
            {
                y++;
                d = d + dN;

            } else
            {
                y++;
                x--;
                d = d + dNW;

            }
            glVertex2f(x, y);
        }
        glEnd();
    }

    void drawLine3(int x0, int y0, float x1, int y1, int zone)
    {
        float dx = x1 - x0, dy = y1 - y0;
        float dW = -dy;
        float dNW = (-dy - dx);
        float d = (-dy) - (dx / 2);
        float x = x0, y = y0;

        glPointSize(2.0f);
        glBegin(GL_POINTS);
        glVertex2f(x, y);

        while (x1 <= x)
        {
            if (d >= 0)
            {
                x--;
                d = d + dW;
            } else
            {
                y++;
                x--;
                d = d + dNW;
            }
            glVertex2f(x, y);
        }
        glEnd();
    }

    void drawLine4(int x0, int y0, float x1, int y1, int zone)
    {
        float dx = x1 - x0, dy = y1 - y0;
        float dW = -dy;
        float dSW = (-dy + dx);
        float d = (-dy) + (dx / 2);
        float x = x0, y = y0;

        glPointSize(2.0f);
        glBegin(GL_POINTS);
        glVertex2f(x, y);

        while (x1 <= x)
        {
            if (d >= 0)
            {
                x--;
                y--;
                d = d + dSW;
            } else
            {
                x--;
                d = d + dW;
            }
            glVertex2f(x, y);
        }
        glEnd();
    }

    void drawLine5(int x0, int y0, float x1, int y1, int zone)
    {
        float dx = x1 - x0, dy = y1 - y0;
        float dS = dx;
        float dSW = (-dy + dx);
        float d = -(dy / 2) + (dx);
        float x = x0, y = y0;

        glPointSize(2.0f);
        glBegin(GL_POINTS);
        glVertex2f(x, y);

        while (y1 <= y)
        {
            if (d < 0)
            {
                x--;
                y--;
                d = d + dSW;

            } else
            {
                y--;
                d = d + dS;
            }
            glVertex2f(x, y);
        }
        glEnd();
    }

    void drawLine6(int x0, int y0, float x1, int y1, int zone)
    {
        float dx = x1 - x0, dy = y1 - y0;
        float dS = dx;
        float dSE = (dy + dx);
        float d = (dy / 2) + (dx);
        float x = x0, y = y0;

        glPointSize(2.0f);
        glBegin(GL_POINTS);
        glVertex2f(x, y);

        while (y1 <= y)
        {
            if (d >= 0)
            {
                x++;
                y--;
                d = d + dSE;

            } else
            {
                y--;
                d = d + dS;
            }
            glVertex2f(x, y);
        }
        glEnd();
    }

    void drawLine7(int x0, int y0, float x1, int y1, int zone)
    {
        float dx = x1 - x0, dy = y1 - y0;
        float dE = dy;
        float dSE = (dy + dx);
        float d = (dy) + (dx / 2);
        float x = x0, y = y0;

        glPointSize(2.0f);
        glBegin(GL_POINTS);
        glVertex2f(x, y);

        while (x <= x1)
        {
            if (d >= 0)
            {
                x++;
                d = d + dE;

            } else
            {
                x++;
                y--;
                d = d + dSE;
            }
            glVertex2f(x, y);
        }
        glEnd();
    }


void drawLine(int x0, int y0, int x1, int y1)
    {
        int zone = findZone(x0, y0, x1, y1);
        if (zone == 0)
            drawLine0(x0, y0, x1, y1, 0);
        else if (zone == 1)
            drawLine1(x0, y0, x1, y1, 1);
        else if (zone == 2)
            drawLine2(x0, y0, x1, y1, 2);
        else if (zone == 3)
            drawLine3(x0, y0, x1, y1, 3);
        else if (zone == 4)
            drawLine4(x0, y0, x1, y1, 4);
        else if (zone == 5)
            drawLine5(x0, y0, x1, y1, 5);
        else if (zone == 6)
            drawLine6(x0, y0, x1, y1, 6);
        else if (zone == 7)
            drawLine7(x0, y0, x1, y1, 7);
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
  
    drawLine(0,0,70,20);
    drawLine(0,0,20,70);
    drawLine(0,0,-20,70);
    drawLine(0,0,-70,20);
    drawLine(0,0,-70,-20);
    drawLine(0,0,-20,-70);
    drawLine(0,0,20,-70);
    drawLine(0,0,70,-20);
    
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


//g++ Q2.cpp -lGL -lGLU -lglut 