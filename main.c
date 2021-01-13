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

int ssc_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

// Builtin function implementations.
/*
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */

int ssc_cd(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "ssc: expected argument to \"cd\"\n");
    }
}