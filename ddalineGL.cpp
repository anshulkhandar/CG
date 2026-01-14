#include<iostream>
#include<GL/glut.h>
using namespace std;
int xa,ya,xb,yb;
int Round(float a)
{
  return (int) (a + 0.5);
}
void Ddaline()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    
    int dx,dy,steps;
    dx = xb-xa;
    dy = yb-ya;
    if (abs(dx) > abs(dy))
    {
        //gental slope
        steps = abs(dx);
    }
    else
    {
        //sharp slope
        steps = abs(dy);
    }
    float xinc = (float)(dx)/steps;
    float yinc = (float)(dy)/steps;

    float x = xa;
    float y = ya;
    cout<<"X\tY\txplot\typlot\n";
    cout<<x<<"\t"<<y<<"\t"<<Round(x)<<"\t"<<Round(y)<<endl;
    glVertex2d(Round(x),Round(y));
    for (int i=0; i<steps; i++)
    {
        x = x+xinc;
        y = y+yinc;
        cout<<x<<"\t"<<y<<"\t"<<Round(x)<<"\t"<<Round(y)<<endl;
        glVertex2d(Round(x),Round(y));
    }
    
    glEnd();
    glFlush();
}
int main(int argc, char **argv)
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

    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("DDALINE");

    glClearColor(0,0,0,0);
    glColor3f(1,1,1);

    gluOrtho2D(0,640,0,480);
    glutDisplayFunc(Ddaline);
    glutMainLoop();
    return 0;
}
