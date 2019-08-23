#include "global.h"
int i, j, k;
char input[100000];
char *homedir;
int homedirlenght;
int commandindex=0;
char commands[20][100];
pid_t forking()
{
  pid_t pid;
  pid = fork();
  return pid;
}

char **get_input(char *input)
{
  char **command = malloc(100 * sizeof(char *));
  char *separator = " ";
  char *parsed;
  int index = 0;

  parsed = strtok(input, separator);
  while (parsed != NULL)
  {
    command[index] = parsed;
    index++;

    parsed = strtok(NULL, separator);
  }
  if (!strcmp(command[index - 1], "&"))
  {
    command[index - 1] = NULL;
  }
  else
  {
    command[index] = NULL;
  }
  return command;
}
int background(char *str)
{
  char **dod;
  dod = get_input(str);
  pid_t pid = forking();
  if (pid == -1)
  {
    perror("fork failed");
    exit(EXIT_FAILURE);
  }
  else if (pid == 0)
  {
    execvp(dod[0], dod);
    _exit(EXIT_SUCCESS);
  }
  else
  {
    int status;
    (void)waitpid(pid, &status, 0);
  }
  return EXIT_SUCCESS;
}

void getuserdetails(char username[], char pc_name[], char cwd[])
{
  struct passwd *details;
  uid_t user_id;
  char comp_name[100];
  user_id = geteuid();
  details = getpwuid(user_id);
  gethostname(comp_name, 100);
  strcpy(username, details->pw_name);
  strcpy(pc_name, comp_name);
  char CurrDir[200];
  if (homedirlenght <= strlen(cwd))
  {
    CurrDir[0] = '~';
    for (i = homedirlenght, j = 1; i < strlen(cwd); i++, j++)
    {
      CurrDir[j] = cwd[i];
    }
    CurrDir[j] = '\0';
  }
  else
  {
    strcpy(CurrDir, cwd);
  }
  printf("%s@%s:%s$ ", username, pc_name, CurrDir);
}
int main()
{
  char *ctrld, *cwd, username[100], pc_name[100];
  cwd = (char *)malloc(sizeof(char) * 100);
  homedir = (char *)malloc(sizeof(char) * 100);
  int pd=getpid();
  char path[100];
  sprintf(path,"/proc/%d/exe",pd);
  realpath(path,homedir);
  homedirlenght = strlen(homedir);
  homedir[homedirlenght-6]='\0';
  homedirlenght = strlen(homedir);
  while (1)
  {
    curworkdir(cwd);
    getuserdetails(username, pc_name, cwd);
    scanf("%[^\n]", input);
    getchar();
    trim(input);
    char *separator = " ";

    char **dod;
    char token[100];
    int idx = 0;
    char *token1 = strtok(input, ";");
    int currindex = 0;
    while (token1 != NULL)
    {
      if (strstr(token1, "&"))
      {
        int p = background(token1);
        int d = getpid();
        if (!p)
          printf("process %d exited normally", d);
      }
      else if (strstr(token1, "history"))
      {
        if (forking() == 0)
        {
          HISTORY(commands, commandindex, token1);
          exit(0);
        }
        else
        {
          wait(NULL);
        }
      }
      else if (token1[0] == 'c' && token1[1] == 'd')
      {
        if (forking() == 0)
        {
          CD(token1);
        }
        else
        {
          wait(NULL);
        }
      }
      else if (token1[0] == 'l' && token1[1] == 's')
      {
        if (forking() == 0)
        {
          LS(token1);
          exit(0);
        }
        else
        {
          wait(NULL);
        }
      }
      else if (token1[0] == 'v' && token1[1] == 'i')
      {
        if (forking() == 0)
        {
          dod = get_input(token1);
          execvp(dod[0], dod);
          exit(0);
        }
        else
        {
          wait(NULL);
        }
      }
      else if (token1[0] == 'p' && token1[1] == 'w' && token1[2] == 'd')
      {
        if (forking() == 0)
        {
          curworkdir(cwd);
          printf("%s\n", cwd);
          exit(0);
        }
        else
        {
          wait(NULL);
        }
      }
      else if (token1[0] == 'e' && token1[1] == 'm' && token1[2] == 'a' && token1[3] == 'c' && token1[4] == 's')
      {
        if (forking() == 0)
        {
          dod = get_input(token1);
          execvp(dod[0], dod);
          exit(0);
        }
        else
        {
          wait(NULL);
        }
      }
      else if (token1[0] == 'e' && token1[1] == 'c' && token1[2] == 'h' && token1[3] == 'o')
      {
        if (forking() == 0)
        {
          ECHOAYA(token1);
          exit(0);
        }
        else
        {
          wait(NULL);
        }
      }
      else if (token1[0] == 'p' && token1[1] == 'i' && token1[2] == 'n' && token1[3] == 'f' && token1[4] == 'o')
      {
        if (forking() == 0)
        {
          PINFO(token1);
          exit(0);
        }
        else
        {
          wait(NULL);
        }
      }
      else if (token1[0] == 'e' && token1[1] == 'x' && token1[2] == 'i' && token1[3] == 't')
      {
        exit(0);
      }

      else
      {
        if (forking() == 0)
        {
          dod = get_input(token1);
          if (!strcmp("nightswatch", dod[0]))
          {
            if (!strcmp("interrupt", dod[3]))
            {
              INTERRUPT(atoi(dod[2]));
              changemode(0);
              exit(0);
            }
            else if (!strcmp("dirty", dod[3]))
            {
              DIRTY(atoi(dod[2]));
              changemode(0);
              exit(0);
            }
          }

          else
          {
            execvp(dod[0], dod);
            exit(0);
          }
        }
        else
        {
          wait(NULL);
        }
      }
      if (commandindex == 20)
      {
        commandindex = 0;
      }
      strcpy(commands[commandindex++], token1);
      token1 = strtok(NULL, ";");
    }
  }
}
