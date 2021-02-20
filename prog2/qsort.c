/* ----------------------------------------------------------- */
/* NAME : Samuel Milner                          */
/* DUE DATE : 02/17/21                                       */
/* PROGRAM ASSIGNMENT #2                                        */
/* PROGRAM PURPOSE:                                           */
/*           */
/* ----------------------------------------------------------- */

/*
    1. When qsort.c runs, it receives the left and right section indices Left and Right and other information from its command line arguments
    2. Then, it partitions the array section a[Left..Right] into two at element a[M]. See your data structures and/or algorithms textbooks for 
    this partitioning procedure. After the partition is obtained, two child processes are created, each of which runs qsort.c using system call 
    execvp(). The first child receives Left and M-1, while the second receives M+1 and Right. The parent then waits until both child processes complete their job
    3. After this, program qsort.c exits
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

// p = left
// r = right

void swap(int *a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int array[], int left, int right) {
    int i = left;
    int M = array[right];
    int j;
    for(j = left; j < right; j++) {
        if(array[j] < M) {
            swap(&array[i], &array[j]);
            i++;
        }
    }
    swap(&array[i], &array[right]);
    return i;
}

void quicksort(int array[], int left, int right) {
    char buff[100];
    pid_t pid1;
    pid_t pid2;
    int q;
    q = partition(array, left, right);

    char l[11];
    sprintf(l, "%d", left);
    char r[11];
    sprintf(r, "%d", q - 1);
    char* argx[4];
    argx[0] = "qsort";
    argx[1] = l;
    argx[2] = r;
    argx[3] = NULL;

    char l2[11];
    sprintf(l2, "%d", q + 1);
    char r2[11];
    sprintf(r2, "%d", right);
    char* argz[4];
    argz[0] = "qsort";
    argz[1] = l2;
    argz[2] = r2;
    argz[3] = NULL;

    pid1 = fork();
    if(pid1 < 0) {
        sprintf(buff, "   ### ERROR: Process doesn't exist!\n");
        write(1, buff, strlen(buff));
    }
    else if(pid1 == 0) {
        if(execvp("./qsort", argx) < 0) {
            sprintf(buff, "   ### ERROR Execution failed\n");
            write(1, buff, strlen(buff));
        }
        exit(1);
    }
    pid2 = fork();
    if(pid1 < 0) {
        sprintf(buff, "   ### ERROR: Process doesn't exist!\n");
        write(1, buff, strlen(buff));
    }
    else if(pid1 == 0) {
        if(execvp("./qsort", argz) < 0) {
            sprintf(buff, "   ### ERROR Execution failed\n");
            write(1, buff, strlen(buff));
        }
        exit(1);
    }
}

int main(int argc, char* argv[]) {

    char buff[100];
    int id;
    id = getpid();
    int errnum;
    int left;
    int right;
    left = atoi(argv[1]);
    right = atoi(argv[2]);
    int ShmID;
    int key;
    int* a;

    sprintf(buff, "   ### Q-PROC(%d) Entering with a[%d..%d]\n", id, left, right);
    write(1, buff, strlen(buff));

    key = ftok("./", 'x');
    int size = right-left;
    ShmID = shmget(key, size*sizeof(int), 0666);
    a = (int *) shmat(ShmID, NULL, 0);
    if(a == (void *)-1) { 
        sprintf(buff, "   ### Q-PROC(%d) ERROR: couldn't attach memory\n", id);
        write(1, buff, strlen(buff));
        errnum = errno;
        sprintf(buff, "   ### Q-PROC(%d) ERROR: %s\n", id, strerror(errnum));
        write(1, buff, strlen(buff));
        exit(errno);
    }
    if(left < right) {
        quicksort(a, left, right);
        while(wait(NULL) > 0) {}
    }
    while(wait(NULL) > 0) {}

    shmdt((void *) a);
    sprintf(buff, "   ### Q-PROC(%d): qsort shared memory successfully detached\n", id);
    write(1, buff, strlen(buff));
    
}