#include <fstream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <string>
#include <vector>

#include "grid.h"

GLint grid::findNeighbours(GLint x, GLint y)
{
   GLint neighbours = 0;
   for(GLint i = -1; i <= 1; i++)
   {
      for(GLint j = -1; j <= 1; j++)
      {
         if(i == 0 && j == 0)
         {
            continue;
         }
         if(grd[(x + i + height) % height][(y + j + width) % width].getStatus() == ALIVE ||
            grd[(x + i + height) % height][(y + j + width) % width].getStatus() == WAS_ALIVE)
         {
            neighbours++;
         }
      }
   }
   return neighbours;
}

grid::grid()
{

}

void grid::initGrid(GLint _width, GLint _height)
{
   height = _height;
   width = _width;
   // grd(_height, vector<cell>(_width));
   cell deadCell;
   vector<cell> allDead(width, deadCell);
   grd.assign(height, allDead);
}

void grid::initGrid(GLint _width, GLint _height, GLint** settingArray)
{
   height = _height;
   width = _width;
   cell deadCell;
   vector<cell> allDead(width, deadCell);
   grd.assign(height, allDead);
   
   for(GLint i = 0; i < _height; i++)
   {
      for(GLint j = 0; j < _width; j++)
      {
         if(settingArray[i][j] == 1)
         {
            grd[i][j].setStatus(ALIVE);
         }
         //else it will be DEAD as default
      }
   }
}

void grid::initFromPlainText(string filename, int borderWidth)
{
   ifstream fin;
   fin.open(filename);
   if(fin.good())
   {
      string currentString;
      do
      {
         getline(fin, currentString);
      }
      while(currentString[0] == '!');

      string lineOfBody = currentString; //that is, the first row of cells

      vector<string> body;

      body.push_back(lineOfBody);

      int rowNumber = 0;
      while(!fin.eof())
      {
         getline(fin, lineOfBody);
         body.push_back(lineOfBody);
         rowNumber++;
      }


      height = rowNumber + borderWidth * 2;

      unsigned int maxWidth = body[0].length();
      for(unsigned int i = 1; i < body.size(); i++)
      {
         if(body[i].length() > maxWidth)
         {
            maxWidth = body[i].length();
         }
      }
      width = maxWidth + borderWidth * 2;


      grd.resize(height);

      for(int i = 0; i < height; i++)
      {
         grd[i].resize(width);
      }

      for(int i = 0; i < height; i++)
      {
         for(int j = 0; j < width; j++)
         {
            grd[i][j].setStatus(DEAD);
         }
      }


      for(unsigned int i = 0; i < body.size(); i++)
      {
         for(unsigned int j = 0; j < body[i].length(); j++)
         {
            if(body[i][j] != '.')
            {
               grd[i + borderWidth][j + borderWidth].setStatus(ALIVE);
            }
         }
      }
   }
   else
   {
      height = 25;
      width = 80;
      grd.resize(height);

      for(int i = 0; i < height; i++)
      {
         grd[i].resize(width);
      }

      for(int i = 0; i < height; i++)
      {
         for(int j = 0; j < width; j++)
         {
            grd[i][j].setStatus(DEAD);
         }
      }
   }
}

int grid::getWidth()
{
   return width;
}

int grid::getHeight()
{
   return height;
}

void grid::draw()
{
   // float cellWidth;
   // if(glutGet(GLUT_WINDOW_WIDTH) > glutGet(GLUT_WINDOW_HEIGHT))
   // {
   //    if(width > height)
   //    {
         
   //    }
   // }
   // else
   // {
      
   // }
   for(GLint i = 0; i < height; i++)
   {
      for(GLint j = 0; j < width; j++)
      {
         if(grd[i][j].getStatus() == ALIVE)
         {
            glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
            glBegin(GL_POLYGON);
            glVertex2f( -1 + j * (2.0 / width), -1 +  i * (2.0 / height));
            glVertex2f( -1 + (j + 1) * (2.0 / width), -1 +  i * (2.0 / height));
            glVertex2f( -1 + (j + 1) * (2.0 / width), -1 + (i + 1) * (2.0 / height));
            glVertex2f( -1 + j * (2.0 / width), -1 + (i + 1) * (2.0 / height));
            glEnd();
         }
      }
   }
}

void grid::update()
{
   for(GLint i = 0; i < height; i++)
   {
      for(GLint j = 0; j < width; j++)
      {
         if(grd[i][j].getStatus() == DEAD &&
            findNeighbours(i, j) == 3)
         {
            grd[i][j].setStatus(WAS_DEAD);
         }
         if(grd[i][j].getStatus() == ALIVE &&
           (findNeighbours(i, j) < 2 || findNeighbours(i, j) > 3))
         {
            grd[i][j].setStatus(WAS_ALIVE);
         }
      }
   }
   for(GLint i = 0; i < height; i++)
   {
      for(GLint j = 0; j < width; j++)
      {
         if(grd[i][j].getStatus() == WAS_DEAD)
         {
            grd[i][j].setStatus(ALIVE);
         }
         if(grd[i][j].getStatus() == WAS_ALIVE)
         {
            grd[i][j].setStatus(DEAD);
         }
      }
   }
}