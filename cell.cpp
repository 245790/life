#include <GL/gl.h>

#include "cell.h"

cell::cell()
{
   status = DEAD;
   cellAge = 0;
}

cell::cell(GLint _status)
{
   cellAge = 0;
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

GLint cell::getAge()
{
   return cellAge;
}

void cell::incrementAge()
{
   if(cellAge < 3)
   {
      cellAge++;
   }
}

void cell::nullifyAge()
{
   cellAge = 0;
}