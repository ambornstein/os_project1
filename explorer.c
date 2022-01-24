#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void main () {
    // Getting random seed
    char buffer[5];
    int childnum;
    int file = open("seed.txt", O_RDONLY);
    read(file, buffer, 5);
    int seed = atoi(buffer);
    printf("Read seed value: %d\n", seed);
    printf("\nIt's time to see the world/file system!\n");
    srand(seed);

    // Getting number of children
    char* directory;
    int myRandom;
    int status;
    char buf[256];

    

    for (int i=0; i < 5; i++)  {
        myRandom = rand();

        switch (myRandom%6) {
            case 0:
                directory = "/home";
                break;
            case 1:
                directory = "/proc";
                break;
            case 2:
                directory = "/proc/sys";
                break;
            case 3:
                directory = "/usr";
                break;
            case 4:
                directory = "/usr/bin";
                break;
            case 5:
                directory = "/bin";
                break;
        }

        chdir(directory);
        printf("Selection #%d: %s\n", (i+1), directory);
        if (getcwd(buf, sizeof(buf)) == NULL) {
            printf("Current reported directory: %s, [FAILED]\n", buf);
        }
        else {
            printf("Current reported directory: %s, [SUCCESS]\n", buf);
        }

        int rc = fork();
        
        if (rc > 0) {
            // parent process
            printf("[Parent]: I am waiting for PID %d to finish.\n", rc);
            wait(&status);
            printf("[Parent]: Child %d finished with status code %d. Onward!\n", rc, WEXITSTATUS(status));
        } else if (rc == 0) {
            // child process
            printf("\t[Child, PID: %d] Executing the 'ls -tr' command...\n", (int) getpid());
            char* args[] = {"ls", "-tr", NULL};
            int status_code = execvp("ls", args);
            exit(status_code);
        }
    }
    exit(0);
}
