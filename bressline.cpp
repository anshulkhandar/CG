#include<iostream>
#include<GL/glut.h>
using namespace std;

int xa,ya,xb,yb,flag=0;


void Bresline(int xa, int ya, int xb, int yb)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    
    int c,r,f;
    int dx = xb-xa;
    int dy = yb-ya;
    int d = 2*abs(dy) - abs(dx);
    
    if(abs(dx)>abs(dy))
    {
    	if(dx>0)
    	{
    		c=xa;
    		r=ya;
    		f=xb;
    	}
    	else
    	{
    		c=xb;
    		r=yb;
    		f=xa;
    	}
		if (flag == 0)
		{
			glVertex2d(c,r);
		}
		else
		{
			glVertex2d(r,c);
		}
    	while(c<=f)
    	{
    		if(d<0)
    		{
    			c=c+1;
    			d=d+ 2*abs(dy);
    		}
    		else
    		{
    			c=c+1;
    			if((dy*dx)>0)//(dx>0 && dy>0) || (dx<0 && dy<0))
    			{
    				r=r+1;
    			}
    			else
    			{
    				r=r-1;
    			}
    			d=d+2*abs(dy)-2*abs(dx);
    		}
    		if (flag == 0)
			{
				glVertex2d(c,r);
			}
			else
			{
				glVertex2d(r,c);
			}
    	}
    }
         
    glEnd();
    glFlush();
}

void draw
{
	int dx = xb - xa;
	int dy = yb - ya;
	if(abs(dx)>abs(dy))
	{
		flag=0;
		Bresline(xa,ya,xb,yb);
	}
	else
	{	
		flag=1;
		Bresline(ya,xa,yb,xb);
	}
}



int main(int argc ,char** argv)
{
	cout<<"enter xa : ";
    cin>>xa;
    cout<<"enter ya : ";
    cin>>ya;
    
    cout<<"enter xb : ";
    cin>>xb;
    cout<<"enter yb : ";
    cin>>yb;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("bresLine");

    glClearColor(0,0,0,0);
    glColor3f(1,1,1);

    gluOrtho2D(0,640,0,480);
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
