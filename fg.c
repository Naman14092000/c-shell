#include "global.h"
void fg(int j_id)
{
  int cnt = 1;
  int status;
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
  int g=kill(pid, SIGCONT);
  printf("%d %s %d\n",pid,temp->proc_name,g);
  waitpid(pid,&status,WUNTRACED);
}