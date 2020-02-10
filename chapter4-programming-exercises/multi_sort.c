#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_LEN 20

/* global variables */
int original_list[MAX_LEN] = {40, 3, 6, 1, 4, 2, 5, 8, 20, 10, 11, -1, -3, 12, 100, 23, -23, 9, 32, 7};
int sub_list1[MAX_LEN / 2];
int sub_list2[MAX_LEN / 2];
int final_list[MAX_LEN];

 /* threads */
pthread_t tid1;
pthread_t tid2;
pthread_t tid3;

/* threads will call these methods */
void *runner1(void *param);
void *runner2(void *param);
void *runner3(void *param);

int main(void) {
    int counter = 0;

    /* thread default attrs */
    pthread_attr_t attr1;
    pthread_attr_t attr2;
    pthread_attr_t attr3;

    /* init thread attributes */
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_attr_init(&attr3);

    /* create two sublists from the original */
    while (counter != MAX_LEN) {
        counter++;
        if (counter <= MAX_LEN / 2) {
            sub_list1[counter - 1] = original_list[counter - 1];
        }
        else if (counter > MAX_LEN / 2) {
            sub_list2[counter - (MAX_LEN / 2) - 1] = original_list[counter - 1];
        }
    }

    /* start threads */
    pthread_create(&tid1, &attr1, runner1, NULL);
    pthread_create(&tid2, &attr2, runner2, NULL);
    pthread_create(&tid3, &attr3, runner3, NULL);

    /* join thread 3 and wait for completion */
    pthread_join(tid3, NULL);

    /* parent displays result */
    for (int i = 0; i < MAX_LEN; i++) {
        printf("%d \n", final_list[i]);
    }

    return 0;
}

/* threads run these */
void *runner1(void *param) {
    /* sort sublist1 */
    for (int i = 0; i < MAX_LEN / 2; i++) {
        for (int k = 0; k < (MAX_LEN / 2) - 1; k++) {
            if (sub_list1[k] > sub_list1[k + 1]) {
                int temp = sub_list1[k];
                sub_list1[k] = sub_list1[k + 1];
                sub_list1[k + 1] = temp;
            }
        }
    }
    pthread_exit(0);
}

void *runner2(void *param) {
    /* sort sublist2 */
    for (int i = 0; i < MAX_LEN / 2; i++) {
        for (int k = 0; k < (MAX_LEN / 2) - 1; k++) {
            if (sub_list2[k] > sub_list2[k + 1]) {
                int temp = sub_list2[k];
                sub_list2[k] = sub_list2[k + 1];
                sub_list2[k + 1] = temp;
            }
        }
    }
    pthread_exit(0);
}

void *runner3(void *param) {
    /* the 3rd thread must wait for threads 1 & 2 to complete */
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    /* put both sublists into final list */
    for (int i = 0; i < MAX_LEN; i++) {
        if ((i + 1) <= (MAX_LEN / 2)) {
            final_list[i] = sub_list1[i];
        }
        else if ((i + 1) > (MAX_LEN / 2)) {
            final_list[i] = sub_list2[(i + 1) - (MAX_LEN / 2) - 1];
        }
    }

    for (int i = 0; i < MAX_LEN; i++) {
        for (int k = 0; k < MAX_LEN - 1; k++) {
            if (final_list[k] > final_list[k + 1]) {
                int temp = final_list[k];
                final_list[k] = final_list[k + 1];
                final_list[k + 1] = temp;
            }
        }
    }

    /* sort the final list */
    pthread_exit(0);
}