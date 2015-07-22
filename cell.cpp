#include <GL/gl.h>

#include "cell.h"

cell::cell()
{
   status = DEAD;
}

cell::cell(GLint _status)
{
   if(_status == 1)
   {
      status = ALIVE;
   }
   else
   {
      status = DEAD;
   }
}

void cell::setStatus(cellStatus s)
{
   if((GLint)s >= 0 && (GLint)s <=3)
   {
      status = s;
   }
}

cellStatus cell::getStatus()
{
   return status;
}