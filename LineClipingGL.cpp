#include <iostream>
#include <cmath>
#include <GL/glut.h>
using namespace std;

int outa[4]={0,0,0,0};
int outb[4]={0,0,0,0};
int xa,ya,xb,yb,xmin,ymin,xmax,ymax;

// drawing / clipping results
int clipStatus = -1; // 0 accepted, 1 rejected, 2 partial
int clip_xa, clip_ya, clip_xb, clip_yb;

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

void newpointfind(int x1, int y1, int out[], float m)
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

    cout<<"----point after cliping ----\n";
    cout<<"("<<x<<","<<y<<")\n";
}

// compute intersection point like newpointfind but return coords
void computeIntersection(int x1, int y1, int out[], float m, int &nx, int &ny)
{
	int x = x1;
	int y = y1;
	if(out[3]==1) { x = xmin; y = y1 + m * (xmin - x1); }
	else if(out[2]==1) { x = xmax; y = y1 + m * (xmax - x1); }
	if(out[1]==1) { y = ymin; if(m!=0) x = x1 + (ymin - y1) / m; }
	else if(out[0]==1) { y = ymax; if(m!=0) x = x1 + (ymax - y1) / m; }
	nx = x; ny = y;
}

void linecliping()
{
	int flag1 = 0; //  =0 if accepted =1 if rejucted or partially accepted
	int flag2 = 0; // =0 if partially accepted =1 if rejected
	
	cout<<"enter xmin : ";
	cin>>xmin;
	cout<<"enter ymin : ";
	cin>>ymin;
	cout<<"enter xmax : ";
	cin>>xmax;
	cout<<"enter ymax : ";
	cin>>ymax;
	
	
	cout<<"enter xa : ";
	cin>>xa;
	cout<<"enter ya : ";
	cin>>ya;
	cout<<"enter xb : ";
	cin>>xb;
	cout<<"enter yb : ";
	cin>>yb;
	
	outcode(xa,ya,outa);//outcode caluculation for a
	outcode(xb,yb,outb);//outcode caluculation for b

	//<------------------->
	
	cout<<"\n -------Outcodes------- \n";
	cout<<"outcode a : ";
	for(int i=0; i<4; i++)
	{
		cout<<outa[i];
	}
	cout<<"\n";
	cout<<"outcode b : ";
	for(int i=0; i<4; i++)
	{
		cout<<outb[i];
	}
	cout<<"\n\n";
	
	//<------------------->
	
	for(int i=0; i<4; i++)
	{
		if(outa[i]==1 || outb[i]==1)
		{
			flag1=1; //rejected or partially accepted
			break;
		}
	}
	
	if(flag1==0)
	{
		cout<<"the line is accepted \n";
	}
	else
	{
		int outpnr[4] ={0,0,0,0};
		for(int i =0; i<4; i++)
		{
			outpnr[i] = outa[i] && outb[i];
			
			if(outpnr[i]==1)
			{
				flag2=1; //rejected
				break;
			}
		}
		if(flag2==0)
		{
			cout<<"the line is partially accepted \n";	
			float m = (float) (yb-ya)/(xb-xa);
			newpointfind(xa,ya,outa,m);
			newpointfind(xb,yb,outb,m);
		}
		else
		{
			cout<<"the line is rejected \n";
		}
	}
}

// round helper
int Round(float a){ return (int)(a+0.5); }

void DDA_draw(int x1,int y1,int x2,int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
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

	float xinc = (float)(dx) / steps;
	float yinc = (float)(dy) / steps;

	float x = x1;
	float y = y1;
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

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3.0f);

	glBegin(GL_POINTS);

	// draw clipping rectangle (white)
	glColor3f(1,1,1);
	DDA_draw(xmin,ymin,xmax,ymin);
	DDA_draw(xmax,ymin,xmax,ymax);
	DDA_draw(xmax,ymax,xmin,ymax);
	DDA_draw(xmin,ymax,xmin,ymin);

	// draw original line in red
	glColor3f(1,0,0);
	DDA_draw(xa,ya,xb,yb);

	// overlay clipped segments in green when appropriate
	glColor3f(0,1,0);
	if(clipStatus==0){
		// accepted — draw green full line over red
		DDA_draw(xa,ya,xb,yb);
	} else if(clipStatus==2){
		// partial — draw clipped segment in green
		DDA_draw(clip_xa,clip_ya,clip_xb,clip_yb);
	}

	glEnd();
	glFlush();
}



int main()
{
	// call your existing console clipping routine to collect inputs and outcodes
	linecliping();

	// decide clip status based on outcodes
	int flag1 = 0; // any outside
	for(int i=0;i<4;i++) if(outa[i]==1 || outb[i]==1) { flag1=1; break; }
	if(flag1==0){
		clipStatus = 0; // accepted
	} else {
		int outpnr[4]={0,0,0,0};
		int flag2=0;
		for(int i=0;i<4;i++){
			outpnr[i] = outa[i] && outb[i];
			if(outpnr[i]==1){ flag2=1; break; }
		}
		if(flag2==1){ clipStatus = 1; }
		else {
			clipStatus = 2;
			float m = (float)(yb - ya) / (xb - xa);
			computeIntersection(xa, ya, outa, m, clip_xa, clip_ya);
			computeIntersection(xb, yb, outb, m, clip_xb, clip_yb);
		}
	}

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
