#include <string.h>
#include <GL/glui.h>
#include <GL/glut.h>
#include <vector>
#include <string>
#include <fstream>
#include "point.h"
#include "line.h"
#include "rectangle.h"
#include "polygon.h"

// These are the live variables passed into GLUI
int wireframe = 0;
int globalRed = 0;
int globalBlue = 0;
int globalGreen = 0;
int main_window;

// Stores the points that are drawn on the screen
std::vector<point> points;

// Stores the lines that are drawn on the screen
std::vector<line> lines;

// Stores the rectangles that are drawn on the screen
std::vector<rectangle> rectangles;

// Stores the polygons that are drawn on the screen
std::vector<polygon> polygons;

// Stores points for a shape that is currently being drawn
std::vector<point> tempPoints;

std::string drawMode = "point";

int lastMouseX;
int lastMouseY;

void processMouse(int button, int state, int x, int y);
void processMouseActiveMotion(int x, int y);
void processMousePassiveMotion(int x, int y);
void processMouseEntry(int state);
std::vector<GLdouble> convert2DTo3D(int x, int y);

// convert2DTo3D()
std::vector<GLdouble> convert2DTo3D(int x, int y){
       std::vector<GLdouble> returnValues(3);
       // Unproject the 2D coordinates into 3D coordinates
       GLint viewport[4];
       GLdouble mvmatrix[16], projmatrix[16];
       GLint realy;  // OpenGL y coordinate position
       glGetIntegerv (GL_VIEWPORT, viewport);
       glGetDoublev (GL_MODELVIEW_MATRIX, mvmatrix);
       glGetDoublev (GL_PROJECTION_MATRIX, projmatrix);
       //  note viewport[3] is height of window in pixels
       realy = viewport[3] - (GLint) y - 1;
       gluUnProject ((GLdouble) x, (GLdouble) realy, 0.0, 
               mvmatrix, projmatrix, viewport, &returnValues[0], &returnValues[1], &returnValues[2]); 
       
       return returnValues;
}

// myGlutIdle()
void myGlutIdle(void)
{
  /* According to the GLUT specification, the current window is 
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if (glutGetWindow() != main_window)
  {
    glutSetWindow(main_window);  
  }
	
  glutPostRedisplay();
}

// This function is in charge of drawing the paint window
void myGlutDisplay(void)
{
    // Display Procedure for Main Window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Draw all points
    for(unsigned int i=0; i<points.size(); i++)
    {
          points[i].Draw();    
    }

    // Draw all lines
    for(unsigned int i=0; i<lines.size(); i++)
    {
          lines[i].Draw();    
    }

    // Draw all rectangles
    for(unsigned int i=0; i<rectangles.size(); i++)
    {
          rectangles[i].Draw();    
    }

    // Draw all polygons
    for(unsigned int i=0; i<polygons.size(); i++)
    {
          polygons[i].Draw();    
    }
    
    if(drawMode == "line" && tempPoints.size() != 0)
    {
       std::vector<GLdouble> DataPoint = convert2DTo3D(lastMouseX, lastMouseY);
       glBegin(GL_LINES);
       glColor3f( globalRed, globalGreen, globalBlue );
       glVertex3f(tempPoints[0].getX(), tempPoints[0].getY(), tempPoints[0].getZ());
       glVertex3f(DataPoint[0], DataPoint[1], DataPoint[2]);
       glEnd();             
    }

    if(drawMode == "polygon" && tempPoints.size() != 0)
    {
       std::vector<GLdouble> DataPoint = convert2DTo3D(lastMouseX, lastMouseY);
       if(tempPoints.size() > 1)
       {
          for(unsigned int i=0; i<tempPoints.size()-1; i++)
	  {
             glBegin(GL_LINES);
             glColor3f(globalRed, globalGreen, globalBlue);
             glVertex3f(tempPoints[i].getX(), tempPoints[i].getY(), tempPoints[i].getZ());
             glVertex3f(tempPoints[i+1].getX(), tempPoints[i+1].getY(), tempPoints[i+1].getZ());
             glEnd();          
          }
          glBegin(GL_LINES);
          glColor3f(globalRed, globalGreen, globalBlue);
          glVertex3f(tempPoints[tempPoints.size()-1].getX(), tempPoints[tempPoints.size()-1].getY(), tempPoints[tempPoints.size()-1].getZ());
          glVertex3f(DataPoint[0], DataPoint[1], DataPoint[2]);
          glEnd();            
       }
       else if(tempPoints.size() == 1)
       {
          glBegin(GL_LINES);
          glColor3f( globalRed, globalGreen, globalBlue );
          glVertex3f(tempPoints[0].getX(), tempPoints[0].getY(), tempPoints[0].getZ());
          glVertex3f(DataPoint[0], DataPoint[1], DataPoint[2]);
          glEnd();                  
       }
    }

    if(drawMode == "rectangle" && tempPoints.size() != 0)
    {
       std::vector<GLdouble> DataPoint = convert2DTo3D(lastMouseX, lastMouseY);
       if((DataPoint[0] > tempPoints[0].getX() && DataPoint[1] < tempPoints[0].getY()) || 
	  (DataPoint[0] < tempPoints[0].getX() && DataPoint[1] > tempPoints[0].getY()))
       {
           glBegin(GL_QUADS);
           glColor3f(globalRed, globalGreen, globalBlue);
           glVertex3f(DataPoint[0], tempPoints[0].getY(), tempPoints[0].getZ());
           glVertex3f(tempPoints[0].getX(), tempPoints[0].getY(), tempPoints[0].getZ());
           glVertex3f(tempPoints[0].getX(), DataPoint[1], DataPoint[2]);
           glVertex3f(DataPoint[0], DataPoint[1], DataPoint[2]);
           glEnd();             
       }
       else
       {
           glBegin(GL_QUADS);
           glColor3f(globalRed, globalGreen, globalBlue);
           glVertex3f(tempPoints[0].getX(), tempPoints[0].getY(), tempPoints[0].getZ());
           glVertex3f(DataPoint[0], tempPoints[0].getY(), tempPoints[0].getZ());
           glVertex3f(DataPoint[0], DataPoint[1], DataPoint[2]);
           glVertex3f(tempPoints[0].getX(), DataPoint[1], DataPoint[2]);
           glEnd();              
       }
    }
	
    glutSwapBuffers();
}

// Handles a window resize
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Right-Click Menu Callback
void DoMainMenu(int value)
{
	switch(value)
	{
        //If quit was selected, close program
	case 0:
	     // gracefully exit the program
	     glFinish();
	     exit(0);
             break;
        case 1:
             // Erase all drawings
             points.clear();
             lines.clear();
             rectangles.clear();
             polygons.clear();
             break;
        case 2:
             // Point mode
             drawMode = "point";
             break;
        case 3:
             // Line mode
             drawMode = "line";
             break;
        case 4:
             // Rectangle mode
             drawMode = "rectangle";
             break;     
        case 5:
             // Polygon mode
             drawMode = "polygon";
             break;     
	}
	tempPoints.clear();
}

// Main
int main(int argc, char* argv[])
{
  /****************************************/
  /*   Initialize GLUT and create window  */
  /****************************************/
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(10, 10);
  glutInitWindowSize(800, 400);
 
  main_window = glutCreateWindow("Dunderware Paint");
  glutDisplayFunc(myGlutDisplay);
  glutReshapeFunc(resize);
  glClearColor(1,1,1,1);
  glCullFace(GL_BACK);
  glDisable(GL_CULL_FACE);

    /* Create Right-Click Mouse Menu */
    int MainMenu = glutCreateMenu(DoMainMenu);
    glutAddMenuEntry("Polygon Mode", 5);
    glutAddMenuEntry("Rectangle Mode", 4);
    glutAddMenuEntry("Line Mode", 3);
    glutAddMenuEntry("Point Mode", 2);
    glutAddMenuEntry("Erase", 1);
    glutAddMenuEntry("Quit", 0);
	
    // attach the pop-up menu to the right mouse button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    // Setup Mouse Callbacks
    glutMouseFunc(processMouse);
    glutMotionFunc(processMouseActiveMotion);
    glutPassiveMotionFunc(processMousePassiveMotion);

  /****************************************/
  /*         GLUI code         */
  /****************************************/  
  GLUI* glui = GLUI_Master.create_glui("Toolbar", 0, 820, 10);
  GLUI_Button* point_button = glui->add_button("Point", 2, (GLUI_Update_CB)DoMainMenu);
  GLUI_Button* line_button = glui->add_button("Line", 3, (GLUI_Update_CB)DoMainMenu);
  GLUI_Button* rectangle_button = glui->add_button("Rectangle", 4, (GLUI_Update_CB)DoMainMenu); 
  GLUI_Button* polygon_button = glui->add_button("Polygon", 5, (GLUI_Update_CB)DoMainMenu);  
  GLUI_Button* erase_button = glui->add_button("Erase", 1, (GLUI_Update_CB)DoMainMenu);  
  
  GLUI_Spinner* segment_spinner_red = glui->add_spinner("Red:", GLUI_SPINNER_INT, &globalRed);
  segment_spinner_red->set_int_limits( 0, 255 ); 
  segment_spinner_red->set_speed( 0.1 ); 
  
  GLUI_Spinner* segment_spinner_green = glui->add_spinner("Green:", GLUI_SPINNER_INT, &globalGreen);
  segment_spinner_green->set_int_limits(0, 255);
  segment_spinner_green->set_speed(0.1);
  
  GLUI_Spinner* segment_spinner_blue = glui->add_spinner("Blue:", GLUI_SPINNER_INT, &globalBlue);
  segment_spinner_blue->set_int_limits(0, 255); 
  segment_spinner_blue->set_speed(0.1); 
     
  glui->set_main_gfx_window(main_window);

  // We register the idle callback with GLUI, *not* with GLUT
  GLUI_Master.set_glutIdleFunc(myGlutIdle); 

  glutMainLoop();
}

// Processes mouse events
void processMouse(int button, int state, int x, int y) 
{
        int specialKey = glutGetModifiers();
	
	// if both a mouse button, and the ALT key, are pressed  then
	if (state == GLUT_DOWN) 
	{
		// for the left button
		if (button == GLUT_LEFT_BUTTON) 
		{
           if(drawMode == "point")
	   {
              std::vector<GLdouble> DataPoint = convert2DTo3D(x, y);  
              points.push_back(point(DataPoint[0],DataPoint[1],DataPoint[2],globalRed, globalGreen, globalBlue));
           }
	   else if(drawMode == "line")
	   {
              if(tempPoints.size()==0)
	      {
                  std::vector<GLdouble> DataPoint = convert2DTo3D(x, y);  
                  tempPoints.push_back(point(DataPoint[0],DataPoint[1],DataPoint[2],globalRed, globalGreen, globalBlue));                        
              }
	      else
	      {
                  std::vector<GLdouble> DataPoint = convert2DTo3D(x, y);
                  tempPoints.push_back(point(DataPoint[0],DataPoint[1],DataPoint[2],globalRed, globalGreen, globalBlue));
                  lines.push_back(line(tempPoints[0],tempPoints[1],globalRed, globalGreen, globalBlue));
                  tempPoints.clear();
              }
           }
	   else if(drawMode == "rectangle")
	   {
              if(tempPoints.size()==0)
	      {
                  std::vector<GLdouble> DataPoint = convert2DTo3D(x, y);  
                  tempPoints.push_back(point(DataPoint[0], DataPoint[1], DataPoint[2], globalRed, globalGreen, globalBlue));                        
              }
	      else
	      {
                  std::vector<GLdouble> DataPoint = convert2DTo3D(x, y);
                  tempPoints.push_back(point(DataPoint[0], DataPoint[1], DataPoint[2], globalRed, globalGreen, globalBlue));
                  rectangles.push_back(rectangle(tempPoints[0], tempPoints[1], globalRed, globalGreen, globalBlue));
                  
                  std::ofstream fout;
                  fout.open("points.txt",std::ios::app);
                  fout << tempPoints[0].getX() << " " << tempPoints[0].getY() << std::endl;
                  fout << tempPoints[1].getX() << " " << tempPoints[1].getY() << std::endl;                  
                  tempPoints.clear();
              }                 
           }
	   else if(drawMode == "polygon")
	   {
               std::vector<GLdouble> DataPoint = convert2DTo3D(x, y);  
               tempPoints.push_back(point(DataPoint[0],DataPoint[1],DataPoint[2],globalRed, globalGreen, globalBlue));                                        
               double ratioX = DataPoint[0] / tempPoints[0].getX();
               double ratioY = DataPoint[1] / tempPoints[0].getY();
               if(ratioX <= 1.2 && ratioY <= 1.2 && ratioX >= 0.8 && ratioY >= 0.8 && tempPoints.size() > 2)
	       {
                  polygons.push_back(polygon(tempPoints,globalRed, globalGreen, globalBlue));
                  tempPoints.clear();
               }
	       else
	       {
                  tempPoints.push_back(point(DataPoint[0],DataPoint[1],DataPoint[2],globalRed, globalGreen, globalBlue));                                                             
               }
           }
		}
		// for the middle button
		else if (button == GLUT_MIDDLE_BUTTON) 
		{
			
		}
		// for the right button
		else 
		{
			// Ignore	
		}
	}
}


void processMouseActiveMotion(int x, int y) {
   lastMouseX = x;
   lastMouseY = y;
}

void processMousePassiveMotion(int x, int y) {
   lastMouseX = x;
   lastMouseY = y;
}

void processMouseEntry(int state) {

}

