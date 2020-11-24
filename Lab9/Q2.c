// Scanline Polygon fill Algorithm 
#include <stdio.h> 
#include <math.h> 
#include <GL/glut.h> 
#define maxHt 800 
#define maxWd 600 
#define maxVer 10000 
FILE *fp; 

typedef struct edgebucket 
{ 
	int ymax; //max y coordinate of edge 
	float xofymin; //x coordinate of lowest edge point updated only in aet 
	float delx; // diff in x coordinate
    float dely; //diff in y coordinate
    int sign; 
}EdgeBucket; 

//The array will give the scanline number and the edge table (ET) with edges entries are sorted in increasing y and x of the lower end 
typedef struct EdgeTable 
{ 
	int e; //no. of edgebucket
	EdgeBucket b[maxVer]; 
}et; 

et EdgeTable[maxHt], aet; 

/* Function to sort an array using bubble sort*/
void sort(et *ett) 
{ 
    int i,j; 
    EdgeBucket temp;  
	for (i = 1; i < ett->e; i++){
		for(int j=1; j<ett->e;j++){
			if(ett->b[j].xofymin < ett->b[j-1].xofymin){
				temp = ett->b[j];
				ett->b[j] = ett->b[j-1];
				ett->b[j-1] = temp;
			}
		}
	}
} 
  
void storeInTuple (et *rec,int ym,int xm,float delx,float dely,int sign) 
{ 
    (rec->b[(rec)->e]).ymax = ym; 
    (rec->b[(rec)->e]).xofymin = (float)xm; 
    (rec->b[(rec)->e]).delx = delx;
    (rec->b[(rec)->e]).dely = dely;
    (rec->b[(rec)->e]).sign = sign; 
    sort(rec);  
    (rec->e)++;     
} 

void storeEdge(int x1,int y1, int x2, int y2) 
{ 
    float m,minv,delx,dely; 
    int sign;
    int ymaxTS,xwithyminTS, scanline; //ts stands for to store 
      
    if (x2==x1) 
    { 
        minv=0.000000; 
    } 
    else
    {  
     dely=y2-y1;
     delx=x2-x1;
    // horizontal lines are not stored in edge table 
    if (y2==y1) 
        return; 
    if(((delx >0)&&(dely>0)) || (delx<0) && (dely<0))
     sign=1;
    else
      sign=-1;
    delx=abs(delx);
    dely=abs(dely);

    } 
    if (y1>y2) 
    { 
        scanline=y2; 
        ymaxTS=y1; 
        xwithyminTS=x2; 
    } 
    else
    { 
        scanline=y1; 
        ymaxTS=y2; 
        xwithyminTS=x1;      
    }  
    storeInTuple(&EdgeTable[scanline],ymaxTS,xwithyminTS,delx,dely,sign);  
}

void removeEdgeByYmax(et *Tup,int yy) 
{ 
    int i,j; 
    for (i=0; i< Tup->e; i++) 
    { 
        if (Tup->b[i].ymax == yy) 
        {               
            for ( j = i ; j < Tup->e -1 ; j++ ) 
                { 
                Tup->b[j].ymax =Tup->b[j+1].ymax; 
                Tup->b[j].xofymin =Tup->b[j+1].xofymin; 
                Tup->b[j].delx = Tup->b[j+1].delx;
                Tup->b[j].dely = Tup->b[j+1].dely; 
                Tup->b[j].sign = Tup->b[j+1].sign;
                } 
                Tup->e--; 
            i--; 
        } 
    } 
}      
float delc=0,c=0;
//Avoiding Floating Point operations and performing only Integer operations to find the next edge point
int findnextedgepoint(int x,float delx,float dely,int sign)
{
    
    if(delx < dely)
    {
      delc=delx;
      c=c+delc;
      if(c>dely)
      {
        c=c-dely;
        return (x+sign);
      }  
      else
      return x;      
    }
    else
    {
        delc=dely;
        while(c<delx)
        {
            c=c+delc;
            x=x+sign;
        }
        c=c-delx;
        return x;
    }
}

void updatexbynextedgepoint(et *Tup) 
{ 
    int i; 
    printf("\nentered\n");
    for (i=0; i<Tup->e; i++) 
    { 
        (Tup->b[i]).xofymin =findnextedgepoint((Tup->b[i]).xofymin,(Tup->b[i]).delx,
                               (Tup->b[i]).dely,(Tup->b[i]).sign); 
        
    } 
} 

void ScanlineFill() 
{ 
/*	1. Horizontal edges: Do not include in edge table 
	2. Horizontal edges: Drawn either on the bottom or on the top. 
	3. Vertices: If local max or min, then count twice, else count once. 
	4. Either vertices at local minima or at local maxima are drawn.*/
	int i, j, x1, ymax1, x2, ymax2, FillFlag = 0, coordCount; 
	// we will start from scanline 0;  Repeat until last scanline: 
	for (i=0; i<maxHt; i++)//4. Increment y by 1 (next scan line) 
	{ 
		
		// 1. Move from ET bucket y to the AET those edges whose ymin = y (entering edges) 
		for (j=0; j<EdgeTable[i].e; j++) 
		{ 
			storeInTuple(&aet,EdgeTable[i].b[j]. 
					ymax,EdgeTable[i].b[j].xofymin, 
					EdgeTable[i].b[j].delx,EdgeTable[i].b[j].dely,EdgeTable[i].b[j].sign); 
		} 

		// 2. Remove from AET those edges for which y=ymax (not involved in next scan line) 
		removeEdgeByYmax(&aet, i); 
		//sort AET (remember: ET is presorted) 
		sort(&aet);		
		//3. Fill lines on scan line y by using pairs of x-coords from AET 
		j = 0; 
		FillFlag = 0; 
		coordCount = 0; 
		x1 = 0; 
		x2 = 0; 
		ymax1 = 0; 
		ymax2 = 0; 
		while (j<aet.e) 
		{ 
			if (coordCount%2==0) 
			{ 
				x1 = (int)(aet.b[j].xofymin); 
				ymax1 = aet.b[j].ymax; 
				if (x1==x2) 
				{ 
//three cases can arrive- 1. lines are towards top of the intersection 2. lines are towards bottom 3. one line is towards top and other is towards bottom 

					if (((x1==ymax1)&&(x2!=ymax2))||((x1!=ymax1)&&(x2==ymax2))) 
					{ 
						x2 = x1; 
						ymax2 = ymax1; 
					} 
					else
						coordCount++; 
				} 
				else
					coordCount++; 
			} 
			else
			{ 
				x2 = (int)aet.b[j].xofymin; 
				ymax2 = aet.b[j].ymax; 
				FillFlag = 0; 
				// checking for intersection... 
				if (x1==x2) 
				{ 
				/*three cases can arive- 
					1. lines are towards top of the intersection 
					2. lines are towards bottom 
					3. one line is towards top and other is towards bottom 
				*/
					if (((x1==ymax1)&&(x2!=ymax2))||((x1!=ymax1)&&(x2==ymax2))) 
					{ 
						x1 = x2; 
						ymax1 = ymax2; 
					} 
					else
					{ 
						coordCount++; 
						FillFlag = 1; 
					} 
				} 
				else
				{ 
						coordCount++; 
						FillFlag = 1; 
				} 
			if(FillFlag) 
			{ 
				//drawing actual lines... 
				glColor3f(0.0f,0.7f,0.0f); 
				glBegin(GL_LINES); 
				glVertex2i(x1,i); 
				glVertex2i(x2,i); 
				glEnd(); 
				glFlush();		 
			} 		
		} 		
		j++; 
	} 	
	// 5. For each nonvertical edge remaining in AET, update x for new y 
	updatexbynextedgepoint(&aet); 
} 
} 

void drawPolygon() 
{ 
	glColor3f(1.0f,0.0f,0.0f); 
	int count = 0,x1,y1,x2,y2; 
	rewind(fp); 
	while(!feof(fp) ) 
	{ 
		count++; 
		if (count>2) 
		{ 
			x1 = x2; 
			y1 = y2; 
			count=2; 
		} 
		if (count==1) 
		{ 
			fscanf(fp, "%d,%d", &x1, &y1); 
		} 
		else
		{ 
			fscanf(fp, "%d,%d", &x2, &y2); 
			printf("\n%d,%d", x2, y2); 
			glBegin(GL_LINES); 
				glVertex2i( x1, y1); 
				glVertex2i( x2, y2); 
			glEnd(); 
			storeEdge(x1, y1, x2, y2);//storage of edges in edge table. 		
			glFlush(); 
		} 
	} 	
} 

void display(void) 
{ 
	//Initialize edge table
	int i; 
	for (i=0; i<maxHt; i++) 
	{ 
		EdgeTable[i].e = 0; 
	} 
	aet.e = 0; 
	drawPolygon(); 	
	ScanlineFill();//actual calling of scanline filling.. 
} 

void myInit(void) 
{ 
	glClearColor(1.0,1.0,1.0,0.0); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluOrtho2D(0,maxHt,0,maxWd); 
	glClear(GL_COLOR_BUFFER_BIT); 
} 

void main(int argc, char** argv) 
{ 
	fp=fopen ("input.txt","r"); 
	if ( fp == NULL ) 
	{ 
		printf( "Could not open file" ) ; 
		return; 
	} 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(maxHt,maxWd); 
	glutInitWindowPosition(100, 150); 
	glutCreateWindow("Scanline filled dinosaur"); 
	myInit(); 
	glutDisplayFunc(display); 
	glutMainLoop(); 
	fclose(fp); 
} 
