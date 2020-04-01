#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

int request_resources(int customer_num, int request[]) {
    return 0;
}

int release_resources(int customer_num, int request[]) {
    return 0;
}

void *runner(void *params);

int main(void) {

    available[0] = 10;
    available[1] = 5;
    available[2] = 7;
    
    /* init threads */
    pthread_t customer1;
    pthread_t customer2;
    pthread_t customer3;
    pthread_t customer4;
    pthread_t customer5;

     /* thread default attrs */
    pthread_attr_t attrs;

    /* start threads */
    pthread_attr_init(&attrs);
    pthread_create(&customer1, &attrs, runner, NULL);

    pthread_attr_init(&attrs);
    pthread_create(&customer2, &attrs, runner, NULL);

    pthread_attr_init(&attrs);
    pthread_create(&customer3, &attrs, runner, NULL);

    pthread_attr_init(&attrs);
    pthread_create(&customer4, &attrs, runner, NULL);

    pthread_attr_init(&attrs);
    pthread_create(&customer5, &attrs, runner, NULL);
}

void *runner(void *params) {
    while(1) {
        sleep(1);
    }
}