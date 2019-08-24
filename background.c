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
    struct bg_process *temp = root;
    if (temp != NULL && temp->pid == node->pid)
    {
        free(temp);
        return;
    }
    while (temp->next != NULL && temp->next->pid != node->pid)
    {
        temp = temp->next;
    }
    if (temp->next == NULL)
        return;
    temp->next = temp->next->next;
    free(temp->next);
}
