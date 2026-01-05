#include<iostream>
using namespace std;
int Round(float a)
{
    return (int) (a+0.5);
}

void DDAline(int xa,int ya,int xb,int yb)
{
    int dx=xb-xa;
    int dy=yb-ya;
    int steps;

    if (abs(dx) > abs(dy))
    {
        steps=abs(dx);
    }
    else
    {
        steps=abs(dy);
    }

    float xinc= dx/(float)steps;
    float yinc=dy/(float)steps;

    float x=xa;
    float y=ya;

    cout<<"X\tY\txplot\typlot\n";
    cout<<x<<"\t"<<y<<"\t"<<Round(x)<<"\t"<<Round(y)<<endl;

    for (int i=0; i<steps; i++)
    {
        x = x+xinc;
        y = y+yinc;
        cout<<x<<"\t"<<y<<"\t"<<Round(x)<<"\t"<<Round(y)<<endl;
    }
    
}
    
int main()
{
    int xa,ya,xb,yb;
    cout<<"enter Xa : ";
    cin>>xa;
    cout<<"enter Ya : ";
    cin>>ya;

    cout<<"enter Xb : ";
    cin>>xb;
    cout<<"enter Yb : ";
    cin>>yb;

    DDAline(xa,ya,xb,yb);
    return 0;
}