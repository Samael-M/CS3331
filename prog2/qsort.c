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

int main(int argv, char* argc[]) {

}