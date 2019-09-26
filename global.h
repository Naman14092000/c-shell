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
#include <signal.h>
#include<sys/prctl.h>
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

void CD(char *str, int spcnt);
void DIRTY(int n);
void ECHOAYA(char *str, int spcnt);
void HISTORY(char *command, int spcnt);
void changemode(int dir);
int kbhit(void);
void INTERRUPT(int n);
void LS1(char *dir);
void LS2(char *dir);
void LS3(char *dir);
void LS(char *str, int spcnt);
void dostat(char *absoluteFileName, char *filename);
void mode_to_letters(int mode, char str[]);
char *uid_to_name(uid_t uid);
char *gid_to_name(gid_t gid);
void show_file_info(char *filename, struct stat *info_p);
void PINFO(char *str, int spcnt);
void curworkdir(char buf[]);
void trim(char *str);
void delete_bg(struct bg_process *node);
int background(char *str,int spcnt);
void writehist(char *sentence);
char **get_input(char *input);
void termination_check();
void insert(pid_t pid, char *str);
int redirection_check(char *str);
void interpreter(char *str);
void pipe_handle(char str[][100], int pipe_count);
int pipe_check(char *str);
pid_t forking();
void redirect(char *str);
void SETENV(char *name, char *value, int spcnt);
void UNSETENV(char *name, int spcnt);
void JOBS(int spcnt);
void K_JOB(char *str, int spcnt);
void OVERKILL(int spcnt);
void fg(int j_id, int ppid, int spcnt);
void bg(int j_id, int spcnt);
int proc_cnt;
char *UP(int cnt);
void CHRONJOB(char *str, int spcnt);
int spacecount(char *str);