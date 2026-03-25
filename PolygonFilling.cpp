#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;

int v;
int vertex[2][10];

float bc[3] = {0.0, 0.0, 0.0};   // boundary color (black now for white bg)
float fc1[3];                    // boundary fill color
float fc2[3];                    // flood fill color
float bg[3] = {1.0, 1.0, 1.0};  // background color (white)

int x, y;
int choice;

// ---------------- Boundary Fill ----------------
void boundary_fill(int x, int y)
{
    float color[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);

    if((fc1[0] != color[0] || fc1[1] != color[1] || fc1[2] != color[2]) && (bc[0] != color[0] || bc[1] != color[1] || bc[2] != color[2]))
    {
        glColor3f(fc1[0], fc1[1], fc1[2]);

        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        boundary_fill(x + 1, y);
        boundary_fill(x - 1, y);
        boundary_fill(x, y + 1);
        boundary_fill(x, y - 1);
    }
}

// ---------------- Flood Fill ----------------
void flood_fill(int x, int y)
{
    float color[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);

    if((fc2[0] != color[0] || fc2[1] != color[1] || fc2[2] != color[2]) && (bg[0] == color[0] && bg[1] == color[1] && bg[2] == color[2]))
    {
        glColor3f(fc2[0], fc2[1], fc2[2]);

        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        flood_fill(x + 1, y);
        flood_fill(x - 1, y);
        flood_fill(x, y + 1);
        flood_fill(x, y - 1);
    }
}

// ---------------- DDA ----------------
int Round(float a) {
    return (int)(a + 0.5);
}

void DDA_draw(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = max(abs(dx), abs(dy));
    if (steps == 0) steps = 1;

    float xinc = (float)dx / steps;
    float yinc = (float)dy / steps;

    float x = x1, y = y1;

    glVertex2i(Round(x), Round(y));

    for (int i = 0; i < steps; i++)
    {
        x += xinc;
        y += yinc;
        glVertex2i(Round(x), Round(y));
    }
}

// ---------------- Draw ----------------
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw polygon
    glColor3f(bc[0], bc[1], bc[2]);

    glBegin(GL_POINTS);
    for (int i = 0; i < v; i++)
    {
        DDA_draw(vertex[0][i], vertex[1][i],
                 vertex[0][(i + 1) % v], vertex[1][(i + 1) % v]);
    }
    glEnd();

    glFlush();
    glFinish();

    // Switch Case
    switch (choice)
    {
        case 1:
            boundary_fill(x, y);
            break;

        case 2:
            flood_fill(x, y);
            break;

        default:
            cout << "Invalid choice!";
    }
}

// ---------------- Main ----------------
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
    cin >> x >> y;

    cout << "\nChoose Algorithm:\n";
    cout << "1. Boundary Fill\n";
    cout << "2. Flood Fill\n-> ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter Boundary Fill Color (R G B): ";
        cin >> fc1[0] >> fc1[1] >> fc1[2];
    }
    else if (choice == 2)
    {
        cout << "Enter Flood Fill Color (R G B): ";
        cin >> fc2[0] >> fc2[1] >> fc2[2];
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(640, 480);
    glutCreateWindow("Polygon Filling");

    // WHITE BACKGROUND
    glClearColor(1, 1, 1, 1);

    gluOrtho2D(0, 640, 0, 480);

    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}
