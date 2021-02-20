/* ----------------------------------------------------------- */
/* NAME : Samuel Milner                          */
/* DUE DATE : 02/18/21                                       */
/* PROGRAM ASSIGNMENT #2                                        */
/* PROGRAM PURPOSE:                                           */
/*  Merge Sort using shared memory
    uses fork to have a child for each element of two arrays and merges.         */
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
#include <errno.h>

int binarySearch(int k, int x[], int n) {
    //write(1, buff, strlen(buff));
    int j;
    for(j = 0; j < n-1; j++) {
        if(k < x[j]) {
            return j;
        }
    }
}

int main(int argc, char* argv[]) {

    char buff[1000];
    char buff2[1000];
    int id;
    id = getpid();
    int errnum;
    int ShmID;
    int key1;
    int key2;
    int key3;
    int sx;
    int sy;
    int sxy;
    sx = atoi(argv[1]);
    sy = atoi(argv[2]);
    sxy = atoi(argv[3]);
    int* x; //[] = {1, 3};
    int* y; //[] = {2, 4};
    int* xy; //[sxy];
    pid_t pid;
    int i;


    sprintf(buff, "   $$$ M-PROC(%d) \n", id);
    write(1, buff, strlen(buff));

    key1 = ftok("./", 'y');
    ShmID = shmget(key1, sx*sizeof(int), 0666);
    x = (int *) shmat(ShmID, NULL, 0);
    if(x == (void *)-1) { 
        sprintf(buff, "   $$$ M-PROC(%d) ERROR: couldn't attach memory\n", id);
        write(1, buff, strlen(buff));
        errnum = errno;
        sprintf(buff, "   $$$ M-PROC(%d) ERROR: %s\n", id, strerror(errnum));
        write(1, buff, strlen(buff));
        exit(errno);
    }

    key2 = ftok("./", 'z');
    ShmID = shmget(key2, sy*sizeof(int), 0666);
    y = (int *) shmat(ShmID, NULL, 0);
    if(y == (void *)-1) { 
        sprintf(buff, "   $$$ M-PROC(%d) ERROR: couldn't attach memory\n", id);
        write(1, buff, strlen(buff));
        errnum = errno;
        sprintf(buff, "   $$$ M-PROC(%d) ERROR: %s\n", id, strerror(errnum));
        write(1, buff, strlen(buff));
        exit(errno);
    }

    key3 = ftok("./", 'a');
    ShmID = shmget(key3, sxy*sizeof(int), 0666);
    xy = (int *) shmat(ShmID, NULL, 0);
    if(xy == (void *)-1) { 
        sprintf(buff, "   $$$ M-PROC(%d) ERROR: couldn't attach memory\n", id);
        write(1, buff, strlen(buff));
        errnum = errno;
        sprintf(buff, "   $$$ M-PROC(%d) ERROR: %s\n", id, strerror(errnum));
        write(1, buff, strlen(buff));
        exit(errno);
    }


    for(i = 0; i < sx; i++) {
        pid = fork();
        if(pid < 0) {
            sprintf(buff, "   $$$ M-PROC(%d) ERROR: Process Doesn't Exist\n", id);
            write(1, buff, strlen(buff));
        }
        else if(pid == 0) {
            sprintf(buff, "   $$$ M-PROC(%d) handling x[%d] = %d\n", id, i, x[i]);
            write(1, buff, strlen(buff));
            if(x[i] < y[0]) {
                sprintf(buff, "   $$$ M-PROC(%d) x[%d] = %d is found to be smaller than y[0] = %d\n", id, i, x[i], y[0]);
                sprintf(buff2, "   $$$ M-PROC(%d) about to write x[%d] = %d into position %d of the output array\n", id, i, x[i], i);
                strcat(buff, buff2);
                write(1, buff, strlen(buff));
                xy[i] = x[i];
            }
            else if(x[i] > y[sy - 1]) {
                sprintf(buff, "   $$$ M-PROC(%d) x[%d] = %d is found to be larger than y[%d] = %d\n", id, i, x[i], sy-1, y[sy-1]);
                sprintf(buff2, "   $$$ M-PROC(%d) about to write x[%d] = %d into position %d of the output array\n", id, i, x[i], sy+i);
                strcat(buff, buff2);
                write(1, buff, strlen(buff));
                xy[sy+i] = x[i];
            }
            else {
                int k = binarySearch(x[i], y, sy);
                sprintf(buff, "   $$$ M-PROC(%d) x[%d] = %d is found between y[%d] = %d and y[%d] = %d\n", id, i, x[i], k-1, y[k-1], k, y[k]);
                sprintf(buff2, "   $$$ M-PROC(%d) about to write x[%d] = %d into position %d of the output array\n", id, i, x[i], k+i);
                strcat(buff, buff2);
                write(1, buff, strlen(buff));
                xy[i+k] = x[i];
            }
            exit(1);
        }
    }
    
    for(i = 0; i < sy; i++) {
        pid = fork();
        if(pid < 0) {
            sprintf(buff, "   $$$ M-PROC(%d) ERROR: Process Doesn't Exist\n", id);
            write(1, buff, strlen(buff));
        }
        else if(pid == 0) {
            sprintf(buff, "   $$$ M-PROC(%d) handling y[%d] = %d\n", id, i, x[i]);
            write(1, buff, strlen(buff));
            if(y[i] < x[0]) {
                sprintf(buff, "   $$$ M-PROC(%d) y[%d] = %d is found to be smaller than x[0] = %d\n", id, i, y[i], x[0]);
                sprintf(buff2, "   $$$ M-PROC(%d) about to write y[%d] = %d into position %d of the output array\n", id, i, y[i], i);
                strcat(buff, buff2);
                write(1, buff, strlen(buff));
                xy[i] = y[i];
            }
            else if(y[i] > x[sx-1]) {
                sprintf(buff, "   $$$ M-PROC(%d) y[%d] = %d is found to be larger than x[%d] = %d\n", id, i, y[i], sx-1, y[sx-1]);
                sprintf(buff2, "   $$$ M-PROC(%d) about to write y[%d] = %d into position %d of the output array\n", id, i, y[i], sx+i);
                strcat(buff, buff2);
                write(1, buff, strlen(buff));
                xy[sx+i] = y[i];
            }
            else {
                int k = binarySearch(y[i], x, sx);
                sprintf(buff, "   $$$ M-PROC(%d) y[%d] = %d is found between x[%d] = %d and x[%d] = %d\n", id, i, y[i], k-1, x[k-1], k, x[k]);
                sprintf(buff2, "   $$$ M-PROC(%d) about to write y[%d] = %d into position %d of the output array\n", id, i, y[i], k+i);
                strcat(buff, buff2);
                write(1, buff, strlen(buff));
                xy[i+k] = y[i];
            }
            exit(1);
        }
    printf("\n");
    }
    while(wait(NULL) > 0) {}

    shmdt((void *) x);
    shmdt((void *) y);
    shmdt((void *) xy);
    sprintf(buff, "   $$$ M-PROC(%d)exits\n", id);
    write(1, buff, strlen(buff));
    
}