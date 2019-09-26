# CSE ASSIGNMENT 2

## Aim

Implement a shell in C.

## How to run

```
make
./shell
```

## Source Files 

### main.c

Sets home directory and Displays the shell prompt(<user_name@system_name:curr_dir_path>)  and checks if a back-ground process has been completed 
 
### cd.c

Implements cd command

### ls.c

Implements ls command
Accepted flags: -l, -a, -la, -al, -l -a 

### pinfo.c

Implements pinfo command in the shell
syntax : pinfo <num(pid)>

### pwd.c

Implements pwd

### echo.c

Implements echo 

### history.c

Implements history
maximum commands stored = 20, maximum commands displayed = 10
syntax : history <num(between 1 to 10)>

### interrupt.c

Implement "nightswatch -n <any number> interrupt"
Press 'q' at any instant to exit.

### dirty.c
Implement "nightswatch -n <any number> dirty".
Press 'q' at any instant to exit.

### background.c
Implement a background command.
syntax : <any command> &.

### trim.c
Removes all whitespaces at start in a string.

### redirect_handle.c
Implement input and output redirection.
syntax : <any command> < inputfile > outputfile
there may be no inputfile or outputfile but atleast one should be present to go into REDIRECT function. 

### pipe_handler.c
Implement pipe and pipe with redirection.
syntax : <any command> | <any command> ....
atleast one pipe should be present for going into this.

### jobs.c
Implements "jobs" that prints all background process of current session with their current status.
syntax : jobs

### kjobs.c
Implement kjob that kills a job.
syntax : kjob <jobid> <signalnumber>

### overkill.c
Implement overkill that kill all the jobs
syntax : overkill

### setenv.c
Implement setenv that set a environment variable to a value.
syntax : setenv ​<variable name> [<value>]. ​

### unsetenv.c
Implement unsetenv that unset a environment variable.
syntax : unsetenv <variable name>

### fg.c
Implement fg that brings a background process to foreground.
syntax : fg <jobid>

### bg.c
Implement bg that changes a stopped background process to a running background process.
syntax : bg <jobid>

### chronjob.c
Implement chronjob that executes a particular command in fixed time interval for a certain period.
syntax : chronjob -c <any command> -t <any time interval> -p <any period>

### ctrl - c
My shell does not exit on pressing ctrl - c and on pressing ctrl - c, all foreground process that are running in my shell would be killed.

### ctrl - z
My shell does not go into background on pressing ctrl - z and on pressing ctrl - z, all foreground process that are running in my shell will go into background with stopped status.

### global.h

A header file containing global functions and variables