#include<iostream>
//#include<GL/glut.h>
using namespace std;

int xmin, ymin, xmax, ymax;
int k=0;
float output[2][10];

void left_clip(int xa, int ya, int xb, int yb)
{
	float m = (float)(yb-ya)/(xb-xa);
	
	if(xa>xmin && xb>xmin)
	{
		output[0][k] = xb;
		output[1][k] = yb;
		k++;
	}
	
	if(xa>xmin && xb<xmin)
	{
		output[0][k] = xmin;
		output[1][k] = yb+m*(xmin-xb);
		k++;
	}
	
	if(xa<xmin && xb>xmin)
	{
		output[0][k] = xmin;
		output[1][k] = ya+m*(xmin-xa);
		k++;
		output[0][k] = xb;
		output[1][k] =yb;
		k++;
	}
}

int main()
{
	cout<<"Enter xmin: ";
	cin>>xmin;
	cout<<"Enter ymin: ";
	cin>>ymin;
	cout<<"Enter xmax: ";
	cin>>xmax;
	cout<<"Enter ymax: ";
	cin>>ymax;
	cout<<"\n";	
	
	int v;
	cout<<"Enter no of vertices : ";
	cin>>v;
	
	int input[2][10];
	
	cout<<"----Enter the co-ordiantes of the points----\n";
	for(int i=0;i<v;i++)
	{
		cout<<i+1<<":\n";
		cout<<"x : ";
		cin>>input[0][i];
		cout<<"y : ";
		cin>>input[1][i];
	}
	
	cout<<"\n\t X\ty\n";
	for(int i=0;i<v;i++)
	{
		cout<<i+1<<"\t"<<input[0][i]<<"\t"<<input[1][i]<<"\n";
	}
	
	
	//left clip
	for(int i=0; i<v; i++)
	{
		left_clip(input[0][i],input[1][i],input[0][(i+1)%v],input[1][(i+1)%v]);
	}
	cout<<"\n\t X\ty\n";
	for(int i=0;i<v;i++)
	{
		cout<<i+1<<"\t"<<output[0][i]<<"\t"<<input[1][i]<<"\n";
	}
}
