#include<iostream>
#include<GL/glut.h>
using namespace std;

int xc, yc, r;
int select;
void brescircle()
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

void MidPointCircle()
{  
  int x = 0;
  int y = r;
  int d = 5/4 - r;
  
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
      d=d+2*x+3;
    }
    else
    {
      x=x+1;
      y=y-1;
      d=d+2*x-2*y+5;
    }
  }
  while(x<=y);
}

void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);

  if (select==1)
  {
    brescircle();
  }
  else
  {
    MidPointCircle();
  }
  

  glEnd();
  glFlush();  
}
int main(int argc, char **argv)
{
  int option;
  cout<<"----Enter cordiantes of center ---- \n";
  cout<<"Enter xC : ";
  cin>>xc;
  cout<<"Enter yC : ";
  cin>>yc;
  cout<<"Enter Radius : ";
  cin>>r;
  
  cout<<"\n----Select the algorithm to draw circle----\n";
  cout<<"1. Bresenham's Circle Algorithm\n";
  cout<<"2. Midpoint Circle Algorithm\n";
  cout<<"-> ";
  cin>>option;

  switch (option)
  {
    case 1: select = 1;
    break;

    case 2: select = 2;
    break;
  }
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("Circle");
  
  glClearColor(0,0,0,1);
  glColor3f(1,1,1);
  
  gluOrtho2D(0,640,0,480);
  glutDisplayFunc(draw);
  glutMainLoop();
  return 0;
}
