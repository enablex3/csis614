#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int value = 5;

int main() {
	/*pid_t pid;
	pid = fork();

	if (pid == 0) {
		// child process
		value += 15;
		return 0;
	}
	else if (pid > 0) {
		// parent process
		wait(NULL);
		printf("PARENT: value = %d\n", value);
		return 0;
	}*/

	printf("%d\n", getpid());
	fork();
	// after the first fork, there will be 2 process (parent & child)
	printf("%d\n", getpid());

	fork();
	// fork will be run by parent and child, resulting in 4 processes @ this point
	printf("%d\n", getpid());

	fork();
	// 8 processes
	printf("%d\n", getpid());

	return 0;
}