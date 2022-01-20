#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void main () {
    // Getting random seed
    char buffer[5];
    int childnum;
    int file = open("seed.txt", O_RDONLY);
    read(file, buffer, 5);
    int seed = atoi(buffer);
    printf("Read seed value: %d\n", seed);
    srand(seed);

    // Getting number of children
    childnum = (rand() % (13 - 8 + 1) + 8);
    printf("Random Child Count: %d\n", childnum);    //Initialize time and exit code
    int myRandom;
    int time;
    int ecode;
    int status;

    for (int i=0; i < childnum; i++)  {
        int rc = fork();
        myRandom = rand();
        time = (myRandom % 3) + 1;
        ecode = (myRandom % 50) + 1;
        
        if (rc > 0) {
            printf("[Parent]: I am waiting for PID %d to finish.\n", rc);
            wait(&status);
            printf("[Parent]: Child %d finished with status code %d. Onward!\n", rc, WEXITSTATUS(status));
        } else if (rc == 0) {
            // child process
            printf("\t[Child, PID: %d] I am the child and I will wait %d seconds and exit with code %d.\n", (int) getpid(),time, ecode);
            sleep(time);
            printf("\t[Child, PID: %d] Now exiting\n", (int) getpid());
            exit(ecode);
        }
    }
    exit(0);
}
