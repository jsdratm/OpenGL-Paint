#include "line.h"

line::line()
{
}

line::line(point startPoint, point endPoint, GLdouble red, GLdouble green, GLdouble blue)
    : startPoint(startPoint)
    , endPoint(endPoint)
    , red(red)
    , green(green)
    , blue(blue)
{
}

line::~line()
{
}

point line::getStartPoint()
{
    return startPoint;
}

point line::getEndPoint()
{
    return endPoint;
}

void line::setStartPoint(point input)
{
    startPoint = input;
}

void line::setEndPoint(point input)
{
    endPoint = input;
}

GLdouble line::getRed()
{
    return red;
}

GLdouble line::getGreen()
{
    return green;
}

GLdouble line::getBlue()
{
    return blue;
}

void line::setRed(GLdouble input)
{
    red = input;
}

void line::setGreen(GLdouble input)
{
    green = input;
}

void line::setBlue(GLdouble input)
{
    blue = input;
}

void line::Draw()
{
    glBegin(GL_LINES);
    glColor3f(red, green, blue);
    glVertex3f(startPoint.getX(), startPoint.getY(), startPoint.getZ());
    glVertex3f(endPoint.getX(), endPoint.getY(), endPoint.getZ());
    glEnd();
}
