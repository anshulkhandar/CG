#include<iostream>
//#include<GL/glut.h>
using namespace std;

int outa[4]={0,0,0,0};
int outb[4]={0,0,0,0};	
int xa,ya,xb,yb,xmin,ymin,xmax,ymax;

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



int main()
{
	linecliping();
}
