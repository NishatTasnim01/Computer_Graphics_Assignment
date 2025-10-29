#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SEGMENTS 500
int seg_x1[MAX_SEGMENTS], seg_y1[MAX_SEGMENTS], seg_x2[MAX_SEGMENTS], seg_y2[MAX_SEGMENTS];
int num_segments = 0;
int clip_xmin = 100, clip_ymin = 100, clip_xmax = 400, clip_ymax = 350;

void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
    glPointSize(1.0);
}

void draw_pixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void draw_raw_line_int(int X1, int Y1, int X2, int Y2)
{
    int dx = X2 - X1;
    int dy = Y2 - Y1;
    int abs_dx = dx < 0 ? -dx : dx;
    int abs_dy = dy < 0 ? -dy : dy;
    int incx = (X2 >= X1) ? 1 : -1;
    int incy = (Y2 >= Y1) ? 1 : -1;
    int x = X1;
    int y = Y1;
    int i, e, inc1, inc2;

    if (abs_dx > abs_dy)
    {
        draw_pixel(x, y);
        e = 2 * abs_dy - abs_dx;
        inc1 = 2 * (abs_dy - abs_dx);
        inc2 = 2 * abs_dy;
        for (i = 0; i < abs_dx; ++i)
        {
            if (e >= 0)
            {
                y += incy;
                e += inc1;
            }
            else
            {
                e += inc2;
            }
            x += incx;
            draw_pixel(x, y);
        }
    }
    else
    {
        draw_pixel(x, y);
        e = 2 * abs_dx - abs_dy;
        inc1 = 2 * (abs_dx - abs_dy);
        inc2 = 2 * abs_dx;
        for (i = 0; i < abs_dy; ++i)
        {
            if (e >= 0)
            {
                x += incx;
                e += inc1;
            }
            else
            {
                e += inc2;
            }
            y += incy;
            draw_pixel(x, y);
        }
    }
}

void draw_line(int a_x1, int a_x2, int a_y1, int a_y2)
{
    int X1 = a_x1;
    int X2 = a_x2;
    int Y1 = a_y1;
    int Y2 = a_y2;
    draw_raw_line_int(X1, Y1, X2, Y2);
}

int liang_barsky_clip(double x0, double y0, double x1d, double y1d,
                      double xmin, double ymin, double xmax, double ymax,
                      int *cx0, int *cy0, int *cx1, int *cy1)
{
    double p[4], q[4];
    double u1 = 0.0, u2 = 1.0;
    double dx = x1d - x0;
    double dy = y1d - y0;

    p[0] = -dx;
    q[0] = x0 - xmin; 
    p[1] = dx;
    q[1] = xmax - x0; 
    p[2] = -dy;
    q[2] = y0 - ymin; 
    p[3] = dy;
    q[3] = ymax - y0; 

    for (int i = 0; i < 4; ++i)
    {
        if (fabs(p[i]) < 1e-9)
        {
            if (q[i] < 0.0)
            {
                return 0;
            }
            else
            {
                continue;
            }
        }
        double t = q[i] / p[i];
        if (p[i] < 0)
        {
            if (t > u2)
                return 0;
            if (t > u1)
                u1 = t;
        }
        else
        {
            if (t < u1)
                return 0;
            if (t < u2)
                u2 = t;
        }
    }

    if (u1 > u2)
        return 0;

    double cx0d = x0 + u1 * dx;
    double cy0d = y0 + u1 * dy;
    double cx1d = x0 + u2 * dx;
    double cy1d = y0 + u2 * dy;

    *cx0 = (int)round(cx0d);
    *cy0 = (int)round(cy0d);
    *cx1 = (int)round(cx1d);
    *cy1 = (int)round(cy1d);

    return 1;
}

void draw_clip_window(int xmin, int ymin, int xmax, int ymax)
{
    glColor3f(0.0f, 1.0f, 0.0f); 
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmin, ymax);
    glVertex2i(xmax, ymax);
    glVertex2i(xmax, ymin);
    glEnd();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);

    draw_clip_window(clip_xmin, clip_ymin, clip_xmax, clip_ymax);

    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < num_segments; ++i)
    {
        draw_line(seg_x1[i], seg_x2[i], seg_y1[i], seg_y2[i]);
    }

    glColor3f(1.0f, 0.0f, 0.0f);
    for (int i = 0; i < num_segments; ++i)
    {
        int cx0, cy0, cx1, cy1;
        int visible = liang_barsky_clip(
            (double)seg_x1[i], (double)seg_y1[i],
            (double)seg_x2[i], (double)seg_y2[i],
            (double)clip_xmin, (double)clip_ymin,
            (double)clip_xmax, (double)clip_ymax,
            &cx0, &cy0, &cx1, &cy1);
        if (visible)
        {
            draw_raw_line_int(cx0, cy0, cx1, cy1);
        }
    }

    glFlush();
}

int read_int_or_default(int *out, int def)
{
    if (scanf("%d", out) == 1)
        return 1;
    *out = def;
    return 0;
}

int main(int argc, char **argv)
{

    printf("Liang-Barsky Line Clipping Demo\n");
    printf("Enter number of line segments (max %d):\n", MAX_SEGMENTS);
    if (scanf("%d", &num_segments) != 1 || num_segments <= 0)
    {
        printf("Invalid number. Exiting.\n");
        return 1;
    }
    if (num_segments > MAX_SEGMENTS)
        num_segments = MAX_SEGMENTS;

    printf("Enter %d line(s) as: x1 y1 x2 y2  (one per line)\n", num_segments);
    for (int i = 0; i < num_segments; ++i)
    {
        if (scanf("%d %d %d %d", &seg_x1[i], &seg_y1[i], &seg_x2[i], &seg_y2[i]) != 4)
        {
            printf("Invalid input for segment %d. Exiting.\n", i + 1);
            return 1;
        }
    }

    printf("Enter clipping window xmin ymin xmax ymax: (eg. 100 100 400 350)\n");
    if (scanf("%d %d %d %d", &clip_xmin, &clip_ymin, &clip_xmax, &clip_ymax) != 4)
    {
        printf("Invalid clipping window. Using defaults: 100 100 400 350\n");
        clip_xmin = 100;
        clip_ymin = 100;
        clip_xmax = 400;
        clip_ymax = 350;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Liang-Barsky Line Clipping");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}