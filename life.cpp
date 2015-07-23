#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>

#include "grid.h"

using namespace std;

void renderScene();

void setupRC();

void changeSize(GLsizei w, GLsizei h);

void timerFunction(GLint value);

grid field;

int main (int argc, char **argv)
{
   string ptName;
   cout<<"\nEnter plain text file name(it should be in 'patterns' directory): ";
   cin>>ptName;
   if(ptName != "random")
   {
      ptName = "patterns/" + ptName;
      int borderWidth;
      cout<<"\nEnter border width: ";
      cin>>borderWidth;
      field.initFromPlainText(ptName, borderWidth);
   }
   else
   {
      // int fieldWidth, fieldHeight;
      // cout<<"\nEnter field width: ";
      // cin>>fieldWidth;
      // cout<<"\nEnter field height: ";
      // cin>>fieldHeight;
      // float randomCoefficient;
      // cout<<"\nEnter randomness coefficient: ";
      // cin>>randomCoefficient;
      // field.initRandom(fieldWidth, fieldHeight, randomCoefficient);
   }

   const int windowWidth = 700;
   const int windowHeight = 700;

   if(windowWidth > windowHeight)
   {
      field.setCellWidth(windowHeight / field.getHeight());
   }
   else
   {
      field.setCellWidth(windowWidth / field.getWidth());
   }

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(windowWidth, windowHeight);
   glutCreateWindow("Conway's Game of Life");
   glutDisplayFunc(renderScene);
   glutReshapeFunc(changeSize);
   glutTimerFunc(100, timerFunction, 1);
   setupRC();
   glutMainLoop();
   return 0;
}

void renderScene()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0f, 0.0f, 0.0f);
   field.draw();
   glutSwapBuffers();
}

void setupRC()
{
   glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
}

void changeSize(GLsizei w, GLsizei h)
{
   if(w > h)
   {
      field.setCellWidth(h / field.getHeight());
   }
   else
   {
      field.setCellWidth(w / field.getWidth());
   }
   glViewport(0, 0, w, h);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
}

void timerFunction(GLint value)
{
   field.update();
   glutPostRedisplay();
   glutTimerFunc(100, timerFunction, 1);
}