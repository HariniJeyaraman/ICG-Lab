#include <stdio.h> 
#include <math.h> 
#include <GL/glut.h> 
/*
Input for rectangle : (100,150) (300,150) (300,250) (100,250)
Example : 
Rotation : by 90 degrees about the centre

Scaling : Uniform scaling by 1.5 in x direction and 1.5 by y direction
*/

void myInit(void) 
{ 
    glClearColor(0,0,0,0); 
    glMatrixMode(GL_PROJECTION); 
      
    glLoadIdentity(); 
    gluOrtho2D(0,800,0,600); 
    glClear(GL_COLOR_BUFFER_BIT); 
} 

//Rotate the rectangle about its centre given angle theta
void RotatePoint(int px[], int py[], int cx, int cy,int n,float theta) 
{ 
    //float theta = 0.0; 
    int i=0,xf,yf;
    while (i<n) { 
        //theta = theta + thetaSpeed; 
        if (theta >= (2.0 * 3.14159)) 
            theta = theta - (2.0 * 3.14159); 

        xf = cx + (int)((float)(px[i] - cx) * cos(theta))+((float)(py[i] - cy) * sin(theta)); 
        yf = cy + (int)((float)(px[i] - cx) * sin(theta))- ((float)(py[i] - cy) * cos(theta));
        px[i]=xf;
        py[i]=yf;
        i++;
    } 
}

//Scale rectangle by sx,sy
void scalePoint(int px[], int py[], float sx, float sy,int n) 
{ 
    int fx, fy,i=0; 
    while (i<n) {
        px[i] = px[i] * sx; 
        py[i] = py[i] * sy; 
    i++;
    } 
}  
  
void RotateScale(int px[],int py[],int cx, int cy,int n,float theta,float sx, float sy){
    int i=0,xf,yf;
    while(i<n){
         if (theta >= (2.0 * 3.14159)) 
            theta = theta - (2.0 * 3.14159); 
        //rotating
        xf = sx*(cx + (int)((float)(px[i] - cx) * cos(theta))+((float)(py[i] - cy) * sin(theta))); 
        yf = sy*(cy + (int)((float)(px[i] - cx) * sin(theta))- ((float)(py[i] - cy) * cos(theta)));
        // scaling
        px[i]=xf;
        py[i]=yf;
        i++;
    }
}

void display(void) 
{ 
    int ch;
    do
    { 
    printf("\n1. Rotation and scale using 2 transformations"
           "\n2. Rotate and scale with 1 transform"
           "\n3. Exit\n"
           "Enter your choice: "); 
    scanf("%d", &ch);

    glClear(GL_COLOR_BUFFER_BIT);
  
    int X[5] = {100, 300, 300, 100};
    int Y[5] = {150, 150, 250, 250};
    int Tx[5],Ty[5];
    int n=4;
    int sumx=0,s1=0,s2=0,sumy=0;
    for(int i=0;i<n;i++)
    {
        Tx[i]=X[i];Ty[i]=Y[i];
        
        sumx+=Tx[i];
        sumy+=Ty[i];
    }
    
    glColor3f(1.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<n;i+=1)
    {
        glVertex2i( X[i], Y[i]); 
    }
    glEnd();
        
    glFlush();
     float angle,sx,sy;
    switch (ch) { 
    case 1: 
    //First apply rotation and then scaling
    //sumx/n, sumy/n is the centre of the rectangle
        printf("Enter angle : ");
        scanf("%f",&angle);
        RotatePoint(Tx,Ty,sumx/n, sumy/n,n,angle); //1.5708 rotate by 90 degrees
        glPointSize(2.0);
        glBegin(GL_POINTS);    
        glVertex2i(sumx/n, sumy/n);     
        glEnd(); 
        //Sx=1.5 and Sy=1.5 (uniform scaling)
        printf("Enter scaling factors : ");
        scanf("%f%f", &sx,&sy);
        scalePoint(Tx,Ty,sx,sy,n); 
        break;
    case 2 : 
    //Rotation and scaling together
        RotateScale(Tx,Ty,sumx/n, sumy/n,n,angle,sx,sy);
        glPointSize(2.0);
        glBegin(GL_POINTS);    
        glVertex2i(sumx/n, sumy/n);     
        glEnd(); 
        break;
    }
    glColor3f(1,1,0); 
   
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<n;i+=1)
    {
        glVertex2i( Tx[i], Ty[i]); 
    }     
    glEnd();    
    glFlush();
 }while(ch!=4);
   glFlush();
} 
  
int main(int argc, char** argv) 
{ 
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    glutInitWindowSize(800,600); 
    glutInitWindowPosition(100, 150); 
    glutCreateWindow("Geometric Transformations"); 
    myInit(); 
    glutDisplayFunc(display); 
    glutMainLoop(); 
   
    return 0;
} 