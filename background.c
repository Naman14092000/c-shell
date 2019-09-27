#include "global.h"

// function to send a command into background
int background(char *str, int spcnt)
{
    char **dod;
    if (spcnt <= 1)
    {
        printf("Invalid command\n");
        return 0;
    }
    dod = get_input(str);
    setpgid(0, 0);
    close(STDERR_FILENO);
    if (execvp(dod[0], dod) == -1)
    {
        perror("Could not execute command");
    }
}

// function to delete node corresponding to terminated background process
void delete_bg(struct bg_process *node)
{
    if (node == root)
    {
        root = NULL;
        return;
    }
    else
    {
        node->pid = node->next->pid;
        node->next = node->next->next;
        strcpy(node->proc_name, node->next->proc_name);
    }
}

// function to insert a node corresponding to a new background process
void insert(pid_t pid, char *str)
{
    struct bg_process *temp = root;
    if (root == NULL)
    {
        root = (struct bg_process *)malloc(sizeof(struct bg_process));
        root->next = (struct bg_process *)malloc(sizeof(struct bg_process));
        root->pid = pid;
        strcpy(root->proc_name, str);
        root->next->next = NULL;
        root->next->pid = 0;
        root->next->proc_name[0] = 0;
    }
    else
    {

        while (temp->next != NULL)
            temp = temp->next;

        strcpy(temp->proc_name, str);
        temp->next = (struct bg_process *)malloc(sizeof(struct bg_process));
        temp->pid = pid;
        temp->next->pid = 0;
        temp->next->proc_name[0] = '\0';
        temp->next->next = NULL;
    }
}

// function to check if some background process exited
void termination_check()
{
    struct bg_process *temp1 = root;
    int status;
    while (temp1 != NULL && temp1->next != NULL)
    {
        int ret = waitpid(temp1->pid, &status, WNOHANG);

        if (ret > 0)
        {
            if (WIFEXITED(status))
            {
                // if exited normally
                printf("Process %s with pid  %d exited normally\n", temp1->proc_name, temp1->pid);
                fflush(stdout);
                delete_bg(temp1);
            }
            else if (WIFSIGNALED(status))
            {
                // if exited abnormally
                printf("Process %s with id %d ", temp1->proc_name, temp1->pid);
                fflush(stdout);
                printf("exited by signal %d\n",WTERMSIG(status));
                delete_bg(temp1);
            }
        }
        if (temp1->next != NULL)
            temp1 = temp1->next;
        else
            break;
    }
}