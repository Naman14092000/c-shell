#include "global.h"
void DIRTY(int n)
{
  while (1)
  {
    changemode(1);
    char ch;
    if(kbhit())
    {
      ch = getchar();
      if(ch=='q')
      {
        break;
      }
    }
    changemode(0);
    char inter[10000];
    int fd = open("/proc/meminfo", O_RDONLY);
    read(fd, inter, 10000);
    char *token = strtok(inter, "\n");
    int index = 0;
    char interrups[1000][100];
    while (token != NULL)
    {
      strcpy(interrups[index++], token);
      if (index == 100)
      {
        break;
      }
      token = strtok(NULL, "\n");
    }
    char *token1 = strtok(interrups[16], " ");
    while (token1 != NULL)
    {
      token1 = strtok(NULL, " ");
      if (token1 != NULL)
      {
        printf("%s ", token1);
      }
    }
    printf("\n");
    sleep(n);
  }
}
