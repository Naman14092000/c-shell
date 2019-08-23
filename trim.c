#include "global.h"
void trim(char *str)
{
  char newstr[100];
  int flag = 0;
  int j = 0;
  for (int i = 0; i < strlen(str); i++)
  {
    if (str[i] != ' ' && str[i] != '\t')
    {
      newstr[j] = str[i];
      j++;
      flag = 1;
    }
    else if ((str[i] == ' ' || str[i] == '\t') && flag == 1)
    {
      newstr[j] = str[i];
      j++;
    }
  }
  newstr[j] = '\0';
  strcpy(str, newstr);
}
