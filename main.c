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
   @brief Builtin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */

int ssc_cd(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "ssc: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("ssc");
        }
    }
    return 1;
}

/**
   @brief Builtin command: print help.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */

int ssc_help(char **args){
    int i;
    printf("Juan P. Romano SSC\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for(i = 0; 0 < ssc_num_builtins(); i++){
        printf(" %s\n", builtin_str[i]);
    }

    printf("Use de man command for instructions about other programs.\n");
    return 1;
}

/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */

int ssc_exit(char **args){
    printf("I will be back user!");
    return 0;
}

/**
  @brief Launch a program and wait for it to terminate.
  @param args Null terminated list of arguments (including program).
  @return Always returns 1, to continue execution.
 */

int ssc_launch(char **args){
    pid_t pid;
    int status;

    pid = fork();
    if(pid == 0){
        // Child process
        if(execvp(args[0], args) == -1){
            perror("ssc");
        }
        exit(EXIT_FAILURE);
    } else if(pid < 0){
        // Error forking
        perror("ssc");
    } else {
        // Parent process
        do {
            waitpid(pid, status, WUNTRACED);
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */

int ssc_launch(char **args){
    int i;

    if(args[0] == NULL)
        // There is an empty command entered
        return 1;

    for(i = 0; i < ssc_num_builtins(); i++){
        if(strcmp(args[0], builtin_str[i]) == 0 ){
            return (*builtin_func[i])(args);
        }

        return ssc_launch(args);
    }
}