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
   GLint findNeighbours(GLint x, GLint y);
public:
   grid();
   void initGrid(GLint _width, GLint _height);
   void initGrid(GLint _width, GLint _height, GLint** settingArray);
   void initFromPlainText(string filename, int borderWidth);
   int getWidth();
   int getHeight();
   void update();
   void draw();
};