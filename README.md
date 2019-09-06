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

Implemetns history
maximum commands stored = 20, maximum commands displayed = 10
syntax : history <num(between 1 to 10)>

### interrupt.c

Implement nightswatch -n <any number> interrupt
Press 'q' at any instant to exit.

### dirty.c
Implement nightswatch -n <any number> dirty
Press 'q' at any instant to exit.

### background.c
Implement a background command.
syntax : <any command> &.

### trim.c
Removes all whitespaces at start in a string.

### global.h

A header file containing global functions and variables
