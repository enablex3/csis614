#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

struct Philosopher {
    int id;
    int alt_time;
    int is_running;
    int is_thinking;
};

/* init mutex */
pthread_mutex_t mutex;
pthread_cond_t cond_var;

/* condition */
int dinnerIsOver = 0;

void *runner(void *ph);

void pickup_forks(int ph_id) {
    /* the philosopher is eating */
    if (dinnerIsOver == 1) {
        printf("Philosopher %d finished dinner eating.\n", ph_id);
    }
}

void return_forks(int ph_id) {
    /* the philosopher is thinking */
    if (dinnerIsOver == 1) {
        printf("Philosopher %d finished dinner thinking.\n", ph_id);
    }
}

int main(void) {

    /* set mutex and conditional var */
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_var, NULL);

    /* init threads */
    pthread_t tid0;
    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;
    pthread_t tid4;

    /* thread default attrs */
    pthread_attr_t attrs;

    /* init philosophers */
    struct Philosopher ph0;
    struct Philosopher ph1;
    struct Philosopher ph2;
    struct Philosopher ph3;
    struct Philosopher ph4;

    /* init pointers */
    struct Philosopher *ph0addr;
    struct Philosopher *ph1addr;
    struct Philosopher *ph2addr;
    struct Philosopher *ph3addr;
    struct Philosopher *ph4addr;

    /* assign IDs to philosophers */
    ph0.id = 0;
    ph1.id = 1;
    ph2.id = 2;
    ph3.id = 3;
    ph4.id = 4;

    /* choose random alternating time */
    ph0.alt_time = 1;
    ph1.alt_time = 2;
    ph2.alt_time = 2;
    ph3.alt_time = 3;
    ph4.alt_time = 1;

    /* assign pointers */
    ph0addr = &ph0;
    ph1addr = &ph1;
    ph2addr = &ph2;
    ph3addr = &ph3;
    ph4addr = &ph4;

    /* set running state */
    ph0.is_running = 1;
    ph1.is_running = 1;
    ph2.is_running = 1;
    ph3.is_running = 1;
    ph4.is_running = 1;

    /* start threads */
    pthread_attr_init(&attrs);
    pthread_create(&tid0, &attrs, runner, ph0addr);

    pthread_attr_init(&attrs);
    pthread_create(&tid1, &attrs, runner, ph1addr);

    pthread_attr_init(&attrs);
    pthread_create(&tid2, &attrs, runner, ph2addr);

    pthread_attr_init(&attrs);
    pthread_create(&tid3, &attrs, runner, ph3addr);

    pthread_attr_init(&attrs);
    pthread_create(&tid4, &attrs, runner, ph4addr);

    /* enter 1 when to finish dinner */
    char buffer[2];

    printf("The philosophers are having dinner. Enter 1 to abruptly end dinner: ");

    fflush(stdout);
    fgets(buffer, sizeof(buffer), stdin);
    
    dinnerIsOver = atoi(buffer);

    /* let threads run */
    pthread_exit(NULL);
}

void *runner(void *pointer) {
    struct Philosopher *ph = pointer;
    while (ph->is_running) {
        if (ph->is_thinking) {
            pickup_forks(ph->id);
            ph->is_thinking = 0;
        }
        else {
            return_forks(ph->id);
            ph->is_thinking = 1;
        }
        pthread_mutex_lock(&mutex);
        if (dinnerIsOver != 1) {
            pthread_cond_wait(&mutex, &cond_var);
        }
        else {
            pthread_cond_signal(&cond_var);
            break;
        }
        pthread_mutex_unlock(&mutex);
        sleep(ph->alt_time);
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}