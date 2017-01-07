#include "point.h"

point::point()
{
}

point::point(GLdouble x, GLdouble y, GLdouble z, GLdouble red, GLdouble green, GLdouble blue)
    : x(x)
    , y(y)
    , z(z)
    , red(red)
    , green(green)
    , blue(blue)
{
}

point::~point()
{
}

GLdouble point::getX()
{
    return x;
}

GLdouble point::getY()
{
    return y;
}

GLdouble point::getZ()
{
    return z;
}

GLdouble point::getRed()
{
    return red;
}

GLdouble point::getGreen()
{
    return green;
}

GLdouble point::getBlue()
{
    return blue;
}

void point::setX(GLdouble input)
{
    x = input;
}

void point::setY(GLdouble input)
{
    y = input;
}

void point::setZ(GLdouble input)
{
    z = input;
}

void point::setRed(GLdouble input)
{
    red = input;
}

void point::setGreen(GLdouble input)
{
    green = input;
}

void point::setBlue(GLdouble input)
{
    blue = input;
}

void point::Draw()
{
    glBegin(GL_POINTS);
    glColor3f(red, green, blue);
    glVertex3f(x, y, z);
    glEnd();
}
