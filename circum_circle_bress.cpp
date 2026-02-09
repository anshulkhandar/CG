#include<iostream>
#include<GL/glut.h>
using namespace std;

void Bresline(int xa, int ya, int xb, int yb, int flag)
{
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
}

void linecall(int xa,int ya, int xb, int yb)
{
        int flag=0;
        int dx = xb - xa;
	int dy = yb - ya;
	if(abs(dx)>abs(dy))
	{
		flag=0;
		Bresline(xa,ya,xb,yb,flag);
	}
	else
	{	
		flag=1;
		Bresline(ya,xa,yb,xb,flag);
	}
}


void brescircle(int xc, int yc, int r)
{
  int x = 0;
  int y = r;
  int d = 3-2*r;
  
  do
  {
    glVertex2d(xc + x, yc + y);
    glVertex2d(xc - x, yc + y);
    glVertex2d(xc + x, yc - y);
    glVertex2d(xc - x, yc - y);
    glVertex2d(xc + y, yc + x);
    glVertex2d(xc - y, yc + x);
    glVertex2d(xc + y, yc - x);
    glVertex2d(xc - y, yc - x);
    if(d<0)
    {
      x=x+1;
      d=d+4*x+6;
    }
    else
    {
      x=x+1;
      y=y-1;
      d=d+4*x-4*y+10;
    }
  }
  while(x<=y);  
}

void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);
  
  linecall(60,100,360,100);
  linecall(60,100,210,360);
  linecall(210,360,360,100);
  
  brescircle(210,187,173);
  
  glEnd();
  glFlush();
}

int main(int argc, char **argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("Shape 1");
  
  glClearColor(0,0,0,0);
  glColor3f(1,1,1);
  
  gluOrtho2D(0,640,0,480);
  glutDisplayFunc(draw);
  glutMainLoop();
}
