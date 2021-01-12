/*******************************************************************************
  @file         main.c
  @author       Juan P. Romano
  @date         Monday, 11 January, 2021
  @brief        SSIC (Simple Shell in C)
*******************************************************************************/

// Calling libraries

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Function Declarations for builtin shell commands:

int ssc_cd(char **args);
int ssc_help(char **args);
int ssc_exit(char **args);

// List of builtin commands, followed by their corresponding functions.

char *builtin_str[] = {
        "cd",
        "help",
        "exit"
};

// Now we assign the variables to the values in the commands array

int (*builtin_func[]) (char **) = {
        &ssc_cd,
        &ssc_help,
        &ssc_exit
};