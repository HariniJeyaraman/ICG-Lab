//Line Clipping
#include<GL/glut.h>
#include<stdio.h>
#include<cstdlib>
#include <unistd.h>
#include<iostream>
using namespace std;
int ww = 1000, wh = 800;
int c=0,l=0;

int points[3][4] = {{10,10,400,100}, {100,40,350,350}, {-10,10,400,400}};
float fillColor[3] = {0.0, 1.0, 0.0};
float fillColor2[3] = {1.0, 0.0, 0.0};

void putPixel(int x, int y, float f[3]) {
    glPointSize(4.0f);
	glBegin(GL_POINTS); 
		glColor3fv(f);
		glVertex2i(x, y);
	glEnd();
	glFlush();
}

void getPixel(int x, int y, float pixels[3]) {
	glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, pixels);
}

// Defining region codes 
const int INSIDE = 0; // 0000 
const int LEFT = 1; // 0001 
const int RIGHT = 2; // 0010 
const int BOTTOM = 4; // 0100 
const int TOP = 8; // 1000 
  
//Bounding Rectangle coordinates of Diagonal points
const int x_max = 350; 
const int y_max = 350; 
const int x_min = 0; 
const int y_min = 0; 
  
//Function to compute region code for a point(x, y) 
int computeCode(double x, double y) 
{ 
    // initialized as being inside 
    int code = INSIDE; 
  
    if(x < x_min) // to the left of rectangle 
        code |= LEFT; 
    else if(x > x_max) // to the right of rectangle 
        code |= RIGHT; 
    if(y < y_min) // below the rectangle 
        code |= BOTTOM; 
    else if(y > y_max) // above the rectangle 
        code |= TOP; 
  
    return code; 
} 
  
//Implementing Cohen-Sutherland algorithm 
//Clipping a line from P1 = (x1, y1) to P2 = (x2, y2) 
void cohenSutherlandClip(double x1, double y1, double x2, double y2) 
{ 
  
    //Compute region codes for P1, P2 
    int code1 = computeCode(x1, y1); 
    int code2 = computeCode(x2, y2); 
  
    //Initialize line as outside the rectangular window 
    bool accept = false; 
  
    while (true) { 
        //Trivially Accepted - Case 1
        if ((code1 == 0) && (code2 == 0)) { 
            // If both endpoints lie within rectangle 
            accept = true; 
            break; 
        } 
        //Trivially Rejected - Case 2
        else if (code1 & code2) { 
            // If both endpoints are outside rectangle, 
            // in same region 
            break; 
        } 
        //Case 3
        else { 
            // Some segment of line lies within the rectangle 
            int code_out; 
            double x, y; 
  
            //At least one endpoint is outside the rectangle, pick it. 
            if (code1 != 0) 
                code_out = code1; 
            else
                code_out = code2; 
  
            //Find intersection point; 
            //using formulas y = y1 + slope * (x - x1), 
            //x = x1 + (1 / slope) * (y - y1) 
            if (code_out & TOP) { 
                //point is above the clip rectangle 
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1); 
                y = y_max; 
            } 
            else if (code_out & BOTTOM) { 
                //point is below the rectangle 
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1); 
                y = y_min; 
            } 
            else if (code_out & RIGHT) { 
                //point is to the right of rectangle 
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1); 
                x = x_max; 
            } 
            else if (code_out & LEFT) { 
                //point is to the left of rectangle 
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1); 
                x = x_min; 
            } 
  
            //Now intersection point x, y is found 
            //We replace point outside rectangle 
            //by intersection point 
            if (code_out == code1) { 
                x1 = x; 
                y1 = y; 
                code1 = computeCode(x1, y1); 
            } 
            else { 
                x2 = x; 
                y2 = y; 
                code2 = computeCode(x2, y2); 
            } 
        } 
    } 
    if (accept) { 
        cout << "Line accepted from " << x1 << ", "<< y1 << " to " << x2 << ", " << y2 << endl; 
            glClear(GL_COLOR_BUFFER_BIT);  
            glColor3f(0.0,1.0,0.0); 
            glPointSize(5.0);  
         glBegin(GL_LINES);
            glVertex2f(x1,y1);
            glVertex2f(x2,y2);
        glEnd();
        glFlush();
        //Here the user can add code to display the rectangle 
        //along with the accepted (portion of) lines 

    } 
    else
        cout << "Line rejected" << endl; 
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

void drawLine(int x1, int y1, int x2, int y2){
    glColor3fv(fillColor2);
    glLineWidth(0.5);
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
    glFlush();
}

void mouse(int btn, int state, int x, int y) {
    if(btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN){
        if(l==0){
        drawLine(points[l][0],points[l][1], points[l][2], points[l][3]);
        l++;
        }
        else{
            drawLine(points[l][0],points[l][1], points[l][2], points[l][3]);
            l++;
        }
        
    }
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        
        //for(int i=0;i<3;i++){
            if(c==0){
                cohenSutherlandClip(points[c][0],points[c][1], points[c][2], points[c][3]); 
                c++;
            }
            else{
                cohenSutherlandClip(points[c][0],points[c][1], points[c][2], points[c][3]);
                c++;
            }
                
                drawRectangle(0,350, 350,0);
        //}
		//cohenSutherlandClip(10, 10, 400, 100); 
        drawRectangle(0,350, 350,0);
	}
}


void display(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawRectangle(0,350, 350,0);
    //drawLine(10, 10, 400, 100); 
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
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;  
 } 

 //g++ Q2.cpp -lGL -lGLU -lglut