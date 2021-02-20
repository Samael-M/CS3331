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
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <errno.h>

//https://pages.mtu.edu/~jshiebel/cs3331/PROG/PG2/prog2.html

// 1. Reads in three arrays a[], x[] and y[] into shared memory segments. k, m, and n are sizes of arrays respectively
// 2. prints out input arrays
// 3. creates child process to run qsort using execvp() and passes assignment Left, Right and other info needed. Initially Left and Right are 0 and k-1
// 4. creates second child process to run program merge.c using the execvp() system call and passes the needed command line arguments to merge.c
// 5. main.c waits for both child processes to complete, prints out the results, and terminates itself

int main(int argc, char* argv[]) {

    printf("Quicksort and Binary Merge with Multiple Processes:\n");

    //int to hold size of array
    int sizeOfA = 0;
    int sizeOfX = 0;
    int sizeOfY = 0;
    key_t key1;
    int ShmID1;
    int* a;
    key_t key2;
    int ShmID2;
    int* x;
    key_t key3;
    int ShmID3;
    int* y;
    key_t key4;
    int ShmID4;
    int* xy;
    char buff[100];
    int i;

    scanf("%d", &sizeOfA);
    key1 = ftok("./", 'x');
    printf("*** MAIN: shared memory1 key1 = %d\n", key1);
    ShmID1 = shmget(key1, sizeOfA*sizeof(int), IPC_CREAT | IPC_EXCL | 0666);
    printf("*** MAIN: shared memory1 created\n");
    a = (int *) shmat(ShmID1, NULL, 0);
    //loop through and scanf size times to fill array from input
    for(i = 0; i < sizeOfA; i++) {
        scanf("%d", &a[i]);
    }
    if(a == (void *)-1) {
        printf("ERROR: could attach memory\n");
        exit(1);
    }
    printf("*** MAIN: shared memory1 attached and ready to use\n");

    scanf("%d", &sizeOfX);
    key2 = ftok("./", 'y');
    printf("*** MAIN: shared memory key2 = %d\n", key2);
    ShmID2 = shmget(key2, sizeOfX*sizeof(int), IPC_CREAT | 0666);
    printf("*** MAIN: shared memory2 created\n");
    x = (int *) shmat(ShmID2, NULL, 0);
    for(i = 0; i < sizeOfX; i++) {
        scanf("%d", &x[i]);
    }
    if(x == (void *)-1) {
        printf("ERROR: could attach memory id=  %d\n", ShmID2);
        exit(1);
    }
    printf("*** MAIN: shared memory2 attached and ready to use\n");

    scanf("%d", &sizeOfY);
    key3 = ftok("./", 'z');
    printf("*** MAIN: shared memory key3 = %d\n", key3);
    ShmID3 = shmget(key3, sizeOfY*sizeof(int), IPC_CREAT | 0666);
    printf("*** MAIN: shared memory3 created\n");
    y = (int *) shmat(ShmID3, NULL, 0);
    for(i = 0; i < sizeOfY; i++) {
        scanf("%d", &y[i]);
    }
    if(y == (void *)-1) {
        printf("ERROR: could attach memory\n");
        exit(1);
    }
    printf("*** MAIN: shared memory3 attached and ready to use\n");

    key4 = ftok("./", 'a');
    printf("*** MAIN: shared memory key4 = %d\n", key4);
    ShmID4 = shmget(key4, (sizeOfX + sizeOfY)*sizeof(int), IPC_CREAT | 0666);
    printf("*** MAIN: shared memory4 created\n");
    xy = (int *) shmat(ShmID4, NULL, 0);
    if(xy == (void *)-1) {
        printf("ERROR: could attach memory\n");
        exit(1);
    }
    printf("*** MAIN: shared memory4 attached and ready to use\n");
    printf("\n");


    printf("Input array for qsort has %d elements:\n", sizeOfA);
    for(i = 0; i < sizeOfA; i++) {
        printf(" %d", a[i]);
    }
    printf("\nInput array x[] for merge has %d elements:\n", sizeOfX);
    for(i = 0; i < sizeOfX; i++) {
        printf(" %d", x[i]);
    }
    printf("\nInput array y[] for merge has %d elements:\n", sizeOfY);
    for(i = 0; i < sizeOfY; i++) {
        printf(" %d", y[i]);
    }
    printf("\n");


    // char left[11];
    // sprintf(left, "%d", 0);
    // char right[11];
    // sprintf(right, "%d", sizeOfA-1);
    // char* argx[4];
    // argx[0] = "qsort";
    // argx[1] = left;
    // argx[2] = right;
    // argx[3] = NULL;
    // pid_t pid1;
    // pid1 = fork();
    // if(pid1 < 0) {
    //     printf("ERROR: Process doesn't exist!\n");
    // }
    // else if(pid1 == 0) {
    //     if(execvp("./qsort", argx) < 0) {
    //         printf("###     ERROR: Execute qsort failed\n");
    //     }
    //     exit(1);
    // }

    char m[] = {"merge"};
    char sx[11];
    char sy[11];
    char sxy[11];
    sprintf(sx, "%d", sizeOfX);
    sprintf(sy, "%d", sizeOfY);
    sprintf(sxy, "%d", sizeOfX+sizeOfY);
    char* argz[5];
    argz[0] = m;
    argz[1] = sx;
    argz[2] = sy;
    argz[3] = sxy;
    argz[4] = '\0';
    int errnum;
    pid_t pid2; 
    pid2 = fork();
    if(pid2 < 0) {
        printf("Process doesn't exist!\n");
    }
    else if(pid2 == 0) {
        if(execvp("./merge", argz) < 0) {
            printf("###      ERROR: Execute Merge failed\n");
            errnum = errno;
            printf("%s\n", strerror(errnum));
        }
        printf("###      ERROR: Something went Wrong\n");
        exit(1);
    }
    while(wait(NULL) > 0){}

    sprintf(buff, "*** MAIN: sorted array by qsort\n\t");
    write(1, buff, strlen(buff));

    for(i = 0; i < sizeOfA; i++) {
        sprintf(buff, " %d", a[i]);
        write(1, buff, strlen(buff));
    }
    sprintf(buff, "\n");
    write(1, buff, strlen(buff));

    printf("*** MAIN: merged array:\n\t");
    for(i = 0; i < sizeOfX+sizeOfY; i++) {
        printf(" %d", xy[i]);
    }
    printf("\n");

    shmdt((void *) a);
    printf("*** MAIN: qsort shared memory successfully detached\n");
    shmdt((void *) x);
    printf("*** MAIN: merge shared memory1 successfully detached\n");
    shmdt((void *) y);
    printf("*** MAIN: merge shared memory2 successfully detached\n");
    shmdt((void *) xy);
    printf("*** MAIN: merge shared memory3 successfully detached\n");

    shmctl(ShmID1, IPC_RMID, NULL);
    printf("*** MAIN: qsort shared memory successfully removed\n");
    shmctl(ShmID2, IPC_RMID, NULL);
    printf("*** MAIN: merge shared memory1 successfully removed\n");
    shmctl(ShmID3, IPC_RMID, NULL);
    printf("*** MAIN: merge shared memory2 successfully removed\n");
    shmctl(ShmID4, IPC_RMID, NULL);
    printf("*** MAIN: merge shared memory3 successfully removed\n");

    printf("Main Process Exits\n");
}