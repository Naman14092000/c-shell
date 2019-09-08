#include "global.h"
void SETENV(char *name, char *value)
{
  char *old_name = getenv(name);
  if (!old_name)
  {
    putenv(name);
    setenv(name, value, 1);
  }
  else
  {
    setenv(name, value, 1);
  }
}