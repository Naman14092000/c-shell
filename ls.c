#include "global.h"
void LS(char *str,int spcnt)
{
  if(spcnt<1)
  {
    printf("Invalid no of arguments\n");
    return;
  }
  trim(str);
  char dir[200];
  char flags[50];
  int var = 0;
  int z = 0, flag = 0, cnt = 0;
  j = 0;
  dir[0] = '\0';
  for (i = 2; i < strlen(str); i++)
  {
    if (str[i] == '-')
    {
      cnt++;
    }
  }
  for (i = 2; i < strlen(str); i++)
  {
    if (flag == 0 && str[i] == '-')
    {
      flag = 1;
    }
    else if (flag == 1 && str[i] != ' ')
    {

      flags[z++] = str[i];
    }
    else if (flag == 1 && str[i] == ' ')
    {

      flag = 0;
    }
    else if (str[i] == '~')
    {
      var = 1;
      for (k = 0; k < strlen(homedir); k++)
      {
        dir[j] = homedir[k];
        j++;
      }
    }
    else
    {

      dir[j] = str[i];
      j++;
    }
  }

  for (i = j - 1; i > 0; i--)
  {
    if (dir[i] != ' ')
    {
      break;
    }
  }
  dir[i + 1] = '\0';
  flags[z] = '\0';
  trim(dir);
  int h = strlen(str) - strlen(flags) - 3 - (2 * cnt);
  if (var == 1)
  {
    h = strlen(homedir) + strlen(str) - 4 - strlen(flags) - (2 * cnt);
  }
  if (h < 0)
  {
    h = 0;
  }
  dir[h] = '\0';
  DIR *p;
  if (strlen(flags))
  {
    if ((flags[0] == 'l' && flags[1] == 'a') || (flags[0] == 'a' && flags[1] == 'l'))
    {
      LS1(dir);
    }
    else if (flags[0] == 'l')
    {
      LS2(dir);
    }
    else if (flags[0] == 'a')
    {
      LS3(dir);
    }
    else
    {
      printf("ls: invalid option -- '%s'\n", flags);
    }
  }
  else
  {
    struct dirent *dirname;
    if (strlen(dir) == 0)
    {
      curworkdir(dir);
    }
    p = opendir(dir);
    if (p == NULL)
    {
      perror("Cannot find directory");
    }
    while (dirname = readdir(p))
    {
      if ((strcmp(dirname->d_name, ".") == 0 || strcmp(dirname->d_name, "..") == 0 || (*dirname->d_name) == '.'))
      {
      }
      else
      {
        printf("%s\t", dirname->d_name);
      }
    }
    printf("\n");
  }
  exit(0);
}
void LS1(char *dir)
{
  DIR *p;
  struct dirent *dirname;
  j = 0;
  if (strlen(dir) == 0)
  {
    curworkdir(dir);
  }
  p = opendir(dir);
  if (p == NULL)
  {
    perror("Cannot find directory");
  }
  while (dirname = readdir(p))
  {
    char *p = (char *)malloc(strlen(dir) + strlen(dirname->d_name) + 2);
    if (p)
    {
      strcpy(p, dir);
      strcat(p, "/");
      strcat(p, dirname->d_name);
      dostat(p, dirname->d_name);
      free(p);
    }
    else
    {
      printf("Allocate memory failed!");
    }
  }
  exit(0);
}
void LS2(char *dir)
{
  DIR *p;
  struct dirent *dirname;
  j = 0;
  if (strlen(dir) == 0)
  {
    curworkdir(dir);
  }
  p = opendir(dir);
  if (p == NULL)
  {
    perror("Cannot find directory");
  }
  while (dirname = readdir(p))
  {
    char *p = (char *)malloc(strlen(dir) + strlen(dirname->d_name) + 2);
    if (p)
    {
      if ((strcmp(dirname->d_name, ".") == 0 || strcmp(dirname->d_name, "..") == 0 || (*dirname->d_name) == '.'))
      {
      }
      else
      {
        strcpy(p, dir);
        strcat(p, "/");
        strcat(p, dirname->d_name);
        dostat(p, dirname->d_name);
        free(p);
      }
    }
    else
    {
      printf("Allocate memory failed!");
    }
  }
  exit(0);
}
void LS3(char *dir)
{
  DIR *p;
  struct dirent *dirname;
  if (strlen(dir) == 0)
  {
    curworkdir(dir);
  }
  p = opendir(dir);
  if (p == NULL)
  {
    perror("Cannot find directory");
  }
  while (dirname = readdir(p))
  {
    printf("%s\t", dirname->d_name);
  }
  printf("\n");
  exit(0);
}
void dostat(char *absoluteFileName, char *filename)
{
  struct stat info;
  if (stat(absoluteFileName, &info) == -1)
    perror(filename);
  else
    show_file_info(filename, &info);
}
void mode_to_letters(int mode, char str[]);
char *uid_to_name(uid_t uid)
{
  struct passwd *getpwuid(), *pw_ptr;
  static char numstr[10];

  if ((pw_ptr = getpwuid(uid)) == NULL)
  {
    sprintf(numstr, "%d", uid);
    return numstr;
  }
  else
    return pw_ptr->pw_name;
}
char *gid_to_name(gid_t gid)
{
  struct group *getgrgid(), *grp_ptr;
  static char numstr[10];

  if ((grp_ptr = getgrgid(gid)) == NULL)
  {
    sprintf(numstr, "%d", gid);
    return numstr;
  }
  else
    return grp_ptr->gr_name;
}
void show_file_info(char *filename, struct stat *info_p)
{
  char *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
  char modestr[11];

  mode_to_letters(info_p->st_mode, modestr);

  printf("%s", modestr);
  printf("%4d ", (int)info_p->st_nlink);
  printf("%-8s ", uid_to_name(info_p->st_uid));
  printf("%-8s ", gid_to_name(info_p->st_gid));
  printf("%8ld ", (long)info_p->st_size);
  printf("%.12s ", 4 + ctime(&info_p->st_mtime));
  printf("%s\n", filename);
}
void mode_to_letters(int mode, char str[])
{
  strcpy(str, "----------");

  if (S_ISDIR(mode))
    str[0] = 'd';
  if (S_ISCHR(mode))
    str[0] = 'c';
  if (S_ISBLK(mode))
    str[0] = 'b';

  if (mode & S_IRUSR)
    str[1] = 'r';
  if (mode & S_IWUSR)
    str[2] = 'w';
  if (mode & S_IXUSR)
    str[3] = 'x';

  if (mode & S_IRGRP)
    str[4] = 'r';
  if (mode & S_IWGRP)
    str[5] = 'w';
  if (mode & S_IXGRP)
    str[6] = 'x';

  if (mode & S_IROTH)
    str[7] = 'r';
  if (mode & S_IWOTH)
    str[8] = 'w';
  if (mode & S_IXOTH)
    str[9] = 'x';
}
