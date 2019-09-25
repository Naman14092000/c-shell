#include "global.h"
void UNSETENV(char *name,int spcnt)
{
  if(spcnt>2 || spcnt<=1)
  {
    printf("Invalid no of arguments\n");
    return;
  }
  unsetenv(name);
}
