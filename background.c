#include "global.h"
int background(char *str, int status)
{
    setpgid(0, 0);
    close(STDERR_FILENO);
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '&')
        {
            str[i] = ' ';
        }
    }
    interpreter(str);
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
    struct bg_process *temp = root;
    int status;
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
            fflush(stdout);
            delete_bg(temp);
        }
        if (temp->next != NULL)
            temp = temp->next;
        else
            break;
    }
}