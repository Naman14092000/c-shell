#include "global.h"
int i, j, k;
char input[100000];
char *homedir;
int homedirlenght;
int commandindex = 0;
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
  fflush(stdout);
}
void SIGIhandler(int signalnum)
{
  signal(SIGINT, SIGIhandler);
  fflush(stdout);
}
void SIGhandler(int signalnum)
{
  signal(SIGTSTP, SIGhandler);
}
int main()
{
  signal(SIGINT, SIGIhandler);
  signal(SIGTSTP, SIGhandler);
  char *ctrld, *cwd, username[100], pc_name[100];
  cwd = (char *)malloc(sizeof(char) * 100);
  homedir = (char *)malloc(sizeof(char) * 100);
  int pd = getpid();
  char path[100];
  char *input;
  input = (char *)malloc(sizeof(char) * 1000);
  size_t size = 1024;
  sprintf(path, "/proc/%d/exe", pd);
  realpath(path, homedir);
  homedirlenght = strlen(homedir);
  homedir[homedirlenght - 6] = '\0';
  homedirlenght = strlen(homedir);
  int idx = 0;
  while (1)
  {
    int pid1, status;
    curworkdir(cwd);
    getuserdetails(username, pc_name, cwd);
    int up = 0;
    int cnt = 0;
    int var = 0;
    int flag=0;
    while (1)
    {
      char c = getchar();
      if (c == '\n' || c == EOF)
      {
        input[idx] = '\0';
        idx = 0;
        break;
      }
      if (var >= 1 && var < 2)
      {
        var++;
        continue;
      }
      else if(var==2)
      {
        var=0;
        int cha=c;
        if(cha==66)
        {
          cnt-=2;
        }
        else if(cha==65)
        {

        }
        else
        {
          flag=1;
        }
        
      }
      else
      {
        if ((int)c == 27 && !up)
        {
          cnt++;
          var = 1;
        }
        else
        {
          up = 1;
          input[idx++] = c;
        }
      }
    }
    if(flag)
    {
          printf("Invalid command\n");
          continue;
    }
    if (up == 0)
    {
      getuserdetails(username, pc_name, cwd);
      char pip_commands[20][100];
      int commandindex = 0, pip_commandindex = 0;
      char *runnext = UP(cnt);
      printf("%s\n", runnext);
      strcpy(input, runnext);
    }
    trim(input);
    char *separator = " ";

    char **dod;
    char token[100];
    int idx = 0;
    char *token2 = strtok(input, ";");
    int currindex = 0;
    char commands[10][100];
    char pip_commands[20][100];
    int commandindex = 0, pip_commandindex = 0;
    while (token2 != NULL)
    {
      strcpy(commands[commandindex++], token2);
      token2 = strtok(NULL, ";");
    }
    for (int q = 0; q < commandindex; q++)
    {
      int pipe_cnt = pipe_check(commands[q]);
      writehist(commands[q]);
      if (!pipe_cnt)
      {
        interpreter(commands[q]);
      }
      else if (pipe_cnt > 0)
      {
        char *token1 = strtok(commands[q], "|");
        while (token1 != NULL)
        {
          strcpy(pip_commands[pip_commandindex++], token1);
          token1 = strtok(NULL, "|");
        }
        pipe_handle(pip_commands, pipe_cnt + 1);
      }
      termination_check();
    }
  }
  return 0;
}
