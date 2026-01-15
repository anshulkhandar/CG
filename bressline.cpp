#include<iostream>
#include<GL/glut.h>

using namespace std;

int xa,ya,xb,yb;

void bressline(int xa, int ya, int xb, int yb)
{
    int c,r,f;
    int dx = xb-xa;
    int dy = yb-ya;
    int d = 2*abs(dy)-abs(dx);


    //if (abs(dx)>abs(dy))
    //{
        if(dx>0)
        {
            c = xa;
            r = ya;
            f = xb;
        }
        else
        {
            c = xb;
            r = yb;
            f = xa;
        }
        while (c<=f)
        {
            if (d<0)
            {
                c = c+1;
                d = d+ 2*abs(dy);
                glVertex2d(c,r);
            }
            else
            {
                if ((dy/dx) > 0)
                {
                    c=c+1;
                    r = r+1;
                }
                else
                {
                    c=c+1;
                    r = r-1;
                }
                d = d + 2*abs(dy) - 2*abs(dx); 
                glVertex2d(c,r);  
            }
        }
    //}
}
void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    int dx = xb-xa;
    int dy = yb-ya;
    if(abs(dx)>abs(dy))
    {
        bressline(xa,ya,xb,yb);
    }
    else
    {
        bressline(ya,xa,yb,xb);
    }
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
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
  glutCreateWindow("Circle");
  
  glClearColor(0,0,0,1);
  glColor3f(1,1,1);
  
  gluOrtho2D(0,640,0,480);
  glutDisplayFunc(Draw);
  glutMainLoop();
  return 0;
}
