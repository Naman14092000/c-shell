#include "global.h"

// function to execute a perticuler command after a regular time interval
void CHRONJOB(char *str, int spcnt)
{
    char redir_commands[20][100];
    int commandidx = 0;
    char *token = strtok(str, " ");
    while (token != NULL)
    {
        strcpy(redir_commands[commandidx++], token);
        token = strtok(NULL, " ");
    }
    char command[1000];
    command[0] = '\0';
    int flag = 0;
    int time = 0;
    int period = 0;
    for (int i = 0; i < commandidx; i++)
    {
        if (!strcmp(redir_commands[i], "-t"))
        {
            time = atoi(redir_commands[i + 1]);
            i++;
            flag = 0;
        }
        if (!strcmp(redir_commands[i], "-p"))
        {
            period = atoi(redir_commands[i + 1]);
            i++;
            flag = 0;
        }
        if (flag)
        {
            strcat(command, redir_commands[i]);
            int lenght = strlen(command);
            command[lenght] = ' ';
            command[lenght + 1] = '\0';
        }
        if (!strcmp(redir_commands[i], "-c"))
        {
            flag = 1;
        }
    }
    for (i = strlen(command) - 1; i >= 0; i--)
    {
        if (command[i] != ' ')
        {
            break;
        }
    }
    command[i + 1] = '\0';
    int j = period / time;
    char command1[1000];
    for (int i = 0; i < j; i++)
    {
        sleep(time);
        strcpy(command1, command);
        printf("%s %d\n", command1, j);
        int pid = forking();
        if (pid < 0)
        {
            perror("fork failed");
        }
        else if (pid == 0)
        {

            char **dod = get_input(command);
            execvp(dod[0], dod);
            // interpreter(command1);
            exit(0);
        }
        else
        {
            insert(pid, "chronjob");
        }
    }
    j = period % time;
    sleep(j);
}