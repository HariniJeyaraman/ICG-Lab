#include<bits/stdc++.h>
using namespace std;
#include <GL/glut.h>

int num_of_points;

struct edge {
	int Y_max;
	int X_min;
	int Y_min;
	int X_min_ori;
	int del_x;
	int del_y;
	int sign;
};

struct vertices
{
	int x;
	int y;
}points[100];

vector<edge> scanline[645];
int global_y_min = INT_MAX;
int global_y_max = -INT_MAX;

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}

edge create_edge(struct vertices v1, struct vertices v2) {
	int x1 = v1.x;
	int y1 = v1.y;
	int x2 = v2.x;
	int y2 = v2.y;

	edge node;

	if(y1>y2)
	{
		node.Y_max = y1;
		node.X_min = x2;
		node.Y_min=y2;
	}
	else
	{
		node.Y_max = y2;
		node.X_min = x1;
		node.Y_min = y1;
	}
	int sign = 1;
	node.X_min_ori = node.X_min;
	
	if (x1 == x2) {
		;
	}
	else {
		if ((float(y2 - y1) / float(x2 - x1)) < 0) {
			node.sign = -1;
		}
		else
			node.sign = 1;
	}
	node.del_x = abs(x2 - x1);
	node.del_y = abs(y2 - y1);

	return node;
}

void nsort(vector<edge> &aet) {
	int n = aet.size();
	edge temp;
	if (n == 0) 
		return;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (aet[j].X_min > aet[j+1].X_min) {
				temp = aet[j];
				aet[j] = aet[j+1];
				aet[j+1] = temp;
			}
		}
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	cout << "\nMain algorithm starts here \n";
	vector<edge> aet;
	
	for (int i = 0; i < 640; i++) {
		
		nsort(scanline[i]);
	}
	
	for (int i = global_y_min; i <= global_y_max; i++) {
		for (int j = 0; j < aet.size(); j++) {
			if (aet[j].Y_max <= i) {
				//Erasing from aet
				vector<edge> temp;
				int n = aet.size();
				for (int k = 0; k < n; k++) 
				{
					if (k != j)
					{
						temp.push_back(aet[k]);
					}
				} 
				aet = temp;
				j--;

			}
			if (aet[j].del_x == 0) {
				;
			}
			else {
				
				aet[j].X_min  = aet[j].X_min_ori + aet[j].sign*(i - aet[j].Y_min) / (float(aet[j].del_y)/float(aet[j].del_x));
			}
		}
			
		//Appending to aet

		int sizeofaet = aet.size();
		int newsize = scanline[i].size();
		for (int k = 0; k < newsize; k++) {
			aet.push_back(scanline[i][k]);
		}

		nsort(aet);
		if (aet.size() >=2) {
			for (int l = 0; l < aet.size() - 1; l+=2) {
				int ptx1, pty1, ptx2, pty2;
				//pairing the points
				ptx1 = aet[l].X_min;
				ptx2 = aet[l+1].X_min;
				pty1 = i;
				pty2 = i;				
				glBegin(GL_LINES);
    			glVertex2f(ptx1,pty1);
    			glVertex2f(ptx2,pty2);
				glEnd();

			}
		}

	}
	cout << "\n Ends here\n";
	glEnd();
	glFlush();
}

int main(int argc, char** argv){
	freopen("input.txt", "r", stdin);
	int temp1, temp2, tempymin;
	edge temp;
	cin >> num_of_points;
	for (int i = 0; i < num_of_points; i++) {
		cin >> temp1;
		cin >> temp2;
		// push the current point to the vector/array of points
		points[i].x=temp1;
		points[i].y=temp2;
		cout<<"\nCoordinates of vertex "<<i<<" are ("<<temp1<<","<<temp2<<")";
		global_y_min = min(temp2, global_y_min);
		global_y_max = max(temp2, global_y_max);
	}
	
	for (int i = 1; i < num_of_points; i++) {
		if ((points[i].y - points[i-1].y)) {
			temp = create_edge(points[i], points[i-1]);
			if(points[i].y<points[i-1].y)
				tempymin=points[i].y;
			else
				tempymin=points[i-1].y;
			scanline[tempymin].push_back(temp);
		}
	}
	if ((points[0].y - points[num_of_points - 1].y)) {
		temp = create_edge(points[0], points[num_of_points - 1]);
		if(points[0].y<points[num_of_points-1].y)
				tempymin=points[0].y;
			else
				tempymin=points[num_of_points-1].y;
		scanline[tempymin].push_back(temp);
	}

	
	cout << "\nGlobal max of y coordinate " <<  global_y_max << "\n";
	cout << "\nGlobal min of y coordinate" << global_y_min << "\n";
	
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Polygon");
	init();
	glutDisplayFunc(display);
	
	glutMainLoop();
	return 0;
}

//x1=250.0;y1=200.0;x2=150.0;y2=300.0;x3=250.0;
// y3=400.0;x4=350.0;y4=300.0;