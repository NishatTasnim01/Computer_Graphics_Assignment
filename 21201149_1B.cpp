#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int x1_global, y1_global, x2_global, y2_global;
int line_width_global = 5;

void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void draw_thick_pixel(int x, int y)
{
    int R = line_width_global / 2;

    glBegin(GL_POINTS);
    for (int i = x - R; i <= x + R; i++)
    {
        for (int j = y - R; j <= y + R; j++)
        {
            glVertex2i(i, j);
        }
    }
    glEnd();
}

void draw_thick_line(int x1, int x2, int y1, int y2, int W)
{
    int dx, dy, i, e;
    int incx, incy, inc1, inc2;
    int x, y;

    line_width_global = W;

    dx = x2 - x1;
    dy = y2 - y1;

    int abs_dx = (dx < 0) ? -dx : dx;
    int abs_dy = (dy < 0) ? -dy : dy;
    incx = (x2 < x1) ? -1 : 1;
    incy = (y2 < y1) ? -1 : 1;

    x = x1;
    y = y1;

    if (abs_dx > abs_dy)
    {
        draw_thick_pixel(x, y);
        e = 2 * abs_dy - abs_dx;
        inc1 = 2 * (abs_dy - abs_dx);
        inc2 = 2 * abs_dy;

        for (i = 0; i < abs_dx; i++)
        {
            if (e >= 0)
            {
                y += incy;
                e += inc1;
            }
            else
                e += inc2;
            x += incx;
            draw_thick_pixel(x, y);
        }
    }
    else
    {
        draw_thick_pixel(x, y);
        e = 2 * abs_dx - abs_dy;
        inc1 = 2 * (abs_dx - abs_dy);
        inc2 = 2 * abs_dx;

        for (i = 0; i < abs_dy; i++)
        {
            if (e >= 0)
            {
                x += incx;
                e += inc1;
            }
            else
                e += inc2;
            y += incy;
            draw_thick_pixel(x, y);
        }
    }
}

void myDisplay()
{
    draw_thick_line(x1_global, x2_global, y1_global, y2_global, line_width_global);
    glFlush();
}

int main(int argc, char **argv)
{
    int thickness;

    printf("Enter (x1, y1, x2, y2)\n");
    if (scanf("%d %d %d %d", &x1_global, &y1_global, &x2_global, &y2_global) != 4)
    {
        printf("Invalid input for coordinates.\n");
        return 1;
    }

    printf("Enter line thickness W (e.g., 5 for a W=5 line)\n");
    if (scanf("%d", &thickness) != 1 || thickness < 1)
    {
        printf("Invalid input for thickness. Using default W=5.\n");
        thickness = 5;
    }
    line_width_global = thickness;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham's Thick Line Drawing");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}