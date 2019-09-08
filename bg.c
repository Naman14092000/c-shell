#include "global.h"
void bg(int j_id)
{
  int cnt = 1;
  struct bg_process *temp=root;
  while (cnt < j_id)
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
  }
  kill(pid, SIGCONT);
}