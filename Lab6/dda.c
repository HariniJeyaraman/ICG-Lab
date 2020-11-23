#include <GL/glut.h>
#include <math.h>
#include<stdio.h>
#include <stdlib.h>

float a, b, c, d;

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
    setpixel((X+0.5), (Y+0.5)); //to find the floor to convert into integer
    X = X + Xinc;
    Y = Y + Yinc;
  }
}

void drawmyline() { DDA(a, b, c, d); }

void init(void) {

  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
//   gluOrtho2D(0.0, 600.0, 0.0, 600.0);
    gluOrtho2D(-580, 580, -320, 320); 
}

int main(int argc, char **argv) {
  printf("DDA\nEnter co-ordinates to draw line : \n");
  printf("X1 = ");
  scanf("%f", &a);
  printf("Y1 = ");
  scanf("%f", &b);
  printf("Xend = ");
  scanf("%f", &c);
  printf("Yend = ");
  scanf("%f", &d);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(400,300);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Digital Differential Analyzer Algorithm");
  init();
  glutDisplayFunc(drawmyline);
  glutMainLoop();
  return 0;
}
//By adding 0.5 before truncating to int, you arrange that numbers with a fractional part greater than 0.5 round up
//Algorithm will generate floatingpoint numbers,  but there are no float numbers in the screen.
//Calculation of float takes extra time compared to integer. So the algorithm is slower
//The points that we are taking are not the accurate points, since we are rounding the float values. 
//So the line in the output will not be a smooth line 

//(10,30), (30,250) m>1
//(0,50), (0,280) m=inf
//(300,70), (0,60) m=0.033
//(300,70), (0,69) m=0.003333333