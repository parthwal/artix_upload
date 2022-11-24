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
    long long ptimes[3]; // process time
    double start[3];
    long long t1,t2,t3;
    t1 = time(NULL);
    // start[0] = (double)clock();
    pid[0] = fork();
    if (pid[0] == 0)
    {
        setpriority(0, PRIO_PROCESS, 1);
        printf("Child0");
        execl("/bin/sh","sh","process1.sh", NULL);
        exit(0);
    }
    else if (pid[0] < 0)
    {
        printf("Could not fork");
        exit(1);
    }

    t2 = time(NULL);
    // start[1] = (double)clock();
    pid[1] = fork();
    if (pid[1] == 0)
    {
        setpriority(0, PRIO_PROCESS, 20);
        printf("Child1");
        // execlp("./process2.sh", "./process2.sh", NULL);
        execl("/bin/sh","sh","process2.sh", NULL);

        exit(0);
    }
    else if (pid[1] < 0)
    {
        printf("Could not fork");
        exit(1);
    }

    t3 = time(NULL);
    // start[2] = (double)clock();
    pid[2] = fork();
    if (pid[2] == 0)
    {
        setpriority(0, PRIO_PROCESS, 40);
        printf("Child2");
        // execlp("./process3.sh", "./process3.sh", NULL);
        execl("/bin/sh","sh","process3.sh", NULL);

        exit(0);
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
            ptimes[0] = (double)(time(NULL)-t1);//(double)(clock() - start[0])/(double)CLOCKS_PER_SEC;
        }
        else if (waitL == pid[1])
        {
            printf("\nprocess2_ended\n");
            ptimes[1] = (double)(time(NULL)-t2);//(double)(clock() - start[1])/(double)CLOCKS_PER_SEC;
        }
        else if (waitL == pid[2])
        {
            printf("\nprocess3_ended\n");
            ptimes[2] = (double)(time(NULL)-t3);//(double)(clock() - start[2])/(double)CLOCKS_PER_SEC;
        }
    }
    for(int i=0;i<np;i++){
        printf("\n%d: ",(int) pid[i]);
        printf("%d\n",(int)ptimes[i]);
    }
}
