#include "rectangle.h"

rectangle::rectangle()
{
}

rectangle::rectangle(point startPoint, point endPoint, GLdouble red, GLdouble green, GLdouble blue)
    : startPoint(startPoint)
    , endPoint(endPoint)
    , red(red)
    , green(green)
    , blue(blue)
{
}

rectangle::~rectangle()
{
}

point rectangle::getStartPoint()
{
    return startPoint;
}

point rectangle::getEndPoint()
{
    return endPoint;
}

void rectangle::setStartPoint(point input)
{
    startPoint = input;
}

void rectangle::setEndPoint(point input)
{
    endPoint = input;
}

GLdouble rectangle::getRed()
{
    return red;
}

GLdouble rectangle::getGreen()
{
    return green;
}

GLdouble rectangle::getBlue()
{
    return blue;
}

void rectangle::setRed(GLdouble input)
{
    red = input;
}

void rectangle::setGreen(GLdouble input)
{
    green = input;
}

void rectangle::setBlue(GLdouble input)
{
    blue = input;
}

void rectangle::Draw()
{
    if ((startPoint.getX() < endPoint.getX() && startPoint.getY() > endPoint.getY()) || (startPoint.getX() > endPoint.getX() && startPoint.getY() < endPoint.getY())) {
        glBegin(GL_QUADS);
        glColor3f(red, green, blue);
        glVertex3f(endPoint.getX(), startPoint.getY(), startPoint.getZ());
        glVertex3f(startPoint.getX(), startPoint.getY(), startPoint.getZ());
        glVertex3f(startPoint.getX(), endPoint.getY(), endPoint.getZ());
        glVertex3f(endPoint.getX(), endPoint.getY(), endPoint.getZ());
        glEnd();
    }
    else {
        glBegin(GL_QUADS);
        glColor3f(red, green, blue);
        glVertex3f(startPoint.getX(), startPoint.getY(), startPoint.getZ());
        glVertex3f(endPoint.getX(), startPoint.getY(), startPoint.getZ());
        glVertex3f(endPoint.getX(), endPoint.getY(), endPoint.getZ());
        glVertex3f(startPoint.getX(), endPoint.getY(), endPoint.getZ());
        glEnd();
    }
}
