#include<iostream>
#include<GL/glut.h>
using namespace std;
int xa,ya,xb,yb;
int Round(float a)
{
	return (int)(a+0.5);
}

void DDA(int xa, int ya, int xb, int yb)
{
 	
	int dx= xb-xa;
 	int dy= yb-ya;
 	int steps;
 	
 	if(abs(dx)>abs(dy))
 	{
 		steps = abs(dx);
 	}
 	else
 	{
 		steps = abs(dy); 
 	}
 	
 	float xinc = (float)(dx)/steps;
 	float yinc = (float)(dy)/steps;
 	
 	float x = xa;
 	float y = ya;
 	glVertex2d(xa,ya);
 	
 	for(int i=0; i<steps; i++)
 	{
 		x+=xinc;
 		y+=yinc;
 		glVertex2d(x,y);
 	}
 	
}
 
void shape()
{
 	glClear(GL_COLOR_BUFFER_BIT);
 	glBegin(GL_POINTS);
 	
 	glColor3f(0,0,0);
 	DDA(xa,ya,xa,yb);
 	DDA(xa,yb,xb,yb);
 	DDA(xb,yb,xb,ya);
 	DDA(xb,ya,xa,ya);
 	
 	
 	glColor3f(1,0,0);
 	DDA(xa,(ya+yb)/2,(xa+xb)/2,yb);
 	DDA((xa+xb)/2,yb,xb,(ya+yb)/2);
 	DDA(xb,(ya+yb)/2,(xa+xb)/2,ya);
 	DDA((xa+xb)/2,ya,xa,(ya+yb)/2);
 	
 	float x1 = xa;
 	float y1 = (ya+yb)/2;
 	
 	float x2 = (xa+xb)/2;
 	float y2 = yb;
 	
 	float x3 =xb;
 	float y3 =(ya+yb)/2;
 	
 	float x4 =(xa+xb)/2;
 	float y4 =ya;
 	
 	glColor3f(0,0,1);
 	DDA((x1+x2)/2, (y1+y2)/2, (x2+x3)/2, (y2+y3)/2);
 	DDA((x2+x3)/2, (y2+y3)/2, (x3+x4)/2, (y3+y4)/2);
 	DDA((x3+x4)/2, (y3+y4)/2, (x4+x1)/2, (y4+y1)/2);
 	DDA((x4+x1)/2, (y4+y1)/2, (x1+x2)/2, (y1+y2)/2);
 	
 	glEnd();
 	glFlush();
 
}


int main(int argc , char **argv)
{
	
	cout<<"enter Xa : ";
    cin>>xa;
    cout<<"enter Ya : ";
    cin>>ya;

    cout<<"enter Xb : ";
    cin>>xb;
    cout<<"enter Yb : ";
    cin>>yb;
    
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	glutCreateWindow("DDA");
	
	glClearColor(1,1,1,0);
	
	gluOrtho2D(0,640,0,480);
	glutDisplayFunc(shape);
	glutMainLoop();
	
}
