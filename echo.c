#include "global.h"
void ECHOAYA(char *str,int spcnt)
{
  trim(str);
  char sentence[100];
  char sentence1[100];
  sentence[0]='\0';
  sentence1[0]='\0';

  for (i = 5; i < strlen(str); i++)
  {
    sentence[i - 5] = str[i];
  }
  trim(sentence);
  for (j = i; j > 0; j--)
  {
    if (sentence[j] != ' ')
    {
      break;
    }
  }
  sentence[j + 1] = '\0';
  j = 0;
  int cnt = 0;
  char g = 'A';
  for (i = 0; i < strlen(sentence); i++)
  {
    if ((int)sentence[i] == 92)
    {
      sentence1[j++] = sentence[++i];
    }
    else if (g == 'A' && (int)sentence[i] == 34)
    {
      g = (char)34;
      cnt = 1;
    }
    else if (g == 'A' && (int)sentence[i] == 39)
    {
      g = (char)39;
      cnt = 1;
    }
    else if (g != 'A' && sentence[i] == g)
    {
      cnt++;
    }
    else
    {
      sentence1[j++] = sentence[i];
    }
  }
  sentence1[j] = '\0';
  if (cnt % 2 == 0)
  {
    printf("%s\n", sentence1);
  }
  else
  {
    printf("Please Enter a valid input\n");
  }
}
