#include "global.h"
// function to remove all the preceding whitespaces in a string
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

// function to find number of spaces in a string
int spacecount(char *str)
{
  char string2[1000];
  int spcnt=0;
  sprintf(string2,"%s",str);
  char *token=strtok(string2," ");
  while(token!=NULL)
  {
    spcnt++;
    token=strtok(NULL," ");
  }
  return spcnt;
}