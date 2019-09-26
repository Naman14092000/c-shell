#include "global.h"

// function that implements overkill
void OVERKILL(int spcnt)
{
  if(spcnt>1)
  {
    printf("Invalid no of arguments\n");
    return;
  }
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