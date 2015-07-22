#include <GL/gl.h>

enum cellStatus
{
   DEAD,
   ALIVE,
   WAS_DEAD,
   WAS_ALIVE
};

class cell
{
private:
   cellStatus status;
public:
   cell(); //initial status is DEAD
   cell(GLint _status); //initialize a cell with stated status
   void setStatus(cellStatus s);
   cellStatus getStatus();
};
