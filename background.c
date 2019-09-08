#include "global.h"
int background(char *str)
{
    char **dod;
    dod = get_input(str);
    setpgid(0, 0);
    close(STDERR_FILENO);
    if (execvp(dod[0], dod) == -1)
    {
        perror("Could not execute command");
    }
}
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
void termination_check()
{
    struct bg_process *temp1 = root;
    int status;
    while (temp1 != NULL && temp1->next != NULL)
    {
        int ret = waitpid(temp1->pid, &status, WNOHANG);

        if (ret == -1)
        {
            printf("Process %s with id %d", temp1->proc_name, temp1->pid);
            fflush(stdout);
            psignal(WTERMSIG(status), "exited by ");
            delete_bg(temp1);
        }
        else if (ret > 0)
        {
            printf("Process %s with pid  %d exited normally\n", temp1->proc_name, temp1->pid);
            fflush(stdout);
            delete_bg(temp1);
        }
        if (temp1->next != NULL)
            temp1 = temp1->next;
        else
            break;
    }
}