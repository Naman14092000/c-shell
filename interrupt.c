#include "global.h"
void changemode(int dir)
{
  static struct termios oldt, newt;
 
  if ( dir == 1 )
  {
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
  }
  else
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}
 
int kbhit (void)
{
  struct timeval tv;
  fd_set rdfs;
 
  tv.tv_sec = 0;
  tv.tv_usec = 0;
 
  FD_ZERO(&rdfs);
  FD_SET (STDIN_FILENO, &rdfs);
 
  select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
  return FD_ISSET(STDIN_FILENO, &rdfs);
 
}
void INTERRUPT(int n)
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
    int fd = open("/proc/interrupts", O_RDONLY);
    read(fd, inter, 10000);
    char *token = strtok(inter, " ");
    int index = 0;
    char interrups[1000][100];
    while (token != NULL)
    {
      strcpy(interrups[index++], token);
      if (index == 50)
      {
        break;
      }
      token = strtok(NULL, " ");
    }
    printf("CPU0\tCPU1\tCPU2\tCPU3\tCPU4\tCPU5\tCPU6\tCPU7\n");
    printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", interrups[22], interrups[23], interrups[24], interrups[25], interrups[26], interrups[27], interrups[28], interrups[29]);
    sleep(n);
  }
}
