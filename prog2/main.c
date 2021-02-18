/* ----------------------------------------------------------- */
/* NAME : Samuel Milner                          */
/* DUE DATE : 02/17/21                                       */
/* PROGRAM ASSIGNMENT #2                                        */
/* PROGRAM PURPOSE:                                           */
/*           */
/* ----------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

//https://pages.mtu.edu/~jshiebel/cs3331/PROG/PG2/prog2.html

// 1. Reads in three arrays a[], x[] and y[] into shared memory segments. k, m, and n are sizes of arrays respectively
// 2. prints out input arrays
// 3. creates child process to run qsort using execvp() and passes assignment Left, Right and other info needed. Initially Left and Right are 0 and k-1
// 4. creates second child process to run program merge.c using the execvp() system call and passes the needed command line arguments to merge.c
// 5. main.c waits for both child processes to complete, prints out the results, and terminates itself

int main(int argc, char* argv[]) {

    FILE* input;
    input = fopen(argv[1], "r+");
    if(input == 0) { printf("ERROR: Couldn't open file\n"); return 0; }

    char inptBuff[255];
    int size = 0;
    int a[];
    int x[];
    int y[];

    fgets(inptBuff, 1, inptBuff);
    sscanf(inptBuff, "%d", &size);
    int i;
    for(i = 0; i < (size + size - 1); i++) {

    }


}