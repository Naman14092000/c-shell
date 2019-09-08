#include "global.h"
void OVERKILL()
{
  struct bg_process *temp = root;
  while (temp)
  {
    int pid = temp->pid;
    printf("Process %s with id %d exited by signal 9\n", temp->proc_name, temp->pid);
    delete_bg(temp);
    kill(pid, 9);
    if (temp->next)
    {
      temp = temp->next;
    }
    else
      break;
  }
}