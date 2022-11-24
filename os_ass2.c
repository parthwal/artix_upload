#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sched.h>
#include <sys/resource.h>

int main()
{
    const int np = 3; // number of processes
    pid_t pid[3];
    double ptimes[3]; // process time
    double start[3];
    start[0] = (double)clock();
    pid[0] = fork();
    if (pid[0] == 0)
    {
        printf("Child0");
        execlp("./process1.sh", "./process1.sh", NULL);
    }
    else if (pid[0] < 0)
    {
        printf("Could not fork");
        exit(1);
    }

    start[1] = (double)clock();
    pid[1] = fork();
    if (pid[1] == 0)
    {
        printf("Child1");
        execlp("./process2.sh", "./process2.sh", NULL);
    }
    else if (pid[1] < 0)
    {
        printf("Could not fork");
        exit(1);
    }

    start[2] = (double)clock();
    pid[2] = fork();
    if (pid[2] == 0)
    {

        printf("Child2");
        execlp("./process3.sh", "./process3.sh", NULL);
    }
    else if (pid[2] < 0)
    {
        printf("Could not fork");
        exit(1);
    }

    for (int j = 0; j < 3; j++)
    {
        pid_t waitL = wait(NULL); // wait loop
        if (waitL == pid[0])
        {
            printf("\nprocess1_ended\n");
        }
        else if (waitL == pid[1])
        {
            printf("\nprocess2_ended\n");
        }
        else if (waitL == pid[2])
        {
            printf("\nprocess3_ended\n");
        }
    }
}