#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* global variables */
int values[11] = {3, 12, 55, 6, 12, 34, 11, 2, 20, -3, 10};
double avg;
int min;
int max;

/* threads will call these methods */
void *runner1(void *param);
void *runner2(void *param);
void *runner3(void *param);

int main(void) {
    
    /* threads */
    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;

    /* thread default attrs */
    pthread_attr_t attr1;
    pthread_attr_t attr2;
    pthread_attr_t attr3;

    /* init thread attributes */
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_attr_init(&attr3);

    /* create the threads */
    pthread_create(&tid1, &attr1, runner1, NULL);
    pthread_create(&tid2, &attr2, runner2, NULL);
    pthread_create(&tid3, &attr3, runner3, NULL);

    /* join threads so the parent must wait for each one to complete */
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    /* after threads have completed, parent will display the results */
    printf("Average: %.2f\n", avg);
    printf("Minimum %d\n", min);
    printf("Maximum %d\n", max);

    return 0;

}

void *runner1(void *param) {
    int cnt = 0;
    double total = 0;
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        total += values[i];
        cnt++;
    }
    avg = total / cnt;
}

void *runner2(void *param) {
    min = values[0];
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        if (min > values[i]) {
            min = values[i];
        }
    }
}

void *runner3(void *param) {
    max = values[0];
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        if (values[i] > max) {
            max = values[i];
        }
    }
}