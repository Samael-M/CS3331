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

char buff[100];
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
    sprintf(buff, "   $$$ M-PROC(%d) sx %d, sy %d, sxy %d\n", id, sx, sy, sxy);
    write(1, buff, strlen(buff));
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
            if(x[i] < y[0]) {
                xy[i] = x[i];
            }
            else if(x[i] > y[sy - 1]) {
                xy[sy+i] = x[i];
            }
            else {
                int k = binarySearch(x[i], y, sy);
                printf("k: %d\n", k+1);
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
            if(y[i] < x[0]) {
                xy[i] = y[i];
            }
            else if(y[i] > x[sx-1]) {
                xy[sx+i] = y[i];
            }
            else {
                int k = binarySearch(y[i], x, sx);
                printf("k: %d\n", k+1);
                xy[i+k] = y[i];
            }
            exit(1);
        }
    printf("\n");
    }
    while(wait(NULL) > 0) {}

    for(i = 0; i < sxy; i++) {
        sprintf(buff, "   xy[%d]\n", xy[i]);
        //write(1, buff, strlen(buff));
        printf("%d ", xy[i]);
    }
    printf("\n");

    shmdt((void *) x);
    shmdt((void *) y);
    shmdt((void *) xy);
    
}