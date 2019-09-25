#include "global.h"
void SETENV(char *name, char *value,int spcnt)
{
  if(spcnt>3 || spcnt<2)
  {
    printf("Invalid no of arguments\n");
    return;
  }
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