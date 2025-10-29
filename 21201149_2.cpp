#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
    glPointSize(1.5);
}

void draw_pixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void plot8(int xc, int yc, int x, int y)
{
    draw_pixel(xc + x, yc + y);
    draw_pixel(xc - x, yc + y);
    draw_pixel(xc + x, yc - y);
    draw_pixel(xc - x, yc - y);
    draw_pixel(xc + y, yc + x);
    draw_pixel(xc - y, yc + x);
    draw_pixel(xc + y, yc - x);
    draw_pixel(xc - y, yc - x);
}

void draw_circle_radius(int xc, int yc, int r)
{
    if (r < 0)
        return;
    int x = 0;
    int y = r;
    int d = 1 - r;

    plot8(xc, yc, x, y);
    while (x < y)
    {
        if (d < 0)
        {
            d += 2 * x + 3;
            x++;
        }
        else
        {
            d += 2 * (x - y) + 5;
            x++;
            y--;
        }
        plot8(xc, yc, x, y);
    }
}

float lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

void draw_concentric(int xc, int yc, int n, int baseR, int stepR, int baseThick, int thickStep,
                     float r0, float g0, float b0, float r1, float g1, float b1)
{
    if (n <= 0)
        return;

    int max_outer_radius = baseR + (n - 1) * stepR + (baseThick + (n - 1) * thickStep);

    for (int i = 0; i < n; ++i)
    {
        int radius = baseR + i * stepR;
        int thickness = baseThick + i * thickStep;
        if (thickness < 1)
            thickness = 1;

        int outer_r = radius + thickness - 1;
        float t = 0.0f;
        if (max_outer_radius > 0)
            t = (float)outer_r / (float)max_outer_radius;
        if (t < 0.0f)
            t = 0.0f;
        if (t > 1.0f)
            t = 1.0f;

        float rr = lerp(r0, r1, t);
        float gg = lerp(g0, g1, t);
        float bb = lerp(b0, b1, t);

        glColor3f(rr, gg, bb);

        for (int r = radius; r <= radius + thickness - 1; ++r)
        {
            draw_circle_radius(xc, yc, r);
        }
    }
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);

    extern int centerX, centerY, numCircles, baseRadius, radiusStep, baseThickness, thicknessStep;
    extern float colR0, colG0, colB0, colR1, colG1, colB1;

    draw_concentric(centerX, centerY, numCircles, baseRadius, radiusStep,
                    baseThickness, thicknessStep,
                    colR0, colG0, colB0, colR1, colG1, colB1);

    glFlush();
}

int centerX = 250, centerY = 250;
int numCircles = 8;
int baseRadius = 20;
int radiusStep = 12;
int baseThickness = 2;
int thicknessStep = 1;
float colR0 = 1.0f, colG0 = 0.2f, colB0 = 0.2f;
float colR1 = 0.1f, colG1 = 0.2f, colB1 = 1.0f;

int main(int argc, char **argv)
{

    printf("Concentric circles with gradient\n");
    printf("Enter centerX centerY  (e.g. 250 250):\n");
    if (scanf("%d %d", &centerX, &centerY) != 2)
    {
        printf("Using default center (250,250)\n");
        centerX = 250;
        centerY = 250;
    }

    printf("Enter number_of_circles baseRadius radiusStep  (e.g. 8 20 12):\n");
    if (scanf("%d %d %d", &numCircles, &baseRadius, &radiusStep) != 3)
    {
        printf("Using defaults: 8 20 12\n");
        numCircles = 8;
        baseRadius = 20;
        radiusStep = 12;
    }

    printf("Enter baseThickness thicknessStep  (e.g. 2 1):\n");
    if (scanf("%d %d", &baseThickness, &thicknessStep) != 2)
    {
        printf("Using defaults: 2 1\n");
        baseThickness = 2;
        thicknessStep = 1;
    }

    printf("Enter inner color R G B (0..1) and outer color R G B (0..1)\n");
    printf("Example (red->blue): 1 0.2 0.2  0.1 0.2 1\n");
    if (scanf("%f %f %f %f %f %f", &colR0, &colG0, &colB0, &colR1, &colG1, &colB1) != 6)
    {
        printf("Using default colors inner(1,0.2,0.2) outer(0.1,0.2,1)\n");
        colR0 = 1.0f;
        colG0 = 0.2f;
        colB0 = 0.2f;
        colR1 = 0.1f;
        colG1 = 0.2f;
        colB1 = 1.0f;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Concentric Circles with Gradient");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}