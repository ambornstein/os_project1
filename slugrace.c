#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

void main () {
    int myRandom;
    int time;
    int status;
    int slugs[4];
    struct timespec race_start;
    struct timespec finish_line;
    clock_gettime(CLOCK_REALTIME, &race_start);
    char buffer[2];

    for (int i=0; i < 4; i++)  {
        sprintf(buffer, "%d", (i+1));
        char* args[] = {"./slug", buffer,  NULL};
        int rc = fork();
        
        if (rc > 0) {
            printf("[Parent]: I forked off child %d. \n", rc);
            slugs[i] = rc;
        } else if (rc == 0) {
            // child process
            printf("\t[Child, PID: %d]: Executing './slug %s' command", (int) getpid(), buffer);
            execvp("./slug", args);
            exit(0);
        }
    }
    
    int slugs_finished = 0;
    while (slugs_finished < 4) {
        usleep(330000);
        int pid = waitpid(-1, &status, WNOHANG);
        if (pid == 0) {
            printf("The race is ongoing. The following children are still racing: ");
            for (int i=0; i<4; i++){ 
                if(slugs[i] != 0) { printf("%d ", slugs[i]); }
            }
            printf("\n");
        } else {
            clock_gettime(CLOCK_REALTIME, &finish_line);
            printf("Child %d has crossed the finish line! It took %lf seconds\n", pid, (double) (finish_line.tv_sec - race_start.tv_sec));
            for (int i=0; i<4; i++){
                if(slugs[i] == pid) { slugs[i] = 0; }
            }
            slugs_finished++;
        }
    }
    
    printf("The race is over! It took %lf seconds\n",  (double) (finish_line.tv_sec - race_start.tv_sec));

    exit(0);
}
