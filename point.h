#ifndef POINT_H
#define POINT_H

#include <GL/glut.h>
#include <stdlib.h>
#include <vector>

class point {
public:
    point();
    point(GLdouble x, GLdouble y, GLdouble z, GLdouble red, GLdouble green, GLdouble blue);
    ~point();
    GLdouble getX();
    GLdouble getY();
    GLdouble getZ();
    GLdouble getRed();
    GLdouble getGreen();
    GLdouble getBlue();
    void setX(GLdouble input);
    void setY(GLdouble input);
    void setZ(GLdouble input);
    void setRed(GLdouble input);
    void setGreen(GLdouble input);
    void setBlue(GLdouble input);
    void Draw();

private:
    GLdouble x;
    GLdouble y;
    GLdouble z;
    GLdouble red;
    GLdouble green;
    GLdouble blue;
};

#endif
