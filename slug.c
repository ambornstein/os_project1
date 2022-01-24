#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void main (int argc, char *argv[]) {
    // Getting random seed
    char buffer[5];
    char filename[16];
    if (argc <= 1) {
        printf("Please enter a command line argument\n");
        exit(0);
    }
    sprintf(filename, "seed_slug_%s.txt", argv[1]);
    int file = open(filename, O_RDONLY);
    read(file, buffer, 5);
    int seed = atoi(buffer);
    printf("[Slug PID: %d] Read seed value: %d\n", (int) getpid(), seed);
    srand(seed);
    int myRandom = rand();
    int time = (myRandom % 5) + 2;
    int coin = myRandom % 2;

    printf("[Slug PID: %d] Delay time is %d seconds. Coin flip: %d\n", (int) getpid(), time, coin);
    char* argslast[4] = {"last", "-i", "-x", NULL};
    char* argsid[3] = {"id", "--group", NULL};
    printf("[Slug PID: %d] I'll get the job done. Eventually...\n", (int) getpid());
    sleep(time);
    switch (coin) { 
        case 0:
            printf("[Slug PID: %d] Break time is over! I am running the 'last -i -x' command.\n", (int) getpid());
            execvp("last", argslast);
            break;
        case 1:
            printf("[Slug PID: %d] Break time is over! I am running the 'id --group' command.\n", (int) getpid());
            execvp("id", argsid);
            break;
    }
}