#include "global.h"

// function that checks whether input or output redirection is present
int redirection_check(char *str)
{
  int red_cnt = 0;
  if (strstr(str, "<"))
  {
    red_cnt += 1;
  }
  if (strstr(str, ">"))
  {
    red_cnt += 2;
  }
  if (strstr(str, ">>"))
  {
    red_cnt += 2;
  }
  return red_cnt;
}

// function that implements redirection
void redirect(char *str)
{
  char redir_commands[30][100];
  char *token1 = strtok(str, " ");
  int commandidx = 0;
  while (token1 != NULL)
  {
    strcpy(redir_commands[commandidx++], token1);
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
      dup2(fd2, 1);
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
        int idx = strlen(command);
        command[idx] = ' ';
        command[idx + 1] = '\0';
        strcat(command, redir_commands[i]);
      }
    }
  }
  char **dod = get_input(command);
  if (execvp(dod[0], dod) < 0)
  {
    printf("Could not execute command\n");
  }
}