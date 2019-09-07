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
void SETENV(char *name,char *value)
{
  char *old_name=getenv(name);
  if(!old_name)
  {
    putenv(name);
    setenv(name,value,1);
  }
  else
  {
   setenv(name,value,1); 
  }
}
void UNSETENV(char *name)
{
  unsetenv(name);
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
void redirect(char *str)
{
  char redir_commands[30][100];
  char *token1 = strtok(str, " ");
  int commandidx = 0;
  while (token1 != NULL)
  {
    strcpy(redir_commands[commandidx++], token1);
    printf("%s\n",token1);
    token1 = strtok(NULL, " ");
  }
  int flag = 0;
  char command[100];
  command[0] = '\0';
  for (int i = 0; i < commandidx; i++)
  {
    if (!strcmp(redir_commands[i], "<"))
    {
      int fd = open(redir_commands[i + 1], O_RDONLY);
      if (fd < 0)
      {
        perror("Error opening file");
      }
      dup2(fd, 0);
      close(fd);
      flag = 1;
      i++;
    }
    if (!strcmp(redir_commands[i], ">"))
    {
      int fd1 = open(redir_commands[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
      dup2(fd1, 1);
      close(fd1);
      flag = 1;
      i++;
    }
    if (!strcmp(redir_commands[i], ">>"))
    {
      int fd2 = open(redir_commands[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
      dup2(fd2, 0);
      close(fd2);
      flag = 1;
      i++;
    }
    if (!flag)
    {
      if (!strlen(command))
      {
        strcpy(command, redir_commands[i]);
      }
      else
      {
        strcat(command, redir_commands[i]);
      }
    }
  }
  char **dod = get_input(command);
  execvp(dod[0], dod);
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
int main()
{
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
    while (1)
    {
      char c = getchar();
      if (c == '\n' || c == EOF)
      {
        input[idx] = '\0';
        idx = 0;
        break;
      }
      else
      {
        input[idx++] = c;
      }
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
    }
    termination_check();
  }
}
