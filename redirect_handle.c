#include "global.h"
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
  if(strstr(str, ">>"))
  {
    red_cnt+=2;
  }
  return red_cnt;
}
void REDIRECT(char *str, int red_cnt)
{
  char command[100], file_name[100], file_name2[100];
  if (red_cnt == 1)
  {
    char *token = strtok(str, "<");
    strcpy(command, token);
    token = strtok(NULL, " ");
    strcpy(file_name, token);
    trim(file_name);
    trim(command);
    char **dod = get_input(command);
    for (i = strlen(file_name) - 1; i > 0; i--)
    {
      if (file_name[i] != ' ')
      {
        break;
      }
    }
    file_name[i + 1] = '\0';
    for (i = strlen(command) - 1; i > 0; i--)
    {
      if (command[i] != ' ')
      {
        break;
      }
    }
    command[i + 1] = '\0';
    int fd = open(file_name, O_RDONLY);
    if (fd < 0)
    {
      perror("COuld not open file or file does not exist");
      return;
    }
    dup2(fd, 0);
    close(fd);
    execvp(dod[0], dod);
  }
  else if (red_cnt == 2)
  {
    char *token = strtok(str, ">");
    strcpy(command, token);
    token = strtok(NULL, " ");
    strcpy(file_name, token);
    trim(file_name);
    trim(command);
    char **dod = get_input(command);
    for (i = strlen(file_name) - 1; i > 0; i--)
    {
      if (file_name[i] != ' ')
      {
        break;
      }
    }
    file_name[i + 1] = '\0';
    for (i = strlen(command) - 1; i > 0; i--)
    {
      if (command[i] != ' ')
      {
        break;
      }
    }
    command[i + 1] = '\0';
    int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(fd, 1);
    close(fd);
    execvp(dod[0], dod);
  }
  else if (red_cnt == 3)
  {
    char *token = strtok(str, "<");
    strcpy(command, token);
    token = strtok(NULL, " ");
    strcpy(file_name, token);
    token = strtok(NULL, ">");
    strcpy(file_name2, token);
    trim(file_name);
    trim(command);
    trim(file_name2);
    char **dod = get_input(command);
    for (i = strlen(file_name) - 1; i > 0; i--)
    {
      if (file_name[i] != ' ')
      {
        break;
      }
    }
    file_name[i + 1] = '\0';
    for (i = strlen(command) - 1; i > 0; i--)
    {
      if (command[i] != ' ')
      {
        break;
      }
    }
    command[i + 1] = '\0';
    for (i = strlen(file_name2) - 1; i > 0; i--)
    {
      if (file_name2[i] != ' ')
      {
        break;
      }
    }
    file_name2[i + 1] = '\0';
    int fd = open(file_name, O_RDONLY);
    if (fd < 0)
    {
      perror("Could not open file or file does not exist");
      return;
    }
    int fd1 = open(file_name2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(fd,0);
    close(fd);
    dup2(fd1,1);
    close(fd1);
    execvp(dod[0],dod);
  }
  else if(red_cnt==4)
  {
    char *token = strtok(str, ">");
    strcpy(command, token);
    token = strtok(NULL, " ");
    token = strtok(NULL," ");
    strcpy(file_name, token);
    trim(file_name);
    trim(command);
    char **dod = get_input(command);
    for (i = strlen(file_name) - 1; i > 0; i--)
    {
      if (file_name[i] != ' ')
      {
        break;
      }
    }
    file_name[i + 1] = '\0';
    for (i = strlen(command) - 1; i > 0; i--)
    {
      if (command[i] != ' ')
      {
        break;
      }
    }
    command[i + 1] = '\0';
    int fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND , 0644);
    dup2(fd, 1);
    close(fd);
    execvp(dod[0], dod);
  }
  else if(red_cnt==5)
  {
    char *token = strtok(str, "<");
    strcpy(command, token);
    token = strtok(NULL, " ");
    strcpy(file_name, token);
    token = strtok(NULL, ">");
    strcpy(file_name2, token);
    trim(file_name);
    trim(command);
    trim(file_name2);
    char **dod = get_input(command);
    for (i = strlen(file_name) - 1; i > 0; i--)
    {
      if (file_name[i] != ' ')
      {
        break;
      }
    }
    file_name[i + 1] = '\0';
    for (i = strlen(command) - 1; i > 0; i--)
    {
      if (command[i] != ' ')
      {
        break;
      }
    }
    command[i + 1] = '\0';
    for (i = strlen(file_name2) - 1; i > 0; i--)
    {
      if (file_name2[i] != ' ')
      {
        break;
      }
    }
    file_name2[i + 1] = '\0';
    int fd = open(file_name, O_RDONLY);
    if (fd < 0)
    {
      perror("Could not open file or file does not exist");
      return;
    }
    int fd1 = open(file_name2, O_WRONLY | O_CREAT | O_APPEND, 0644);
    dup2(fd,0);
    close(fd);
    dup2(fd1,1);
    close(fd1);
    execvp(dod[0],dod);
  }
}