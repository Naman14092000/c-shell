#include "global.h"
// function to handle pipe seperated commands
void pipe_handle(char str[][100], int pipe_count)
{
    int status;
    int fd[2];
    int in_fd = dup(0);
    int out_fd = dup(1);
    for (int curr_cmd = 1; curr_cmd <= pipe_count; curr_cmd++)
    {
        if (curr_cmd == 1)
        {
            // first command
            pipe(fd);
            out_fd = dup(1);
            dup2(fd[1], 1);
        }
        if (curr_cmd == pipe_count)
        {
            // last command
            close(fd[1]);
            in_fd = dup(0);
            dup2(fd[0], 0);
            close(fd[0]);
        }
        else if (curr_cmd != 1 && curr_cmd != pipe_count)
        {
            // neither first nor last command
            close(fd[1]);            
            in_fd = dup(0);
            dup2(fd[0], 0);
            close(fd[0]);
            pipe(fd);            
            out_fd = dup(1);
            dup2(fd[1], 1);
        }
        pid_t pid = forking();
        if (pid == 0)
        {
            int red_cnt = redirection_check(str[curr_cmd - 1]);
            if (red_cnt)
            {
                // if commmand is including redirection
                redirect(str[curr_cmd - 1]);
            }
            else
            {
                // if there is no redirection
                interpreter(str[curr_cmd - 1]);
            }
            exit(0);
        }
        else if(pid>0)
        {
            waitpid(pid, &status, 0);
            dup2(in_fd, 0);
            dup2(out_fd, 1);
        }
        else
        {
            perror("fork failed");
        }
        
    }
}

int pipe_check(char *str)
{
    int pip_cnt = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '|')
        {
            pip_cnt++;
        }
    }
    return pip_cnt;
}