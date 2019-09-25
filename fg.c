#include "global.h"
int signalFlag22 = 0;
int anotherSignalFlag22 = 0;

void anotherSignalHandler22(int sig)
{
  anotherSignalFlag22 = 1;
  return;
}

void signalHandler22(int sig)
{
  signalFlag22 = 1;
  return;
}
void fg(int j_id,int ppid,int spcnt)
{
  int cnt = 1;
  int status;
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
    delete_bg(temp);
    signal(SIGINT, signalHandler22);
    signal(SIGTSTP, anotherSignalHandler22);
    int g = kill(pid, SIGCONT);
    char commane[1000];
    sprintf(commane, "%s", temp->proc_name);
    printf("%d %s %d %d\n", pid, commane, g, ppid);
    int ret = waitpid(ppid, &status, WNOHANG);
    while (ret != pid)
    {
      // printf("%d\n", ret);
      if (signalFlag22 == 1)
      {
        kill(pid, SIGINT);
        signalFlag22 = 0;
        break;
      }
      if (anotherSignalFlag22 == 1)
      {
        kill(pid, SIGSTOP);
        insert(pid, commane);
        anotherSignalFlag22 = 0;
        break;
      }
      ret = waitpid(ppid, &status, WNOHANG);
      // printf("%d\n", __getpgid(pid));
    }
  }
  else
  {
    printf("No such job number exist\n");
    return;
  }
  
}