#ifndef POLYGON_H
#define POLYGON_H

#include <GL/glut.h>
#include <stdlib.h>
#include <vector>
#include "point.h"

class polygon{
public:
	polygon();
	polygon(std::vector<point> points, GLdouble red, GLdouble green, GLdouble blue);
	~polygon();
    std::vector<point> getPoints();
    GLdouble getRed();
    GLdouble getGreen();
    GLdouble getBlue();
    void setPoints(std::vector<point> input);
    void setRed(GLdouble input);
    void setGreen(GLdouble input);
    void setBlue(GLdouble input);
    void Draw();
    
private:
	std::vector<point> points;
	GLdouble red;
	GLdouble green;
	GLdouble blue;
};


#endif
