#include "global.h"
void HISTORY(char commands[][100], int index, char *command)
{
  int idx = 10;
  char *token = strtok(command, " ");
  if (token != NULL)
  {
    token = strtok(NULL, " ");
    if (token != NULL)
    {
      idx = atoi(token);
    }
  }
  for (int e = 0; e < idx; e++)
  {
    if (strlen(commands[e]))
    {
      printf("%s\n", commands[e]);
    }
    else
    {
      break;
    }
  }
}
