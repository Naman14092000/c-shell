#include "global.h"
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
    command[0]='\0';
    for (int i = 0; i < commandidx; i++)
    {
        if (!strcmp(redir_commands[i], "<"))
        {
            int fd = open(redir_commands[i+1], O_RDONLY);
            if (fd < 0)
            {
                perror("Error opening file");
            }
            dup2(fd, 0);
            close(fd);
            flag=1;
            i++;
        }
        if (!strcmp(redir_commands[i], ">"))
        {
            int fd1 = open(redir_commands[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd1, 1);
            close(fd1);
            flag=1;
            i++;
        }
        if (!strcmp(redir_commands[i], ">>"))
        {
            int fd2 = open(redir_commands[i+1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(fd2,0);
            close(fd2);
            flag=1;
            i++;
        }
        if(!flag)
        {
            if(!strlen(command))
            {
                strcpy(command,redir_commands[i]);
            }
            else
            {
                strcat(command,redir_commands[i]);
            }
        }
    }
    char **dod=get_input(command);
    execvp(dod[0],dod);
}
// void JOBS()
// {
//   struct bg_process *temp=root;
//   int pro_cnt=0;
//   while(!temp)
//   {
//     int pid=temp->pid;
//     char path[50];
//     sprintf(path,"/proc/%d/status",pid);
//     int fd=open(path,O_RDONLY);
//     char buff[1000];
//     read(fd,buff,500);
//     char *token=strtok(buff,"\n");
//     printf("%s\n",token);
//     token=strtok(NULL,"\n");
//     printf("%s\n",token);
//     token=strtok(NULL,"\n");
//     printf("%s\n",token);
//     char *token1=strtok(token," ");
//     printf("%s\n",token1);
//     token1=strtok(NULL," ");
//     printf("%s\n",token1);
//     if(!strcmp("S",token1))
//     {
//       printf("[%d] Stopped %s [%d]\n",++pro_cnt,temp->proc_name,temp->pid);
//     }
//     else if(!strcmp("R",token1))
//     {
//       printf("[%d] Running %s [%d]\n",++pro_cnt,temp->proc_name,temp->pid);
//     }
//     temp=temp->next;
//   }
// }