#include "global.h"
int proc_cnt = 1;
void JOBS()
{
  struct bg_process *temp = root;
  while (temp)
  {
    int pid = temp->pid;
    char name[1000];
    name[0] = '\0';
    strcpy(name, temp->proc_name);
    char path[1000];
    sprintf(path, "/proc/%d/status", pid);
    int fd = open(path, O_RDONLY);
    char buff[200];
    read(fd, buff, 190);
    char *token = strtok(buff, "\n");
    token = strtok(NULL, "\n");
    token = strtok(NULL, "\n");
    char *token1 = strtok(token, " ");
    if (token1[strlen(token1) - 1] == 'R')
    {
      printf("[%d] Running %s [%d]\n", proc_cnt, name, pid);
    }
    if (token1[strlen(token1) - 1] == 'S')
    {
      printf("[%d] Stopped %s [%d]\n", proc_cnt, name, pid);
    }
    proc_cnt++;
    temp = temp->next;
  }
}