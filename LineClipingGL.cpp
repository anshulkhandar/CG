#include <iostream>
#include <cmath>
#include <GL/glut.h>

using namespace std;

int outa[4] = {0, 0, 0, 0};
int outb[4] = {0, 0, 0, 0};

int xa, ya, xb, yb;
int xmin, ymin, xmax, ymax;

// clipping results
int clipStatus = -1; // 0 accepted, 1 rejected, 2 partial
int clip_xa, clip_ya, clip_xb, clip_yb;


void outcode(int x, int y, int out[])
{
    if (x < xmin)
    {
        out[3] = 1;
    }

    if (x > xmax)
    {
        out[2] = 1;
    }

    if (y < ymin)
    {
        out[1] = 1;
    }

    if (y > ymax)
    {
        out[0] = 1;
    }
}


// compute intersection point
void computeIntersection(int x1, int y1, int out[], float m, int &nx, int &ny)
{
    int x = x1;
    int y = y1;

    // LEFT
    if (out[3] == 1)
    {
        x = xmin;
        y = y1 + m * (xmin - x1);
    }
    // RIGHT
    else if (out[2] == 1)
    {
        x = xmax;
        y = y1 + m * (xmax - x1);
    }

    // BOTTOM
    if (out[1] == 1)
    {
        y = ymin;

        if (m != 0)
        {
            x = x1 + (ymin - y1) / m;
        }
    }
    // TOP
    else if (out[0] == 1)
    {
        y = ymax;

        if (m != 0)
        {
            x = x1 + (ymax - y1) / m;
        }
    }

    nx = x;
    ny = y;
}


void linecliping()
{
    int flag1 = 0;
    int flag2 = 0;

    cout << "enter xmin : ";
    cin >> xmin;

    cout << "enter ymin : ";
    cin >> ymin;

    cout << "enter xmax : ";
    cin >> xmax;

    cout << "enter ymax : ";
    cin >> ymax;

    cout << "enter xa : ";
    cin >> xa;

    cout << "enter ya : ";
    cin >> ya;

    cout << "enter xb : ";
    cin >> xb;

    cout << "enter yb : ";
    cin >> yb;

    outcode(xa, ya, outa);
    outcode(xb, yb, outb);

    cout << "\n -------Outcodes------- \n";

    cout << "outcode a : ";
    for (int i = 0; i < 4; i++)
    {
        cout << outa[i];
    }

    cout << "\noutcode b : ";
    for (int i = 0; i < 4; i++)
    {
        cout << outb[i];
    }

    cout << "\n\n";


    // check accepted
    for (int i = 0; i < 4; i++)
    {
        if (outa[i] == 1 || outb[i] == 1)
        {
            flag1 = 1;
            break;
        }
    }

    if (flag1 == 0)
    {
        cout << "the line is accepted \n";
        clipStatus = 0;
    }
    else
    {
        int outpnr[4] = {0, 0, 0, 0};

        for (int i = 0; i < 4; i++)
        {
            outpnr[i] = outa[i] && outb[i];

            if (outpnr[i] == 1)
            {
                flag2 = 1;
                break;
            }
        }

        if (flag2 == 0)
        {
            cout << "the line is partially accepted \n";

            float m;

            if (xb - xa != 0)
            {
                m = (float)(yb - ya) / (xb - xa);
            }
            else
            {
                m = 1e9; // vertical line safety
            }

            computeIntersection(xa, ya, outa, m, clip_xa, clip_ya);
            computeIntersection(xb, yb, outb, m, clip_xb, clip_yb);

            cout << "----points after clipping ----\n";
            cout << "(" << clip_xa << "," << clip_ya << ")\n";
            cout << "(" << clip_xb << "," << clip_yb << ")\n";

            clipStatus = 2;
        }
        else
        {
            cout << "the line is rejected \n";
            clipStatus = 1;
        }
    }
}


// round helper
int Round(float a)
{
    return (int)(a + 0.5);
}


void DDA_draw(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps;

    if (abs(dx) > abs(dy))
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }

    float xinc = (float)dx / steps;
    float yinc = (float)dy / steps;

    float x = x1;
    float y = y1;

    glVertex2d(Round(x), Round(y));

    for (int i = 0; i < steps; i++)
    {
        x = x + xinc;
        y = y + yinc;

        glVertex2d(Round(x), Round(y));
    }
}


void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3.0f);

    glBegin(GL_POINTS);

    // rectangle
    glColor3f(1, 1, 1);
    DDA_draw(xmin, ymin, xmax, ymin);
    DDA_draw(xmax, ymin, xmax, ymax);
    DDA_draw(xmax, ymax, xmin, ymax);
    DDA_draw(xmin, ymax, xmin, ymin);

    // original line
    glColor3f(1, 0, 0);
    DDA_draw(xa, ya, xb, yb);

    // clipped result
    glColor3f(0, 1, 0);

    if (clipStatus == 0)
    {
        DDA_draw(xa, ya, xb, yb);
    }
    else if (clipStatus == 2)
    {
        DDA_draw(clip_xa, clip_ya, clip_xb, clip_yb);
    }

    glEnd();
    glFlush();
}


int main()
{
    linecliping();

    glutInit();
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Line Clipping Demo");

    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);

    gluOrtho2D(0, 640, 0, 480);

    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}
