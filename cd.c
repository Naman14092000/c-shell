#include "global.h"

//function that implements cd
void CD(char *str, int spcnt)
{
  if(spcnt>2)
  {
    printf("Invalid number of arguments\n");
    return;
  }
  char dir[200];
  j = 0;
  trim(str);
  for (int i = 2; i < strlen(str); i++)
  {
    if (str[i] == '~')
    {
      for (k = 0; k < strlen(homedir); k++)
      {
        dir[j] = homedir[k];
        j++;
      }
    }
    else if ((int)str[i] == 34)
    {
    }
    else
    {
      dir[j] = str[i];
      j++;
    }
  }
  for (i = j - 1; i > 0; i--)
  {
    if (dir[i] != ' ')
    {
      break;
    }
  }
  dir[i + 1] = '\0';
  trim(dir);
  if (strlen(dir) == 0)
  {
    strcpy(dir, homedir);
  }
  if(chdir(dir)<0)
  {
    // if directory not found
    printf("No such file or directory\n");
  }
}