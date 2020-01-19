#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 80 // Max command length

int main(void) {
	// variables for command parsing
	char *args[MAX_LINE/2 + 1];
	char *tok;
	int k;
	const char* delim = " ";
	char buffer[MAX_LINE];

	// run time variables
	int should_run = 1;
	int bg_run;
	pid_t pid;

	// history
	char buffer_h[MAX_LINE] = "";

	while (should_run) {
		printf("project1>");
		fflush(stdout);
		// get input command line
		fgets(buffer, sizeof(buffer), stdin);
		// remove new line at the end
		buffer[strcspn(buffer, "\n")] = 0;
		// check if user wants to use history feat.
		if (strstr(buffer, "!!") != NULL) {
			if (buffer_h[0] == '\0') {
				printf("No command history!\n");
			}
			else {
			    strcpy(buffer, buffer_h);
			    printf("Executed most recent command: %s\n", buffer);
			}
		}
		else {
			strcpy(buffer_h, buffer);
		}
		// split input into args char array
		tok = strtok(buffer, delim);
		k = 0;
		while (tok != NULL) {
			args[k] = tok;
			if (tok == "&") {
				bg_run = 1;
			}
			else {
				bg_run = 0;
			}
			tok = strtok(NULL, delim);
		}
		pid = fork();
		if (pid == 0) {
			execvp(args[0], args);
			return 0;
		}
		else if (pid > 0) {
			if (bg_run) {
				wait(NULL);
			}
		}
	}
	return 0;
}