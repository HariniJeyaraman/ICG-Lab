#include<GL/glut.h>
#include<cstdlib>
#include<iostream>
using namespace std;
#define WINDOW_HEIGHT 800 
#define maxWd 600 
//The edge data structure
typedef struct Edge{
int  yUpper;
float xIntersect, dxPerScan;
struct tEdge * next;
}gEdge;

typedef struct tdcPt{
int x;
int y;
}dcPt;

void scanFill (int cnt, dcPt * pts){
    Edge * edges[WINDOW_HEIGHT], * active;int i, scan;
    for (i=0; i<WINDOW_HEIGHT; i++){
        edges[i] = (Edge *) malloc (sizeof (Edge));
        edges[i]->next = NULL;
    }
    buildEdgeList (cnt, pts, edges);
    active = (Edge *) malloc (sizeof (Edge));
    active->next = NULL;
    for (scan=0; scan<WINDOW_HEIGHT; scan++){
        buildActiveList (scan, active, edges);
        if (active->next){
            fillScan (scan, active);
            updateActiveList(scan, active);
            resortActiveList (active);
        }
    }

}

void buildEdgeList (int cnt, dcPt * pts, Edge * edges[]){
    Edge * edge;
    dcPt v1, v2;
    int i, yPrev = pts[cnt - 2].y;
    v1.x = pts[cnt-1].x; v1.y = pts[cnt-1].y;
    for (i=0; i<cnt; i++){
        v2 = pts[i];
        if (v1.y != v2.y){
            edge = (Edge *) malloc (sizeof (Edge));
            if (v1.y < v2.y)                 /* up-going edge      */
            makeEdgeRec (v1, v2, yNext (i, cnt, pts), edge, edges);
            else                             /* down-going edge    */
            makeEdgeRec (v2, v1, yPrev, edge, edges);
        }
        yPrev = v1.y;
        v1 = v2;
    }
}

/* For an index, return y-coordinate of next nonhorizontal line */
int yNext (int k, int cnt, dcPt * pts){
    int j;
    if ((k+1) > (cnt-1))
        j=0;
    else
        j=k+1;
    while (pts[k].y == pts[j].y)
        if ((j+1) > (cnt-1))
            j=0;
        else
            j++;
    return (pts[j].y);
}

void buildEdgeList (int cnt, dcPt * pts, Edge * edges[]){
    Edge * edge;
    dcPt v1, v2;
    int i, yPrev = pts[cnt - 2].y;
    v1.x = pts[cnt-1].x; 
    v1.y = pts[cnt-1].y;
    for (i=0; i<cnt; i++){
        v2 = pts[i];
        if (v1.y != v2.y){
            edge = (Edge *) malloc (sizeof (Edge));
            if (v1.y < v2.y)                 /* up-going edge      */
            makeEdgeRec (v1, v2, yNext (i, cnt, pts), edge, edges);
            else                             /* down-going edge    */
            makeEdgeRec (v2, v1, yPrev, edge, edges);
        }
    }
}

/* Store lower-y coordinate and inverse slope for each edge.  
Adjustand store upper-y coordinate for edges that are the lower memberof a monotically increasing or decreasing pair of edges */
void makeEdgeRec(dcPt lower, dcPt upper, int yComp, Edge * edge, Edge * edges[]){
    edge->dxPerScan =(float) (upper.x - lower.x) / (upper.y - lower.y);
    edge->xIntersect = lower.x;
    if (upper.y < yComp)
        edge->yUpper = upper.y - 1;
    else
        edge->yUpper = upper.y;
    insertEdge (edges[lower.y], edge);
}   

/* Inserts edge into list in order of increasing xIntersect field. */
void insertEdge (Edge * list, Edge * edge){
    Edge *p,*q=list;
    p = q->next;
    while (p != NULL){
        if (edge->xIntersect < p->xIntersect)
            p = NULL;
        else{
            q=p;
            p = p->next;
        }
    }
    edge->next = q->next;
    q->next = edge;
}

void buildActiveList (int scan, Edge * active, Edge * edges[]){
    Edge *p,*q;
    p = edges[scan]->next;
    while (p){
        q = p->next;
        insertEdge (active, p);
        p=q;
    }
}

