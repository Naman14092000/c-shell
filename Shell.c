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
    char *token1 = strtok(input, ";");
    int currindex = 0;
    while (token1 != NULL)
    {
      pid_t pid = forking();
      if (strstr(token1, "&"))
      {
        if (pid == -1)
        {
          perror("Error forking");
        }
        else if (pid == 0)
        {
          int p = background(token1);
        }
        else
        {
          dod = get_input(token1);
          struct bg_process *temp = root;
          if (root == NULL)
          {
            root = (struct bg_process *)malloc(sizeof(struct bg_process));
            root->next = (struct bg_process *)malloc(sizeof(struct bg_process));
            root->pid = pid;
            strcpy(root->proc_name, dod[0]);
            root->next->next = NULL;
            root->next->pid = 0;
            root->next->proc_name[0] = 0;
          }
          else
          {

            while (temp->next != NULL)
              temp = temp->next;

            strcpy(temp->proc_name, dod[0]);
            temp->next = (struct bg_process *)malloc(sizeof(struct bg_process));
            temp->pid = pid;
            temp->next->pid = 0;
            temp->next->proc_name[0] = '\0';
            temp->next->next = NULL;
          }
        }
      }
      else if (strstr(token1, "history"))
      {
        if (pid == 0)
        {
          HISTORY(token1);
          exit(0);
        }
        else
        {
          waitpid(pid, &status, 0);
        }
      }
      else if (token1[0] == 'c' && token1[1] == 'd')
      {
        if (pid == 0)
        {
          CD(token1);
        }
        else
        {
          waitpid(pid, &status, 0);
          exit(0);
        }
      }
      else if (token1[0] == 'l' && token1[1] == 's')
      {
        if (pid == 0)
        {
          LS(token1);
          exit(0);
        }
        else
        {
          waitpid(pid, &status, 0);
        }
      }
      else if (token1[0] == 'v' && token1[1] == 'i')
      {
        if (pid == 0)
        {
          dod = get_input(token1);
          execvp(dod[0], dod);
          exit(0);
        }
        else
        {
          waitpid(pid, &status, 0);
        }
      }
      else if (token1[0] == 'p' && token1[1] == 'w' && token1[2] == 'd')
      {
        if (pid == 0)
        {
          curworkdir(cwd);
          printf("%s\n", cwd);
          exit(0);
        }
        else
        {
          waitpid(pid, &status, 0);
          // wait(NULL);
        }
      }
      else if (token1[0] == 'e' && token1[1] == 'm' && token1[2] == 'a' && token1[3] == 'c' && token1[4] == 's')
      {
        if (pid == 0)
        {
          dod = get_input(token1);
          execvp(dod[0], dod);
          exit(0);
        }
        else
        {
          waitpid(pid, &status, 0);
        }
      }
      else if (token1[0] == 'e' && token1[1] == 'c' && token1[2] == 'h' && token1[3] == 'o')
      {
        if (pid == 0)
        {
          ECHOAYA(token1);
          exit(0);
        }
        else
        {
          waitpid(pid, &status, 0);
        }
      }
      else if (token1[0] == 'p' && token1[1] == 'i' && token1[2] == 'n' && token1[3] == 'f' && token1[4] == 'o')
      {
        if (pid == 0)
        {
          PINFO(token1);
          exit(0);
        }
        else
        {
          waitpid(pid, &status, 0);
        }
      }
      else if (token1[0] == 'e' && token1[1] == 'x' && token1[2] == 'i' && token1[3] == 't')
      {
        exit(0);
      }

      else
      {
        if (pid == 0)
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
          waitpid(pid, &status, 0);
        }
      }
      writehist(token1);
      token1 = strtok(NULL, ";");
    }
    struct bg_process *temp = root;
    while (temp != NULL && temp->next != NULL)
    {
      int ret = waitpid(temp->pid, &status, WNOHANG);

      if (ret == -1)
      {
        printf("Process %s with id %d", temp->proc_name, temp->pid);
        fflush(stdout);
        psignal(WTERMSIG(status), "exited by ");
        delete_bg(temp);
      }
      else if (ret > 0)
      {
        printf("Process %s with pid  %d exited normally\n", temp->proc_name, temp->pid);
        delete_bg(temp);
      }
      if (temp->next != NULL)
        temp = temp->next;
      else
        break;
    }
  }
}
