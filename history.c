#include "global.h"
char path[256];
void writehist(char *sentence)
{
  char input[256];
  sprintf(input, "%s\n", sentence);
  sprintf(path, "%s/.history.txt", homedir);
  FILE *hisfile = fopen(path, "r");
  char temp[256];
  fgets(temp, 256, hisfile);
  int num = atoi(temp);
  char path1[256];
  sprintf(path1, "%s/temp", homedir);
  FILE *new = fopen(path1, "w");
  if (num == 20)
    num = 0;
  num = num + 1;
  sprintf(temp, "%d\n", num);
  fprintf(new, "%s", temp);
  for (int i = 0; i < 20; i++)
  {
    if (i + 1 == num)
    {
      fgets(temp, 256, hisfile);
      fputs(input, new);
    }
    else
    {
      if (fgets(temp, 256, hisfile) != NULL)
      {
        fprintf(new, "%s", temp);
        fflush(stdout);
      }
    }
  }
  fclose(hisfile);
  fclose(new);
  remove(path);
  rename(path1, path);
}
void HISTORY(char *command)
{
  int idx = 10;
  // printf("%s\n",command);
  char *token = strtok(command, " ");
  if (token != NULL)
  {
    token = strtok(NULL, " ");
    if (token != NULL)
    {
      idx = atoi(token);
    }
  }
  // printf("%d\n",idx);
  FILE *hisfile = fopen(path, "r");
  char temp[256];
  fgets(temp, 256, hisfile);
  int num = atoi(temp);
  // printf("%d\n",num);
  char his[20][256];
  // printf("%d\n",num-idx+21);
  for (int i = 0; i < 20; i++)
  {
    if(fgets(his[i], 256, hisfile)==NULL)
      his[i][0]='\0';

  }
  for (int i = (num - idx + 21) % 20; idx != 0; idx--)
  {
    if (his[i - 1] != NULL)
    {
      printf("%s", his[i - 1]);
    }
    if (i == 20)
      i = 1;
    else
      i++;
  }
  fclose(hisfile);
}