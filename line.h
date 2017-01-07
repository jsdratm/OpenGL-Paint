#ifndef LINE_H
#define LINE_H

#include <GL/glut.h>
#include <stdlib.h>
#include <vector>
#include "point.h"

class line{
public:
	line();
	line(point startPoint, point endPoint, GLdouble red, GLdouble green, GLdouble blue);
	~line();
    point getStartPoint();
    point getEndPoint();
    GLdouble getRed();
    GLdouble getGreen();
    GLdouble getBlue();
    void setStartPoint(point input);
    void setEndPoint(point input);
    void setRed(GLdouble input);
    void setGreen(GLdouble input);
    void setBlue(GLdouble input);
    void Draw();
    
private:
	point startPoint;
	point endPoint;
	GLdouble red;
	GLdouble green;
	GLdouble blue;
};


#endif
