#include "global.h"
void K_JOB(char *str, int spcnt)
{
  if (spcnt != 3)
  {
    printf("Invalid no of arguments\n");
    return;
  }
  char *token = strtok(str, " ");
  token = strtok(NULL, " ");
  int jid = atoi(token);
  int cnt = 1;
  token = strtok(NULL, " ");
  struct bg_process *temp = root;
  while (cnt < jid && temp)
  {
    if (temp->next)
    {
      temp = temp->next;
    }
    else
      break;
    cnt++;
  }
  int pid;
  int status;
  if (cnt == jid)
  {
    pid = temp->pid;
    int sig = atoi(token);
    printf("Process %s with id %d exited by signal %d\n", temp->proc_name, temp->pid, sig);
    delete_bg(temp);
    kill(pid, sig);
  }
  else
  {
    printf("No such job number exist\n");
    return;
  }
}