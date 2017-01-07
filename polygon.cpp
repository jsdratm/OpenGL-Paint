#include "polygon.h"

polygon::polygon()
{
}

polygon::polygon(std::vector<point> points, GLdouble red, GLdouble green, GLdouble blue)
    : points(points)
    , red(red)
    , green(green)
    , blue(blue)
{
}

polygon::~polygon()
{
}

std::vector<point> polygon::getPoints()
{
    return points;
}

void polygon::setPoints(std::vector<point> input)
{
    points = input;
}

GLdouble polygon::getRed()
{
    return red;
}

GLdouble polygon::getGreen()
{
    return green;
}

GLdouble polygon::getBlue()
{
    return blue;
}

void polygon::setRed(GLdouble input)
{
    red = input;
}

void polygon::setGreen(GLdouble input)
{
    green = input;
}

void polygon::setBlue(GLdouble input)
{
    blue = input;
}

void polygon::Draw()
{
    glBegin(GL_POLYGON);
    glColor3f(red, green, blue);
    for (unsigned int i = 0; i < points.size(); i++) {
        glVertex3f(points[i].getX(), points[i].getY(), points[i].getZ());
    }
    glEnd();
}
