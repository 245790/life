#include <GL/gl.h>
#include <string>
#include <vector>

#include "cell.h"

using namespace std;

class grid
{
private:
   vector<vector<cell> > grd;
   GLint width;
   GLint height;
   GLfloat cellWidth;
   vector<GLfloat> cellColor;
   vector<GLfloat> spaceColor;
   GLint findNeighbours(GLint x, GLint y);
   void initColor();
public:
   grid();
   void initGrid(GLint _width, GLint _height);
   void initGrid(GLint _width, GLint _height, GLint** settingArray);
   void initFromPlainText(string filename, GLint borderWidth);
   void initRandom(GLint _width, GLint _height, GLfloat randomCoefficient);
   void setCellWidth(GLfloat w);
   int getWidth();
   int getHeight();
   void update();
   void draw();
};