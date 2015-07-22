#include <GL/gl.h> //include the gl header file
#include <GL/glut.h> //include the glut header file
#include <iostream>

#include "grid.h"

using namespace std;

void renderScene();

void setupRC();

void changeSize(GLsizei w, GLsizei h);

void timerFunction(GLint value);

GLint gridSizeX;
GLint gridSizeY;
GLfloat cellSize;

grid field;

int main (int argc, char **argv)
{
   // cout<<"Enter the width of the field: ";
   // cin>>gridSizeX;
   // cout<<"\nEnter the height of the field: ";
   // cin>>gridSizeY;
   cout<<"\nEnter the cell size: ";
   cin>>cellSize;
   // cout<<"\n";

   // int seed;
   // cout<<"Enter seed: ";
   // cin>>seed;
   // srand(seed);
   // GLint **initArray;
   // initArray = new GLint*[gridSizeY];
   // for(GLint i = 0; i < gridSizeY; i++)
   // {
   //    initArray[i] = new GLint[gridSizeX];
   // }
   // //Empty field
   // for(GLint i = 0; i < gridSizeY; i++)
   // {
   //    for(GLint j = 0; j < gridSizeX; j++)
   //    {
   //       initArray[i][j] = 0;
   //    }
   // }
   //Random
   // for(GLint i = 0; i < gridSizeY; i++)
   // {
   //    for(GLint j = 0; j < gridSizeX; j++)
   //    {
   //       if(rand() % 2 == 0)
   //       {
   //          initArray[i][j] = 1;
   //       }
   //    }
   // }

   //Discovered by me
   // initArray[2][0] = 1;
   // initArray[2][1] = 1;
   // initArray[3][0] = 1;
   // initArray[3][1] = 1;

   // initArray[4][2] = 1;
   // initArray[4][3] = 1;
   // initArray[5][2] = 1;
   // initArray[5][3] = 1;

   //Heavyweight spaceship
   // initArray[5][5] = 1;
   // initArray[5][6] = 1;
   // initArray[5][7] = 1;
   // initArray[6][5] = 1;
   // initArray[7][5] = 1;
   // initArray[8][5] = 1;
   // initArray[9][5] = 1;
   // initArray[10][5] = 1;
   // initArray[6][8] = 1;
   // initArray[8][9] = 1;
   // initArray[9][9] = 1;
   // initArray[11][6] = 1;
   // initArray[11][8] = 1;


   //R-pentomino
   // initArray[5][3] = 1;
   // initArray[5][4] = 1;
   // initArray[5][5] = 1;
   // initArray[6][4] = 1;
   // initArray[4][5] = 1;

   //Glider
   // initArray[2][0] = 1;
   // initArray[2][1] = 1;
   // initArray[2][2] = 1;
   // initArray[1][2] = 1;
   // initArray[0][1] = 1;

   //Figure eight
   // initArray[5][5] = 1;
   // initArray[5][6] = 1;
   // initArray[5][7] = 1;
   // initArray[6][5] = 1;
   // initArray[6][6] = 1;
   // initArray[6][7] = 1;
   // initArray[7][5] = 1;
   // initArray[7][6] = 1;
   // initArray[7][7] = 1;

   // initArray[8][8] = 1;
   // initArray[8][9] = 1;
   // initArray[8][10] = 1;
   // initArray[9][8] = 1;
   // initArray[9][9] = 1;
   // initArray[9][10] = 1;
   // initArray[10][8] = 1;
   // initArray[10][9] = 1;
   // initArray[10][10] = 1;

   // field.initGrid(gridSizeX, gridSizeY, initArray);


   string ptName;
   cout<<"\nEnter plain text file name(it should be in 'patterns' directory): ";
   cin>>ptName;
   ptName = "patterns/" + ptName;
   int borderWidth;
   cout<<"\nEnter border width: ";
   cin>>borderWidth;
   field.initFromPlainText(ptName, borderWidth);


   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(field.getWidth() * cellSize * 2, field.getHeight() * cellSize * 2);
   glutCreateWindow("Conway's Game of Life");
   glutDisplayFunc(renderScene);
   //glutReshapeFunc(changeSize);
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
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void changeSize(GLsizei w, GLsizei h)
{
   GLfloat aspectRatio;
   if(h == 0)
   {
      h = 1;
   }
   glViewport(-w, -h, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   aspectRatio = (GLfloat)w/(GLfloat)h;
   if(w <= h)
   {
      //glOrtho(0.0, 50.0, -50.0/aspectRatio, 0, 1.0, -1.0);
      glOrtho(100, 100, 100, 100, 1.0, -1.0);
   }
   else
   {
      //glOrtho(0, 50.0*aspectRatio, -50.0, 0.0, 1.0, -1.0);
      glOrtho(500, -500, -500, 500, 1.0, -1.0);
   }
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void timerFunction(GLint value)
{
   field.update();
   glutPostRedisplay();
   glutTimerFunc(100, timerFunction, 1);
}