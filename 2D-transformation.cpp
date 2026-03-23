#include<iostream>
#include<math.h>
#include <cmath>
#include<GL/glut.h>
using namespace std;

int v; //no of vertices
int input[3][10]; // input vertex
float output[3][10]; // output matrix
float tx,ty; // translation factors
float sx,sy,xf,yf; // scalling factor and fixed point
float ang, xr, yr; // 

//DDA line 
int Round(float a)
{
  return (int) (a + 0.5);
}
void Ddaline(int xa, int ya, int xb, int yb)
{   
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
    glVertex2d(Round(x)+320,Round(y)+240);
    for (int i=0; i<steps; i++)
    {
        x = x+xinc;
        y = y+yinc;
        glVertex2d(Round(x)+320,Round(y)+240);
    }
    
}

//multiplication function
void multiplication(float output[3][10], float f[3][3], int input[3][10])
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<v; j++)
		{	
			output[i][j] = 0;
			for(int k=0; k<3; k++)
			{
				output[i][j] += f[i][k] * input[k][j];
			}
		}
	}
}

//translation
void translation()
{
	cout<<"----x Enter translation factor x----\n";
	cout<<"tx : ";
	cin>>tx; 
	cout<<"ty : ";
	cin>>ty;
	
	float t[3][3]= {{1,0,tx},
			 		{0,1,ty},
			 		{0,0,1}};
	
	
	multiplication(output,t,input);
	
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<v; j++)
		{
			cout<<output[i][j]<<"\t";
		}
		cout<<"\n";
	}
}

//reflection
void reflection()
{			
	float r[3][3]= {{1,0,0},
			{0,-1,0},
			{0,0,1}};
	
	multiplication(output,r,input);
	
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<v; j++)
		{
			cout<<output[i][j]<<"\t";
		}
		cout<<"\n";
	}
}

//scalling
void scaling()
{
	cout<<"----x Enter Scalling factor x----\n";
	cout<<"sx : ";
	cin>>sx; 
	cout<<"sy : ";
	cin>>sy;
	
	cout<<"----x Enter fixed points factor x----\n";
	cout<<"xf : ";
	cin>>xf; 
	cout<<"yf : ";
	cin>>yf;
	
	float s[3][3]= {{sx, 0, xf*(1-sx)},
			{0, sy, yf*(1-sy)},
			{0, 0, 1}};
			
	multiplication(output,s,input);
	
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<v; j++)
		{
			cout<<output[i][j]<<"\t";
		}
		cout<<"\n";
	}
	
}

//rotation 
void rotation()
{
	cout<<"----x Enter Degree of rotation (Anticlockwise +ve) x----\n";
	cout<<"ang : ";
	cin>>ang; 
	
	ang = ang * M_PI / 180;
	
	cout<<"----x Enter Arbitrary points factor x----\n";
	cout<<"xr : ";
	cin>>xr; 
	cout<<"yr : ";
	cin>>yr;
	
	float rt[3][3]={{cos(ang), -sin(ang), xr*(1-cos(ang)) - yr*sin(ang)},
					{sin(ang), cos(ang), yr*(1-cos(ang)) + xr*sin(ang)},
					{0, 0, 1}};
	
	multiplication(output,rt,input);
	
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<v; j++)
		{
			cout<<output[i][j]<<"\t";
		}
		cout<<"\n";
	}
}

//shear
void shear()
{
    int type;

    cout << "----x Select Shearing Type x----\n";
    cout << "1. X-Shear\n2. Y-Shear\n-> ";
    cin >> type;

    float shx = 0, shy = 0;

    if (type == 1)
    {
        cout << "Enter shx: ";
        cin >> shx;

        float sh[3][3] = {
            {1, shx, 0},
            {0, 1,   0},
            {0, 0,   1}
        };

        multiplication(output, sh, input);
    }
    else if (type == 2)
    {
        cout << "Enter shy: ";
        cin >> shy;

        float sh[3][3] = {
            {1,   0, 0},
            {shy, 1, 0},
            {0,   0, 1}
        };

        multiplication(output, sh, input);
    }

    // print output (same as your style)
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < v; j++)
        {
            cout << output[i][j] << "\t";
        }
        cout << "\n";
    }
}

//draw function
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
  	glBegin(GL_POINTS);
  	
  	//the co-odrinate axis
  	glColor3f(1,1,1);
  	Ddaline(-320,0,320,0);//(-320,0,320,0)
  	glColor3f(1,1,1);
  	Ddaline(0,-240,0,240);//(0,-240,0,240)
  	
  	//---------------------
  	
  	glColor3f(1,0,0);
  	for(int i=0; i<v; i++)
  	{
  		Ddaline(input[0][i],input[1][i],input[0][(i+1)%v],input[1][(i+1)%v]);
  	}
  	
  	glColor3f(0,1,0);
  	for(int i=0; i<v; i++)
  	{
  		Ddaline(output[0][i],output[1][i],output[0][(i+1)%v],output[1][(i+1)%v]);
  	}
  	
  	
  	glEnd();
  	glFlush();
	
}

int main(int argc, char **argv)
{
	int option;
	cout<<"Enter no of vertices : ";
	cin>>v;
	
	cout<<"----x Enter all vertices x----\n";
	for(int i=0;i<v;i++)
	{
		cout<<"X"<<i+1<<" : ";
		cin>>input[0][i];
		cout<<"Y"<<i+1<<" : ";
		cin>>input[1][i];
		input[2][i]=1;
	}
	cout<<"\n";

	cout<<"----x select one option x----\n";
	cout<<"1.translation\n2.reflection\n3.scalling\n4.rotation\n5.shear\n-> ";
	cin>>option;
	
		switch(option)
		{
		case 1: translation();
		break;
		case 2: reflection();
		break;
		case 3: scaling();
		break; 
		case 4: rotation();
		break;
		case 5: shear();
		break;
		}
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0,0);
	glutCreateWindow("2d transformation");
	
	glClearColor(0,0,0,0);
	glColor3f(1,1,1);
	
	gluOrtho2D(0,640,0,480);
	glutDisplayFunc(draw);
	glutMainLoop();

	return 0;
}
