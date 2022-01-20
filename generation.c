#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void descend(int lifespans) {
    //base case
    if (lifespans <= 0) { return; }

    int status;

    int rc = fork();
    if (rc > 0) {
        printf("[Parent, PID: %d]: I am waiting for PID %d to finish.\n", (int) getpid(), rc);
        wait(&status);
        printf("[Parent, PID: %d]: Child %d finished with status code %d. It's now my turn to exit.\n", (int) getpid(), rc, WEXITSTATUS(status));
    }
    else if (rc == 0) {
        // child process
        printf("\t[Child, PID: %d] I was called with descendant count=%d. I'll have %d descendant(s).\n",(int) getpid(), lifespans--, lifespans);
        descend(lifespans);
        exit(lifespans);
    }
}

void main () {
    // Getting random seed
    char buffer[5];
    int lifespans;
    int file = open("seed.txt", O_RDONLY);
    read(file, buffer, 5);
    int seed = atoi(buffer);
    printf("Read seed value: %i\n", seed);
    srand(seed);

    // Getting number of children
    lifespans = (rand() % (12 - 5 + 1) + 5);
    printf("Random Descendant Count: %d\nTime to meet the kids/grandkids/great grand kids/...\n", lifespans);
    descend(lifespans);
    exit(0);
}