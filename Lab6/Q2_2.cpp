#include <GL/glut.h>
#include<cstdlib>
#include<math.h>
#include<iostream> 
using namespace std;

//Function to check in which zone/octant the given line belongs to
int findZone(int x0, int y0, int x1, int y1)
    {
        int dx = x1 - x0, dy = y1 - y0;
        //zone 0, 3, 4, 7
        //abs(slope)<=1 for these octants
        if (abs(dx) >= abs(dy))
        { 
            if (dy >= 0 && dx >= 0)
                return 0;
            else if (dx < 0 && dy >= 0)
                return 3;
            else if (dx < 0 && dy < 0)
                return 4;
            else return 7;
        } 
        //zone 1,2,5,6
        else
        { 
            if (dy >= 0 && dx >= 0)
                return 1;
            else if (dx < 0 && dy >= 0)
                return 2;
            else if (dx < 0 && dy < 0)
                return 5;
            else return 6;
        }
    }

    
// drawing a line in octant 0
void drawLine0(int x0, int y0, int x1, int y1, int zone)
{
    //We make use of symmetricity property
    //We make every point belonging to any octant fall into the 0th octant
    //So, we take the abs value of the points
    x0=abs(x0);
    y0=abs(y0);
    x1=abs(x1);
    y1=abs(y1);
    //For octants 1,2,5,6 swap the x and y values to make the point fall in 0th octant
    if(zone==1||zone==2||zone==5||zone==6)
    {
        swap(x0,y0);
        swap(x1,y1);
    }
    float dx = x1 - x0, dy = y1 - y0;
    float dE = dy;
    float dNE = (dy - dx);
    float d = (dy) - dx/2; //to decrease any floating point operation, we can assign d as d = 2*(dy) - dx
    float x = x0, y = y0;
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    while (x <= x1)
    {
        //choose east
        if (d < 0)
        {   //we increment x in every iteration
            x++;
            //dnew = dold + dE
            d = d + dE;
        } 
        //choose NE
        else
        {
            x++;
            y++;
            d = d + dNE;
        }
        if(zone==0)
        glVertex2f(x, y);
        //Using symmetricity to draw in other octants
        else if(zone==1)
        cout<<y<<" "<<x<<"\n";
        //glVertex2f(y,x);
        else if(zone==2)
        glVertex2f(-1*y,x);
        else if(zone==3)
        glVertex2f(-1*x,y);
        else if(zone==4)
        glVertex2f(-1*x,-1*y);
        else if(zone==5)
        glVertex2f(-1*y,-1*x);
        else if(zone==6)
        glVertex2f(y,-1*x);
        else if(zone==7)
        glVertex2f(x,-1*y);
        
    }
    glEnd();

}

void drawLine(int x0, int y0, int x1, int y1)
{
    int zone = findZone(x0, y0, x1, y1);
    drawLine0(x0, y0, x1, y1, zone);
    
}


void myInit (void) 
{ 
    glClearColor(0.0, 0.0, 0.0, 1.0); 
    glColor3f(1.0, 1.0, 1.0); 
    glPointSize(1.0); 
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
    // setting window dimension in X- and Y- direction 
    gluOrtho2D(-580, 580, -320, 320); 
} 

void displayMe()
{
    
    glColor3f(0.6f, 0.6f, 0.6f);
    //drawing the same line in all 8 octants
    // drawLine(0,0,70,20); //octant 0
    // drawLine(0,0,20,70); //octant 1
    // drawLine(0,0,-20,70); //octant 2
    // drawLine(0,0,-70,20); //octant 3
    // drawLine(0,0,-70,-20); //octant 4
    // drawLine(0,0,-20,-70); //octant 5
    // drawLine(0,0,20,-70); //octant 6
    // drawLine(0,0,70,-20); //octant 7
    drawLine(2,3,5,10);
    
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


//g++ Q2_2.cpp -lGL -lGLU -lglut 