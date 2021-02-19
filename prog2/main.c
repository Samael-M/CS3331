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

//https://pages.mtu.edu/~jshiebel/cs3331/PROG/PG2/prog2.html

// 1. Reads in three arrays a[], x[] and y[] into shared memory segments. k, m, and n are sizes of arrays respectively
// 2. prints out input arrays
// 3. creates child process to run qsort using execvp() and passes assignment Left, Right and other info needed. Initially Left and Right are 0 and k-1
// 4. creates second child process to run program merge.c using the execvp() system call and passes the needed command line arguments to merge.c
// 5. main.c waits for both child processes to complete, prints out the results, and terminates itself

int main(int argc, char* argv[]) {

    

    //int to hold size of array
    int size = 0;
    int sizeOfA = 0;
    int sizeOfX = 0;
    int sizeOfY = 0;
    int i;
    scanf("%d", &size);
    int a[size];
    //loop through and scanf size times to fill array from input
    for(i = 0; i < size; i++) {
        scanf("%d", &a[i]);
        sizeOfA++;
    }
    scanf("%d", &size);
    int x[size];
    for(i = 0; i < size; i++) {
        scanf("%d", &x[i]);
        sizeOfX++;
    }
    scanf("%d", &size);
    int y[size];
    for(i = 0; i < size; i++) {
        scanf("%d", &y[i]);
        sizeOfY++;
    }
    printf("Quicksort and Binary Merge with Multiple Processes:\n");
    key_t key1;
    int ShmID1;
    int* qsortA;
    key1 = ftok("./", 'x');
    printf("*** MAIN: shared memory1 key1 = %d\n", key1);
    ShmID1 = shmget(key1, sizeOfA*sizeof(int), IPC_CREAT | 0666);
    printf("*** MAIN: shared memory1 created\n");
    qsortA = (int *) shmat(ShmID1, NULL, 0);
    if(qsortA == (void *)-1) {
        printf("ERROR: could attach memory\n");
        exit(1);
    }
    printf("*** MAIN: shared memory1 attached and ready to use\n");

    key_t key2;
    int ShmID2;
    int* mergeX;
    key2 = ftok("./", 'y');
    printf("*** MAIN: shared memory key2 = %d\n", key2);
    ShmID2 = shmget(key2, sizeOfX*sizeof(int), IPC_CREAT | 0666);
    printf("*** MAIN: shared memory2 created\n");
    mergeX = (int *) shmat(ShmID2, NULL, 0);
    if(mergeX == (void *)-1) {
        printf("ERROR: could attach memory id=  %d\n", ShmID2);
        exit(1);
    }
    printf("*** MAIN: shared memory2 attached and ready to use\n");

    key_t key3;
    int ShmID3;
    int* mergeY;
    key3 = ftok("./", 'z');
    printf("*** MAIN: shared memory key3 = %d\n", key3);
    ShmID3 = shmget(key3, (sizeOfY)*sizeof(int), IPC_CREAT | 0666);
    printf("*** MAIN: shared memory3 created\n");
    mergeY = (int *) shmat(ShmID3, NULL, 0);
    if(mergeY == (void *)-1) {
        printf("ERROR: could attach memory\n");
        exit(1);
    }
    printf("*** MAIN: shared memory3 attached and ready to use\n");

    key_t key4;
    int ShmID4;
    int* mergeXY;
    key4 = ftok("./", 'a');
    printf("*** MAIN: shared memory key4 = %d\n", key4);
    ShmID4 = shmget(key4, (sizeOfX + sizeOfY)*sizeof(int), IPC_CREAT | 0666);
    printf("*** MAIN: shared memory4 created\n");
    mergeXY = (int *) shmat(ShmID4, NULL, 0);
    if(mergeXY == (void *)-1) {
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

    pid_t pid1;
    pid1 = fork();
    if(pid1 < 0) {
        printf("Process doesn't exist!\n");
    }
    else if(pid1 == 0) {

    }

    pid_t pid2;
    pid2 = fork();
    if(pid2 < 0) {
        printf("Process doesn't exist!\n");
    }
    else if(pid2 == 0) {
        
    }
}