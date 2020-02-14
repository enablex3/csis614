#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Write a C program that forks a child process
   that ultimately, becomes a zombie process. Retain
   zombie state for at least 10 seconds */

void countToOne() {
    exit(1);
}

int main(void) {
    pid_t pid;
    int status;

    /* create the child process */
    pid = fork();

    if (pid == 0) {
        // child
        countToOne();
        return 0;
    }
    // pause for a second
    if (pid > 0) {
        // parent
        for (int k = 1; k <= 10; k++) {
            system("ps -l | grep -i zombie");
            sleep(1);
        }
        wait(NULL);
    }
    return 0;
}