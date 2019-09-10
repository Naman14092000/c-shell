#include "global.h"
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
            pipe(fd);
            out_fd = dup(1);
            dup2(fd[1], 1);
        }
        if (curr_cmd == pipe_count)
        {
            close(fd[1]);
            in_fd = dup(0);
            dup2(fd[0], 0);
            close(fd[0]);
        }
        else if (curr_cmd != 1 && curr_cmd != pipe_count)
        {
            pipe(fd);
            out_fd = dup(1);
            dup2(fd[1], 1);
            close(fd[1]);
            in_fd = dup(0);
            dup2(fd[0], 0);
            close(fd[0]);
        }
        pid_t pid = forking();
        if (pid == 0)
        {
            int red_cnt = redirection_check(str[curr_cmd - 1]);
            if (red_cnt)
            {
                redirect(str[curr_cmd - 1]);
            }
            else
            {
                interpreter(str[curr_cmd - 1]);
            }
            exit(0);
        }
        else
        {
            waitpid(pid, &status, 0);
            dup2(in_fd, 0);
            dup2(out_fd, 1);
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