#include <iostream>
#include <cmath>   // for abs
#include <GL/glut.h>
using namespace std;

int outa[4]={0,0,0,0};
int outb[4]={0,0,0,0};

// clipping window
int xa,ya,xb,yb,xmin,ymin,xmax,ymax;

// result of clipping
int clipStatus = -1; // 0 = accepted, 1 = rejected, 2 = partial
int newXa, newYa, newXb, newYb;

void outcode(int x, int y, int out[])
{
	if(x<xmin)
	{
		out[3]=1;
	}
	if(x>xmax)
	{
		out[2]=1;
	}
	if(y<ymin)
	{
		out[1]=1;
	}
	if(y>ymax)
	{
		out[0]=1;
	}
	
}

// compute clipped intersection point and return via reference
void newpointfind(int x1, int y1, int out[], float m, int &nx, int &ny)
{
    int x = x1;
    int y = y1;
    
    // Clip against vertical boundaries (LEFT/RIGHT)
    if(out[3]==1)  // LEFT
    {
        x = xmin;
        y = y1 + m * (xmin - x1);
    }
    else if(out[2]==1)  // RIGHT
    {
        x = xmax;
        y = y1 + m * (xmax - x1);
    }
    
    // Clip against horizontal boundaries (BOTTOM/TOP)
    if(out[1]==1)  // BOTTOM
    {
        y = ymin;
        x = x1 + (ymin - y1) / m;
    }
    else if(out[0]==1)  // TOP
    {
        y = ymax;
        x = x1 + (ymax - y1) / m;
    }

    nx = x;
    ny = y;
    cout<<"----point after cliping ----\n";
    cout<<"("<<x<<","<<y<<")\n";
}

// perform clipping calculation and set globals
void linecliping()
{
    int flag1 = 0; // =0 if fully inside
    int flag2 = 0; // =1 if trivially rejected

    // rectangle and line endpoints already read before calling this

    outcode(xa,ya,outa); // outcodes for A
    outcode(xb,yb,outb); // outcodes for B

    // print outcodes (optional, for console feedback)
    cout << "\n -------Outcodes------- \n";
    cout << "outcode a : ";
    for(int i=0; i<4; i++) cout<<outa[i];
    cout << "\n";
    cout << "outcode b : ";
    for(int i=0; i<4; i++) cout<<outb[i];
    cout << "\n\n";

    // check for fully inside
    for(int i=0; i<4; i++)
    {
        if(outa[i]==1 || outb[i]==1)
        {
            flag1 = 1; // either point outside
            break;
        }
    }

    if(flag1 == 0)
    {
        cout << "the line is accepted \n";
        clipStatus = 0;
        newXa = xa; newYa = ya;
        newXb = xb; newYb = yb;
    }
    else
    {
        int outpnr[4] = {0,0,0,0};
        for(int i = 0; i<4; i++)
        {
            outpnr[i] = outa[i] && outb[i];
            if(outpnr[i] == 1)
            {
                flag2 = 1; // trivially rejected
                break;
            }
        }
        if(flag2 == 0)
        {
            cout << "the line is partially accepted \n";
            clipStatus = 2;
            float m = (float)(yb - ya) / (xb - xa);
            newpointfind(xa, ya, outa, m, newXa, newYa);
            newpointfind(xb, yb, outb, m, newXb, newYb);
        }
        else
        {
            cout << "the line is rejected \n";
            clipStatus = 1;
        }
    }
}

int Round(float a)
{
    return (int)(a + 0.5);
}

// draw a line using DDA between arbitrary points; color should be set by caller
void DdaLineGeneric(int x1, int y1, int x2, int y2)
{
    glPointSize(2.0f);
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    if (steps == 0) {
        // single point
        glBegin(GL_POINTS);
        glVertex2i(x1, y1);
        glEnd();
        return;
    }
    float xinc = (float)dx / steps;
    float yinc = (float)dy / steps;

    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for(int i = 0; i <= steps; i++)
    {
        glVertex2i(Round(x), Round(y));
        x += xinc;
        y += yinc;
    }
    glEnd();
}

// draw the clipping window rectangle
void drawRectangle()
{
    // four edges
    DdaLineGeneric(xmin, ymin, xmax, ymin);
    DdaLineGeneric(xmax, ymin, xmax, ymax);
    DdaLineGeneric(xmax, ymax, xmin, ymax);
    DdaLineGeneric(xmin, ymax, xmin, ymin);
}

// draw callback invoked by GLUT
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // draw clipping rectangle in white
    glColor3f(1,1,1);
    drawRectangle();

    // draw lines according to clipping status
    if(clipStatus == 0)
    {
        // completely accepted
        glColor3f(0,1,0);
        DdaLineGeneric(xa, ya, xb, yb);
    }
    else if(clipStatus == 1)
    {
        // rejected
        glColor3f(1,0,0);
        DdaLineGeneric(xa, ya, xb, yb);
    }
    else if(clipStatus == 2)
    {
        // partial: original red, clipped green
        glColor3f(1,0,0);
        DdaLineGeneric(xa, ya, xb, yb);
        glColor3f(0,1,0);
        DdaLineGeneric(newXa, newYa, newXb, newYb);
    }

    glFlush();
}


int main()
{
    // collect clipping window and a single line from console before opening window
    cout << "enter xmin : ";
    cin >> xmin;
    cout << "enter ymin : ";
    cin >> ymin;
    cout << "enter xmax : ";
    cin >> xmax;
    cout << "enter ymax : ";
    cin >> ymax;

    cout << "enter xa : ";
    cin >> xa;
    cout << "enter ya : ";
    cin >> ya;
    cout << "enter xb : ";
    cin >> xb;
    cout << "enter yb : ";
    cin >> yb;

    // compute clipping status using original logic
    linecliping();

    // set up OpenGL window
    glutInit();
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Line Clipping Demo");

    glClearColor(0,0,0,0);
    glColor3f(1,1,1);
    gluOrtho2D(0,640,0,480);

    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}
