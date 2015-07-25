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

void grid::initColor()
{
   cellColor = {{0.6f, 0.6f, 0.6f}, //grey
               {0.4f, 0.4f, 0.4f}, //grey
               {0.2f, 0.2f, 0.2f}, //blacker grey
               {0.0f, 0.0f, 0.0f}}; //black
   spaceColor = {1.0f, 1.0f, 1.0f};
   ifstream fin("settings/colorTheme");
   for(int i = 0; i < 4; i++)
   {
      if(fin.good())
      {
         fin>>cellColor[i][0];
      }
      if(fin.good())
      {
         fin>>cellColor[i][1];
      }
      if(fin.good())
      {
         fin>>cellColor[i][2];
      }
   }
   if(fin.good())
   {
      fin>>spaceColor[0];
   }
   if(fin.good())
   {
      fin>>spaceColor[1];
   }
   if(fin.good())
   {
      fin>>spaceColor[2];
   }
   fin.close();
}

grid::grid()
{

}

void grid::initGrid(GLint _width, GLint _height)
{
   height = _height;
   width = _width;

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

void grid::initFromPlainText(string filename, GLint borderWidth)
{
   initColor();
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

      unsigned int bodySize = body.size();

      for(unsigned int i = 0; i < bodySize / 2; i++)
      {
         swap(body[i], body[bodySize - i - 1]);
      }

      height = rowNumber + borderWidth * 2;

      unsigned int maxWidth = body[0].length();
      for(unsigned int i = 1; i < bodySize; i++)
      {
         if(body[i].length() > maxWidth)
         {
            maxWidth = body[i].length();
         }
      }
      width = maxWidth + borderWidth * 2;

      cellWidth = 10;

      initGrid(width, height);

      for(unsigned int i = 0; i < bodySize; i++)
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
      initGrid(width, height);
   }
   fin.close();
}

void grid::initRandom(GLint _width, GLint _height, GLfloat randomCoefficient, GLint seed)
{
   initGrid(_width, _height);
   initColor();
   srand(seed);
   if(randomCoefficient < 0)
   {
      randomCoefficient = 0;
   }
   if(randomCoefficient > 1)
   {
      randomCoefficient = 1;
   }
   int rc = randomCoefficient * 100;
   for(int i = 0; i < height; i++)
   {
      for(int j = 0; j < width; j++)
      {
         if(rand() % 100 < rc)
         {
            grd[i][j].setStatus(ALIVE);
         }
      }
   }
}

void grid::setCellWidth(GLfloat w)
{
   cellWidth = w;
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
   glClearColor(spaceColor[0] / 256, spaceColor[1] / 256, spaceColor[2] / 256, 1.0f);
   for(GLint i = 0; i < height; i++)
   {
      for(GLint j = 0; j < width; j++)
      {
         if(grd[i][j].getStatus() == ALIVE)
         {
            GLint age = grd[i][j].getAge();
            glColor4f(cellColor[age][0] / 256, cellColor[age][1] / 256, cellColor[age][2] / 256, 1.0f);
            glBegin(GL_POLYGON);
               GLint x = j - width / 2;
               GLint y = i - height / 2;
               glVertex2f(x * cellWidth, y * cellWidth);
               glVertex2f((x + 1) * cellWidth, y * cellWidth);
               glVertex2f((x + 1) * cellWidth, (y + 1) * cellWidth);
               glVertex2f(x * cellWidth, (y + 1) * cellWidth);
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
         if(grd[i][j].getStatus() == ALIVE)
         {
            grd[i][j].incrementAge();
         }
         if(grd[i][j].getStatus() == WAS_DEAD)
         {
            grd[i][j].setStatus(ALIVE);
            grd[i][j].nullifyAge();
         }

         if(grd[i][j].getStatus() == WAS_ALIVE)
         {
            grd[i][j].setStatus(DEAD);
            grd[i][j].nullifyAge();
         }
      }
   }
}