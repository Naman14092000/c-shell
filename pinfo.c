#include "global.h"
void PINFO(char *str,int spcnt)
{
  if(spcnt>2)
  {
    printf("Invalid no of arguments\n");
    return;
  }
  trim(str);
  char process[100];
  char path[100];
  int pd = getppid();
  for (i = 5; i < strlen(str); i++)
  {
    process[i - 5] = str[i];
  }
  for (j = i - 6; j > 0; j--)
  {
    if (process[j] != ' ')
    {
      break;
    }
  }
  char data[1000];
  process[j + 1] = '\0';
  trim(process);
  printf("pid --  ");
  if (strlen(process) == 0)
  {
    sprintf(path, "/proc/%d/stat", pd);
    printf("%d", pd);
  }
  else
  {
    sprintf(path, "/proc/%s/stat", process);
    printf("%s", process);
  }
  int fd = open(path, O_RDONLY);
  read(fd, data, 1000);
  int cnt = 0;
  printf("\nProcess Status --  ");
  for (int i = 0; i < strlen(data); i++)
  {
    if (cnt == 2 && data[i] != ' ')
    {
      printf("%c", data[i]);
    }
    else if (cnt == 2 && data[i] == ' ')
    {
      printf("\nmemory ​ --  ");
    }
    if (data[i] == ' ')
    {
      cnt++;
    }
    if (cnt == 22 && data[i] != ' ')
    {
      printf("%c", data[i]);
    }
  }
  for (i = 5; i < strlen(str); i++)
  {
    process[i - 5] = str[i];
  }
  for (j = i - 6; j > 0; j--)
  {
    if (process[j] != ' ')
    {
      break;
    }
  }
  process[j + 1] = '\0';
  trim(process);
  printf("\nExecutable Path --​  ");
  if (strlen(process) == 0)
  {
    sprintf(path, "/proc/%d/exe", pd);
  }
  else
  {
    sprintf(path, "/proc/%s/exe", process);
  }
  char execu[100];
  realpath(path, execu);
  printf("%s\n", execu);
}
