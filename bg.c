#include "global.h"

// function that implement bg
void bg(int j_id, int spcnt)
{
  int cnt = 1;
  struct bg_process *temp = root;
  while (cnt < j_id && temp)
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
  if (cnt == j_id)
  {
    pid = temp->pid;
    kill(pid, SIGCONT);
  }
  else
  {
    printf("No such job number exist\n");
    return;
  }
}