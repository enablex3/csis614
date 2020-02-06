#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n_values[10000]; // 10000 as max number of integers in the array
int fibonacci_sequence[10000];
int n;
int f;

// Method to generate values for 'n'
void generateNValues() {
    for (int k = 0; k < f; k ++) {
        n_values[k] = k + 3;
    }
}

// thread calls this function
void *runner(void *param);

int main(void) {
    char buffer[5];
    pthread_t tid;
    pthread_attr_t attr;

    // we know 0 and 1 start the fibonacci sequence
    fibonacci_sequence[0] = 0;
    fibonacci_sequence[1] = 1;

    // get input from user
    printf("How many fibonacci numbers would you like? ");
    fflush(stdout);
    fgets(buffer, sizeof(buffer), stdin);
    f = atoi(buffer);

    // generate values for n
    generateNValues(f);
    // initialize thread
    pthread_attr_init(&attr);
    // create the thread
    pthread_create(&tid, &attr, runner, NULL);
    // run and wait for thread to finish
    pthread_join(tid, NULL);
    // display the generated sequence
    for (int k = 0; k < n; k++) {
        printf("%d ", fibonacci_sequence[k]);
    }
    printf("\n");
    return 0;
}

// Method to generate the fibonacci sequence (this is what the thread runs)
void *runner(void *param) {
    for (int k = 0; k < sizeof(n_values) / sizeof(n_values[0]); k++) {
        n = k + 2;
        fibonacci_sequence[n] = fibonacci_sequence[n - 1] + fibonacci_sequence[n - 2];
        if (n == f) {
            break;
        }
    }
    pthread_exit(0);
}