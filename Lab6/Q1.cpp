#include <GL/glut.h>
#include<cstdlib>
#include<math.h>
#include<iostream> 
using namespace std;

float a, b, c, d;
//Function to specify a vertex
void setpixel(GLint xCoordinate, GLint yCoordinate) {
  glBegin(GL_POINTS);
  glVertex2i(xCoordinate, yCoordinate);
  glEnd();
  glFlush();
}

void DDA(int X1, int Y1, int X2, int Y2) {
  int I;
  float Length;
  float X, Y, Xinc, Yinc;
  //Length is the step size
  Length = abs(X2 - X1);
  if (abs(Y2 - Y1) > Length)
    Length = abs(Y2 - Y1);
  Xinc = (X2 - X1) / (Length);
  Yinc = (Y2 - Y1) / (Length);
  X = X1;
  Y = Y1;
  for (I = 0; I < Length; I++) {
    //By adding 0.5 before truncating to int, you arrange that numbers with a fractional part greater than 0.5 round up
    setpixel((X+0.5), (Y+0.5)); //We can also use round()
    X = X + Xinc;
    Y = Y + Yinc;
  }
}

void display() { 
    DDA(a, b, c, d); 
}

void init(void) {
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(-580, 580, -320, 320); 
}

int main(int argc, char **argv) {
  cout<<"DDA\nEnter co-ordinates to draw line : \n";
  cout<<"X1 = ";
  cin>>a;
  cout<<"Y1 = ";
  cin>>b;
  cout<<"X2 = ";
  cin>>c;
  cout<<"Y2 = ";
  cin>>d;
  //glutInit is used to initialize the GLUT library. 
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  // giving window size in X- and Y- direction 
  glutInitWindowSize(400,300);
  glutInitWindowPosition(0, 0);
  // Giving name to window 
  glutCreateWindow("DDA");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}

//Algorithm will generate floating point numbers,  but there are no float numbers in the screen.
//Although, DDA is better than brute force, and avoids floating point multiplication, floating point addition is still used here.
//Calculation of float takes extra time compared to integer. So the algorithm is slow
//The points that we are taking are not the accurate points, since we are rounding the float values. 
//So the line in the output will not be a smooth line and may be zig-zag

//(10,30), (30,250) m>1
//(0,50), (0,280) m=inf
//(300,70), (0,60) m=0.033
//(300,70), (0,69) m=0.003333333