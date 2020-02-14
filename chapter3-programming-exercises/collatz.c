#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Write a C program using fork() that generates
   the Collatz conjecture */


#define MAX 1000000

void generateCollatzSequence(int val) {
    printf("%d ", val);
    while (val != 1) {
        if (val % 2 == 0) {
            // val is even
            val = val / 2;
        }
        else {
            // val is odd
            val = (3 * val) + 1;
        }
        printf("%d ", val);
    }
    printf("\n");
    exit(0);
}

int main(void) {
    int val;
    char buff[MAX];
    pid_t pid;

    printf("Enter a value for n: ");
    fflush(stdout);

    fgets(buff, sizeof(buff), stdin);
    buff[strcspn(buff, "\n")] = 0;

    val = atoi(buff);
    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    }
    else if (val < 0) {
        printf("Please enter a positive integer\n");
        fflush(stdout);
        exit(1);
    }
    else {
        pid = fork();
        if (pid == 0) {
            generateCollatzSequence(val);
            return 0;
        }
        else {
            wait(NULL);
        }
    }
    return 0;
}