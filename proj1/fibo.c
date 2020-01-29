#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FIB 3

int *fib_seq;
fib_seq = (int[2]){0, 1};

int main(void) {
	char buff[MAX_FIB];
	printf("How many fibonnaci numbers would you like? ");
	fflush(stdout);
	fgets(buff, sizeof(buff), stdin);
	buff[strcspn(buff, "\n")] = 0;
	int f = atoi(buff);
	printf("You entered: %d\n", f);
}