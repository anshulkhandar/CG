#include <iostream>
#include <cmath>
#include <GL/glut.h>
using namespace std;

int xmin, ymin, xmax, ymax;
int k = 0;
float output[2][10];

// store original polygon for drawing
int origCount = 0;
float orig[2][10];

// will hold the clipped vertices after all edges
int finalCount = 0;

// helper to round float to int
int Round(float a)
{
    return (int)(a + 0.5);
}

void ddaline(float xa, float ya, float xb, float yb)
{
    int dx = (int)(xb - xa);
    int dy = (int)(yb - ya);
    int steps;
    if (abs(dx) > abs(dy))
    {
        // gentle slope
        steps = abs(dx);
    }
    else
    {
        // sharp slope
        steps = abs(dy);
    }
    if (steps == 0) steps = 1;

    float xinc = (float)(dx) / (float)steps;
    float yinc = (float)(dy) / (float)steps;

    float x = xa;
    float y = ya;
    // debug output (keeps user's original prints)
    cout << "X\tY\txplot\typlot\n";
    cout << x << "\t" << y << "\t" << Round(x) << "\t" << Round(y) << endl;
    glVertex2d(Round(x), Round(y));
    for (int i = 0; i < steps; i++)
    {
        x = x + xinc;
        y = y + yinc;
        cout << x << "\t" << y << "\t" << Round(x) << "\t" << Round(y) << endl;
        glVertex2d(Round(x), Round(y));
    }
}

void left_clip(float xa, float ya, float xb, float yb)
{
    float m = (yb - ya) / (xb - xa);
	
	if(xa>xmin && xb>xmin)
	{
		output[0][k] = xb;
		output[1][k] = yb;
		k++;
	}
	
	if(xa>xmin && xb<xmin)
	{
		output[0][k] = xmin;
		output[1][k] = yb+m*(xmin-xb);
		k++;
	}
	
	if(xa<xmin && xb>xmin)
	{
		output[0][k] = xmin;
		output[1][k] = ya+m*(xmin-xa);
		k++;
		output[0][k] = xb;
		output[1][k] =yb;
		k++;
	}
}

void right_clip(float xa, float ya, float xb, float yb)
{
    float m = (yb - ya) / (xb - xa);
	
	if(xa<xmax && xb<xmax)
	{
		output[0][k] = xb;
		output[1][k] = yb;
		k++;
	}
	
	if(xa<xmax && xb>xmax)
	{
		output[0][k] = xmax;
		output[1][k] = yb+m*(xmax-xb);
		k++;
	}
	
	if(xa>xmax && xb<xmax)
	{
		output[0][k] = xmax;
		output[1][k] = ya+m*(xmax-xa);
		k++;
		output[0][k] = xb;
		output[1][k] =yb;
		k++;
	}
}

void bottom_clip(float xa, float ya, float xb, float yb)
{
    float m = (yb - ya) / (xb - xa);
	
	if(ya>ymin && yb>ymin)
	{
		output[0][k] = xb;
		output[1][k] = yb;
		k++;
	}
	
	if(ya>ymin && yb<ymin)
	{
		output[0][k] = xb+m*(ymin-yb);
		output[1][k] = ymin;
		k++;
	}
	if(ya<ymin && yb>ymin)
	{
		output[0][k] = xa+m*(ymin-ya);
		output[1][k] = ymin;
		k++;
		output[0][k] = xb;
		output[1][k] =yb;
		k++;
	}
}

void top_clip(float xa, float ya, float xb, float yb)
{
    float m = (yb - ya) / (xb - xa);
	
	if(ya<ymax && yb<ymax)
	{
		output[0][k] = xb;
		output[1][k] = yb;
		k++;
	}
	
	if(ya<ymax && yb>ymax)
	{
		output[0][k] = xb+m*(ymax-yb);
		output[1][k] = ymax;
		k++;
	}
	if(ya>ymax && yb<ymax)
	{
		output[0][k] = xa+m*(ymax-ya);
		output[1][k] = ymax;
		k++;
		output[0][k] = xb;
		output[1][k] =yb;
		k++;
	}
}

// draw function performing DDA inside — now uses ddaline helper with a single glBegin/glEnd
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3.0f);

    glBegin(GL_POINTS);

    // draw clipping rectangle in white
    glColor3f(1,1,1);
    ddaline((float)xmin, (float)ymin, (float)xmax, (float)ymin);
    ddaline((float)xmax, (float)ymin, (float)xmax, (float)ymax);
    ddaline((float)xmax, (float)ymax, (float)xmin, (float)ymax);
    ddaline((float)xmin, (float)ymax, (float)xmin, (float)ymin);

    // draw original polygon in red
    glColor3f(1,0,0);
    for(int j=0;j<origCount;j++){
        int ni=(j+1)%origCount;
        ddaline(orig[0][j], orig[1][j], orig[0][ni], orig[1][ni]);
    }

    // draw clipped polygon in green (if any)
    if(finalCount>0){
        glColor3f(0,1,0);
        for(int j=0;j<finalCount;j++){
            int ni=(j+1)%finalCount;
            ddaline(output[0][j], output[1][j], output[0][ni], output[1][ni]);
        }
    }

    glEnd();
    glFlush();
}

int main()
{
    cout<<"Enter xmin: ";
    cin>>xmin;
    cout<<"Enter ymin: ";
    cin>>ymin;
    cout<<"Enter xmax: ";
    cin>>xmax;
    cout<<"Enter ymax: ";
    cin>>ymax;
    cout<<"\n";

    int v;
    cout<<"Enter no of vertices : ";
    cin>>v;

    int input[2][10];
    
    cout<<"----Enter the co-ordiantes of the points----\n";
    for(int i=0;i<v;i++)
    {
        cout<<i+1<<":\n";
        cout<<"x : ";
        cin>>input[0][i];
        cout<<"y : ";
        cin>>input[1][i];
    }

    // copy to global orig for drawing later
    origCount = v;
    for(int i=0;i<v;i++){
        orig[0][i] = input[0][i];
        orig[1][i] = input[1][i];
    }

    cout<<"\n\t X\ty\n";
    for(int i=0;i<v;i++)
    {
        cout<<i+1<<"\t"<<input[0][i]<<"\t"<<input[1][i]<<"\n";
    }

    // successive clipping, each stage uses previous output as input
    float curr[2][10];
    int currCount = v;
    for(int i=0;i<v;i++){
        curr[0][i] = input[0][i];
        curr[1][i] = input[1][i];
    }

    // left edge — call using original input order (1-2,2-3,...)
    k = 0;
    for(int i=0;i<v;i++){
        left_clip(input[0][i], input[1][i], input[0][(i+1)%v], input[1][(i+1)%v]);
    }
    currCount = k;
    for(int i=0;i<currCount;i++){
        curr[0][i] = output[0][i];
        curr[1][i] = output[1][i];
    }

    // right edge (preserve original input ordering accuracy)
    k = 0;
    for(int i=0;i<currCount;i++){
        int ni = (i+1)%currCount;
        right_clip(curr[0][i], curr[1][i], curr[0][ni], curr[1][ni]);
    }
    currCount = k;
    for(int i=0;i<currCount;i++){
        curr[0][i] = output[0][i];
        curr[1][i] = output[1][i];
    }

    // bottom edge
    k = 0;
    for(int i=0;i<currCount;i++){
        int ni = (i+1)%currCount;
        bottom_clip(curr[0][i], curr[1][i], curr[0][ni], curr[1][ni]);
    }
    currCount = k;
    for(int i=0;i<currCount;i++){
        curr[0][i] = output[0][i];
        curr[1][i] = output[1][i];
    }

    // top edge
    k = 0;
    for(int i=0;i<currCount;i++){
        int ni = (i+1)%currCount;
        top_clip(curr[0][i], curr[1][i], curr[0][ni], curr[1][ni]);
    }
    finalCount = k;

    // set up OpenGL window
    glutInit();
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Polygon Clip");
    glClearColor(0,0,0,0);
    gluOrtho2D(0,640,0,480);
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
