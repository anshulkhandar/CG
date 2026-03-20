#include <iostream>
#include <GL/glut.h>

using namespace std;

int v;
int vertex[2][10];

float bc[3] = {1.0, 1.0, 1.0};   // boundary color (white)
float fc1[3];                    // boundary fill color
float fc2[3];                    // flood fill color
float bg[3];                     // background for flood fill

int x, y;                        // inside pixel
int choice;                      // user choice


void boundry_fill(float bc[3], float fc1[3], int x, int y)
{
    float color[3];

    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);

    if ((fc1[0] != color[0] || fc1[1] != color[1] || fc1[2] != color[2]) &&
        (bc[0] != color[0] || bc[1] != color[1] || bc[2] != color[2]))
    {
        glColor3f(fc1[0], fc1[1], fc1[2]);
        glVertex2d(x, y);

        boundry_fill(bc, fc1, x + 1, y);
        boundry_fill(bc, fc1, x - 1, y);
        boundry_fill(bc, fc1, x, y + 1);
        boundry_fill(bc, fc1, x, y - 1);
    }
}


void flood_fill(float bg[3], float fc2[3], int x, int y)
{
    float color[3];

    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);

    if ((fc2[0] != color[0] || fc2[1] != color[1] || fc2[2] != color[2]) &&
        (bg[0] == color[0] && bg[1] == color[1] && bg[2] == color[2]))
    {
        glColor3f(fc2[0], fc2[1], fc2[2]);
        glVertex2d(x, y);

        flood_fill(bg, fc2, x + 1, y);
        flood_fill(bg, fc2, x - 1, y);
        flood_fill(bg, fc2, x, y + 1);
        flood_fill(bg, fc2, x, y - 1);
    }
}


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

    if (steps == 0)
    {
        steps = 1;
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

    // Draw polygon boundary
    glColor3f(bc[0], bc[1], bc[2]);

    glBegin(GL_POINTS);
    for (int i = 0; i < v; i++)
    {
        DDA_draw(vertex[0][i], vertex[1][i],
                 vertex[0][(i + 1) % v], vertex[1][(i + 1) % v]);
    }
    glEnd();

    // Ensure drawing is complete before reading pixels
    glFinish();

    // Boundary Fill
    glColor3f(fc1[0], fc1[1], fc1[2]);

    glBegin(GL_POINTS);
    boundry_fill(bc, fc1, x, y);
    glEnd();

    glFlush();

    // Optional Flood Fill
    if (choice == 1)
    {
        glFinish();

        glColor3f(fc2[0], fc2[1], fc2[2]);

        glBegin(GL_POINTS);
        flood_fill(bg, fc2, x, y);
        glEnd();

        glFlush();
    }
}


int main(int argc, char **argv)
{
    cout << "Enter number of vertices: ";
    cin >> v;

    cout << "---- Enter the Vertices ----\n";
    for (int i = 0; i < v; i++)
    {
        cout << "X" << i + 1 << ": ";
        cin >> vertex[0][i];

        cout << "Y" << i + 1 << ": ";
        cin >> vertex[1][i];
    }

    cout << "\nEnter an inside pixel:\n";
    cout << "X: ";
    cin >> x;

    cout << "Y: ";
    cin >> y;

    // Boundary fill color input
    cout << "\nEnter Boundary Fill Color (R G B):\n";

    cout << "R: ";
    cin >> fc1[0];

    cout << "G: ";
    cin >> fc1[1];

    cout << "B: ";
    cin >> fc1[2];

    // Ask for flood fill
    cout << "\nDo you want to execute Flood Fill?\n";
    cout << "1. Yes\n2. No\n-> ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "\nEnter Flood Fill Color (R G B):\n";

        cout << "R: ";
        cin >> fc2[0];

        cout << "G: ";
        cin >> fc2[1];

        cout << "B: ";
        cin >> fc2[2];

        // Set background as boundary filled region
        bg[0] = fc1[0];
        bg[1] = fc1[1];
        bg[2] = fc1[2];
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Polygon Filling");

    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);

    gluOrtho2D(0, 640, 0, 480);

    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}
