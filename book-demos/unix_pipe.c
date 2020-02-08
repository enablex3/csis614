#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define MESSAGE_COUNT 10
#define READ_END 0
#define WRITE_END 1

int main(void) {
	char write_messages[MESSAGE_COUNT][BUFFER_SIZE] = {"Greetings", "My friend", "I am", "The producer", "I am", "The parent process", "You are", "The child process", "I write", "You read!"};
	char read_msg[BUFFER_SIZE];
	char write_msg[BUFFER_SIZE];

	int fd[2];
	pid_t pid;

	for (int k = 0; k < 10; k++) {
		strcpy(write_msg, write_messages[k]);
		// create the pipe
		if (pipe(fd) == -1) {
			fprintf(stderr, "The pipe failed.\n");
			return 1;
		}

		/* the parent process is writing to the pipe
		   while the child process is reading from the pipe */

		// fork a child process
		pid = fork();
		if (pid < 0) {
			fprintf(stderr, "Fork failed.\n");
			return 1;
		}

		if (pid > 0) {
			// close the unused end of the pipe
			close(fd[READ_END]);

			// write to the pipe
			write(fd[WRITE_END], write_msg, strlen(write_msg)+1);

			// close the write end of the pipe
			close(fd[WRITE_END]);
		}
		else {
			// close the unused end of the pipe
			close(fd[WRITE_END]);

			// read from the pipe
			read(fd[READ_END], read_msg, BUFFER_SIZE);
			printf("%s\n", read_msg);

			// close the read end of the pipe
			close(fd[READ_END]);
		}
	}
    return 0;
}