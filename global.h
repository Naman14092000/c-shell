#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <termios.h>
#include <sys/time.h>
#include <grp.h>
#include <libgen.h>
int i, j, k;
char input[100000];
char *homedir;
int homedirlenght;
int commandindex;
char commands[20][100];
struct bg_process
{
  int pid;
  char proc_name[128];
  struct bg_process *next;
};
struct bg_process *root;

void CD(char *str);
void DIRTY(int n);
void ECHOAYA(char *str);
void HISTORY(char *command);
void changemode(int dir);
int kbhit (void);
void INTERRUPT(int n);
void LS1(char *dir);
void LS2(char *dir);
void LS3(char *dir);
void LS(char *str);
void dostat(char *absoluteFileName, char *filename);
void mode_to_letters(int mode, char str[]);
char *uid_to_name(uid_t uid);
char *gid_to_name(gid_t gid);
void show_file_info(char *filename, struct stat *info_p);
void PINFO(char *str);
void curworkdir(char buf[]);
void trim(char *str);
void addhistory(char *commmand);
void delete_bg(struct bg_process *node);
int background(char *str);
void writehist(char *sentence);
char **get_input(char *input);