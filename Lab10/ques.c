#include <stdio.h> 
#include <math.h> 
#include <GL/glut.h> 


void myInit(void) 
{ 
    glClearColor(0,0,0,0); 
    glMatrixMode(GL_PROJECTION); 
      
    glLoadIdentity(); 
    gluOrtho2D(0,800,0,600); 
    glClear(GL_COLOR_BUFFER_BIT); 
} 

void translatePoint(int px[], int py[], int tx, int ty,int n) 
{ 
    int i=0;
    while(i<n)
    {
        if (px[i] <640 || px[i] > 0 || py[i] < 400 || py[i] > 0) { 
            px[i] = px[i] + tx; 
            py[i] = py[i] + ty; 
        } 
        i++;
    }   
} 
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
void scalePoint(int px[], int py[], float sx, float sy,int n) 
{ 
    int fx, fy,i=0; 
    while (i<n) {

        px[i] = px[i] * sx; 
        py[i] = py[i] * sy; 
    i++;
  
    } 
}  
  
void display(void) 
{ 
    int ch;
    do
    { 
    printf("\n1. Translation"
           "\n2. Rotation"
           "\n3. Scaling\n"
           "\n4. Exit\n\tEnter your choice: "); 
    scanf("%d", &ch);

    glClear(GL_COLOR_BUFFER_BIT);
    int X[6]={100,110,200,290,300},Tx[6],Ty[6];
    int Y[6]={150,250,300,250,150};
    int n=5;
    int sumx=0,s1=0,s2=0,sumy=0;
    for(int i=0;i<n;i++)
    {
        Tx[i]=X[i];Ty[i]=Y[i];
        
        sumx+=Tx[i];
        sumy+=Ty[i];
    }
    
    glColor3f(1.0f,0.0f,0.0f);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<=3;i+=1)
    {
        glVertex2i( X[i], Y[i]); 
        glVertex2i( X[i+1], Y[i+1]); 
    }
    glEnd();
        
    //glFlush();
     
    switch (ch) { 
    case 1: 
        translatePoint(Tx,Ty,100,100 ,n); 
        break; 
    case 2: 
        RotatePoint(Tx,Ty,sumx/n, sumy/n,n,360);
        glPointSize(2.0);
        glBegin(GL_POINTS);    
        glVertex2i(sumx/n, sumy/n);     
        glEnd();  
        break; 
    case 3: 
        scalePoint(Tx,Ty,1.5,1.5,n); 
        break;
    }
    glColor3f(1,1,0); 
   
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<=3;i+=1)
    {
        glVertex2i( Tx[i], Ty[i]); 
        glVertex2i( Tx[i+1], Ty[i+1]); 
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