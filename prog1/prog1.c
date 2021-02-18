/* ----------------------------------------------------------- */
/* NAME : Samuel Milner                          */
/* DUE DATE : 02/9/21                                       */
/* PROGRAM ASSIGNMENT #1                                        */
/* PROGRAM PURPOSE :                                           */
/*    4 proecss running concurrently, fibonacci sequence, buffosn needle, ellipse and pinball simulation        */
/* ----------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int fibonacci(int n)
{
    char buff[100];
    if (n > 2)
    {
        n = fibonacci(n - 1) + fibonacci(n - 2);
    }
    else if (n < 3 && n > 0)
        return 1;
    else
        return 0;
    return n;
}

void buffon(int r)
{
    // Buffons Needle Calcualtion = (2/pi)*(L/G)
    // for simplicity L = G = 1
    // r is the amount of times needle is thrown
    char buff[100];
    int t = 0; //amount of times needles crosses dividing line
    int i;
    for (i = 0; i < r; i++)
    {
        double a = (double)rand() / RAND_MAX;
        double d = (double)rand();
        d = d / (RAND_MAX / (2 * acos(-1.0)));

        if (d + sin(a) < 0.0 || d + sin(a) > 1.0)
        {
            t++;
        }
    }
    double final = t / (double)r;
    sprintf(buff, "     Estimated Probability is %f\n", final);
    write(1, buff, strlen(buff));
    //return t / (double)r; // amount of times needle crossed dividing line / amount of times needle thrown
}
void area(int a, int b, int s)
{
    char buff[100];
    int t = 0; // amount of points in ellipse
    int i;
    for (i = 0; i < s; i++)
    {                                                       //makes s (x,y) pairs
        double x = (double)rand() / (RAND_MAX / (double)a); //generate (x,y) pair
        double y = (double)rand() / (RAND_MAX / (double)b);

        if ((double)(x * x) / (a * a) + (y * y) / (b * b) <= 1)
        { // test if (x,y) pair is in ellipse
            t++;
        }
    }
    double est = (((double)t / s) * a * b) * 4.0;
    double actual = acos(-1.0) * a * b;
    sprintf(buff, "         Total Hits %d\n", t);
    write(1, buff, strlen(buff));

    sprintf(buff, "         Estimate Area is %f\n", est);
    write(1, buff, strlen(buff));

    sprintf(buff, "         Actual Area is %f\n", actual);
    write(1, buff, strlen(buff));


}
void pinball(int x, int y)
{
    //bins = x
    char buff[100];
    int bins[x];
    int bin; //track what bin we are over

    int i;
    int j; // for simulating ball drop, x-1 times
    for (i = 0; i < x; i++)
    {
        bins[i] = 0;
    }
    //for y simulations
    for (i = 0; i < y; i++)
    {
        bin = 0;
        for (j = 0; j < (x - 1); j++)
        {
            int random = rand() % 2;
            if (random == 0)
            {
                //stay in bin
            }
            if (random == 1)
            {
                bin++;
            }
        }
        bins[bin]++;
    }
    //Figure out what bin has most pins
    int largest = 0;
    for (i = 0; i < x; i++)
    {
        if (bins[i] > largest)
        {
            largest = bins[i];
        }
    }
    //print histogram
    for (i = 0; i < x; i++)
    {
        double percent = (bins[i] / (double) y) * 100.0;
        int histo = (int) round( bins[i] / (double) largest * 100) / 2;
        sprintf(buff, "%3d-( %7d)-(%5.2f%%) |", i, bins[i], percent);
        write(1, buff, strlen(buff));
        for (j = 0; j < histo; j++)
        {
            sprintf(buff, "*");
            write(1, buff, strlen(buff));
        }
        sprintf(buff, "\n");
        write(1, buff, strlen(buff));
    }
}

int main(int argc, char **argv)
{

    int n = atoi(argv[1]);
    int r = atoi(argv[2]);
    int a = atoi(argv[3]);
    int b = atoi(argv[4]);
    int s = atoi(argv[5]);
    int x = atoi(argv[6]);
    int y = atoi(argv[7]);
    char buff[100];

    printf("Main Process Started\n");
    printf("Fibonacci Input = %d\n", n);
    printf("Buffon's Needle Iterations %d\n", r);
    printf("Total Number of Random pairs = %d\n", s);
    printf("Semi-Major Axis Length = %d\n", a);
    printf("Semi-Minor Axis Length %d\n", b);
    printf("Number of bins %d\n", x);
    printf("Number of Ball Droppings %d\n", y);

    pid_t pid1;
    pid1 = fork();
    if(pid1 < 0) {
        printf("Process doesn't exist!\n");
    }
    else if(pid1 == 0) {
        sprintf(buff, "   Fibonacci Process Started\n");
        write(1, buff, strlen(buff));

        sprintf(buff, "   Input Number %d\n", n);
        write(1, buff, strlen(buff));
        int fib = fibonacci(n);
        sprintf(buff, "   Fibonacci Number f(%d) is %d\n", n, fib);
        write(1, buff, strlen(buff));
        sprintf(buff, "   Fibonacci Process Exits\n");
        write(1, buff, strlen(buff));
        exit(1);
    }
    pid_t pid2;
    pid2 = fork();
    if(pid2 < 0) {
        printf("Process doesn't exist!\n");
    }
    else if(pid2 == 0) {
        sprintf(buff, "     Buffon Process Started\n");
        write(1, buff, strlen(buff));
        sprintf(buff, "   Input Number %d\n", r);
        write(1, buff, strlen(buff));
        buffon(r);
        sprintf(buff, "     Buffon Process Exits\n");
        write(1, buff, strlen(buff));
        exit(1);
    }

    pid_t pid3;
    pid3 = fork();
    if(pid3 < 0) {
        printf("Process doesn't exist!\n");
    }
    else if(pid3 == 0) {
        sprintf(buff, "         Ellipse Area Process Started\n");
        write(1, buff, strlen(buff));

        sprintf(buff, "         Total Random Number Pairs %d\n", s);
        write(1, buff, strlen(buff));

        sprintf(buff, "         Semi-Major Axis Length %d\n", a);
        write(1, buff, strlen(buff));

        sprintf(buff, "         Semi-Major Axis Length %d\n", b);
        write(1, buff, strlen(buff));

        area(a, b, s);
        sprintf(buff, "         Ellipse Area Process Exits\n");
        write(1, buff, strlen(buff));
        exit(1);
    }

    pid_t pid4;
    pid4 = fork();
    if(pid4 < 0) {
        printf("   Process doesn't exist!\n");
    }
    else if(pid4 == 0) {
        sprintf(buff, "Pinball Process Started\n");
        write(1, buff, strlen(buff));
        pinball(x, y);
        sprintf(buff, "Pinball Process Exits\n");
        write(1, buff, strlen(buff));
        exit(1);
    }
    int i;
    for(i = 0; i < 4; i++) {
        pid_t pid_child;
        int status;
        pid_child = wait(&status);
    }
    printf("Main Process Exits\n");
}