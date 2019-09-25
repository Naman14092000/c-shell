#include "global.h"
int fg_pid = 0;
int ctrlz = 0;
void zact(int sig)
{
  ctrlz = 1;
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGTSTP);
  sigprocmask(SIG_UNBLOCK, &mask, NULL);
  kill(fg_pid, SIGSTOP);
  return;
}
void interpreter(char *str)
{
  char strin[100],strout[100];
  int status;
  pid_t pid = forking();
  strcpy(strin, str);
  strcpy(strout,str);
  char **dod = get_input(str);
  int red_cnt = redirection_check(strin);
  int spcnt=spacecount(strout);
  if (red_cnt)
  {
    if (pid == 0)
    {
      redirect(strin);
      exit(0);
    }
    else
    {
      waitpid(pid, &status, 0);
    }
  }
  else if (strstr(strin, "&"))
  {
    if (pid == -1)
    {
      perror("Error forking");
      fflush(stdout);
    }
    else if (pid == 0)
    {
      background(strin,spcnt);
    }
    else
    {
      insert(pid, dod[0]);
    }
  }
  else if (!strcmp(dod[0], "cd"))
  {
    if (pid == 0)
    {
      CD(strin,spcnt);
    }
    else
    {
      waitpid(pid, &status, 0);
      exit(0);
    }
  }
  else if (!strcmp(dod[0], "jobs"))
  {
    if (pid == 0)
    {
      JOBS(spcnt);
      exit(0);
    }
    else
    {
      waitpid(pid, &status, 0);
    }
  }
  else if (!strcmp(dod[0], "kjob"))
  {
    if (pid == 0)
    {
      K_JOB(strin,spcnt);
      exit(0);
    }
    else
    {
      waitpid(pid, &status, 0);
    }
  }
  else if (!strcmp(dod[0], "overkill"))
  {
    if (pid == 0)
    {
      OVERKILL(spcnt);
      exit(0);
    }
    else
    {
      waitpid(pid, &status, 0);
    }
  }
  else if (!strcmp(dod[0], "ls"))
  {
    if (pid == 0)
    {
      LS(strin,spcnt);
      exit(0);
    }
    else
    {
      waitpid(pid, &status, 0);
    }
  }
  else if (!strcmp(dod[0], "setenv"))
  {
    if (pid == 0)
    {
      char *token4 = strtok(strin, " ");
      token4 = strtok(NULL, " ");
      char name[100], value[100];
      strcpy(name, token4);
      token4 = strtok(NULL, " ");
      for (int b = 1; b < strlen(token4) - 1; b++)
      {
        value[b - 1] = token4[b];
      }
      value[strlen(token4) - 2] = '\0';
      SETENV(name, value, spcnt);
      printf("%s %s\n", name, value);
      exit(0);
    }
    else
    {
      waitpid(pid, &status, 0);
    }
  }
  else if (!strcmp(dod[0], "unsetenv"))
  {
    if (pid == 0)
    {
      char *token4 = strtok(strin, " ");
      token4 = strtok(NULL, " ");
      UNSETENV(token4,spcnt);
      printf("%s\n", token4);
      exit(0);
    }
    else
    {
      waitpid(pid, &status, 0);
    }
  }
  else if (!strcmp(dod[0], "bg"))
  {
    if (pid == 0)
    {
      bg(atoi(dod[1]),spcnt);
      exit(0);
    }
    else
    {
      waitpid(pid, &status, 0);
    }
  }
  else if (!strcmp(dod[0], "fg"))
  {
    if (pid == 0)
    {
      int ppid = getppid();
      fg(atoi(dod[1]), ppid,spcnt);
      exit(0);
    }
    else
    {
      waitpid(pid, &status, 0);
    }
  }
  else if (!strcmp(dod[0], "echo"))
  {
    if (pid == 0)
    {
      ECHOAYA(strin,spcnt);
      exit(0);
    }
    else
    {
      waitpid(pid, &status, 0);
    }
  }
  else if (!strcmp(dod[0], "history"))
  {
    if (pid == 0)
    {
      HISTORY(strin,spcnt);
      exit(0);
    }
    else
    {
      waitpid(pid, &status, 0);
    }
  }
  else if (!strcmp(dod[0], "pinfo"))
  {
    if (pid == 0)
    {
      PINFO(strin,spcnt);
      exit(0);
    }
    else
    {
      waitpid(pid, &status, 0);
    }
  }
  else if (!strcmp(dod[0], "pwd"))
  {
    if (pid == 0)
    {
      char cwd[100];
      curworkdir(cwd);
      printf("%s\n", cwd);
      exit(0);
    }
    else
    {
      waitpid(pid, &status, 0);
    }
  }
  else if (!strcmp(dod[0], "nightswatch"))
  {
    if (pid == 0)
    {
      if (!strcmp("interrupt", dod[3]))
      {
        INTERRUPT(atoi(dod[2]));
        changemode(0);
      }
      else if (!strcmp("dirty", dod[3]))
      {
        DIRTY(atoi(dod[2]));
        changemode(0);
      }
      exit(0);
    }
    else
    {
      waitpid(pid, &status, 0);
    }
  }
  else if(!strcmp(dod[0],"chronjob"))
  {
    if(pid==0)
    {
      CHRONJOB(strin,spcnt);
      exit(0);
    }
    else
    {
      waitpid(pid,&status,0);
    }
    
  }
  else if (!strcmp(dod[0], "quit"))
  {
    exit(0);
  }
  else
  {
    if (pid == 0)
    {
      if (execvp(dod[0], dod) == -1)
      {
        perror("Command Not Found");
      }
      exit(0);
    }
    else
    {
      fg_pid = pid;
      signal(SIGTSTP, zact);
      waitpid(pid, &status, WUNTRACED);
      if (ctrlz == 1)
      {
        insert(pid, dod[0]);
        ctrlz = 0;
      }
    }
  }
}