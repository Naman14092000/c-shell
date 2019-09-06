#include "global.h"
void interpreter(char *str)
{
  char strin[100];
  int status;
  pid_t pid=forking();
  strcpy(strin, str);
  char **dod = get_input(str);
  int red_cnt = redirection_check(strin);
  if (red_cnt)
  {
    if (pid == 0)
    {
      REDIRECT(strin, red_cnt);
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
      int p = background(strin, status);
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
      CD(strin);
    }
    else
    {
      waitpid(pid, &status, 0);
      exit(0);
    }
  }
  else if (!strcmp(dod[0], "ls"))
  {
    if (pid == 0)
    {
      LS(strin);
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
      ECHOAYA(strin);
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
      HISTORY(strin);
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
      PINFO(strin);
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
  else if (!strcmp(dod[0], "exit"))
  {
    exit(0);
  }
  else
  {
    if (pid == 0)
    {
      if (execvp(dod[0], dod) == -1)
      {
        printf("Invalid command\n");
      }
      exit(0);
    }
    else
    {
      waitpid(pid, &status, 0);
    }
  }
}