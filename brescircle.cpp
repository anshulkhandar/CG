#include<iostream>
#include<GL/glut.h>
using namespace std;

int xc, yc, r;
void brescircle()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);
  
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
  glEnd();
  glFlush();  
}
int main(int argc, char **argv)
{
  cout<<"----Enter cordiantes of center ----";
  cout<<"Enter XC : ";
  cin>>xc;
  cout<<"Enter XC : ";
  cin>>yc;
  cout<<"Enter Radius : ";
  cin>>r;
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("Circle");
  
  glClearColor(0,0,0,1);
  glColor3f(1,1,1);
  
  gluOrtho2D(0,640,0,480);
  glutDisplayFunc(brescircle);
  glutMainLoop();
  return 0;
}
