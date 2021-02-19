/* ----------------------------------------------------------- */
/* NAME : Samuel Milner                          */
/* DUE DATE : 02/17/21                                       */
/* PROGRAM ASSIGNMENT #2                                        */
/* PROGRAM PURPOSE:                                           */
/*           */
/* ----------------------------------------------------------- */



/*
    1. When merge.c runs, it receives whatever command line arguments
    2. Then, it creates m+n child processes, each of which is assigned to an element of x[ ] or an element of y[ ]
    3. Each child process carries out a modified binary search as discussed earlier to determine the final location of the assigned element in the sorted array
    4. When the final location is found, the process writes its assigned value into that location of the output array
    5. merge.c waits until all of its child processes exit, and terminates itself

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main(int argv, char* argc[]) {



}