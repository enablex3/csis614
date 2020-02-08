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
	char history_array[20][MAX_LINE]; // 20 is an arbitrary integer for max history levels
	int h = 0;

	while (should_run) {
		printf("the_shell>");
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
		else if (strstr(buffer, "!") != NULL) {
			int history_idx = atoi(&buffer[1]);
			if (history_array[history_idx][0] != '@') {
				strcpy(buffer, history_array[history_idx]);
				printf("Executed command at level %d: %s\n", history_idx, history_array[history_idx]);
			}
			else {
				printf("No command at history level %d\n", history_idx);
			}
		}
		else if (strstr(buffer, "history") != NULL) {
			for (int i = 0; i <= h; i++) {
				printf("%d %s\n", i, history_array[i]);
			}
		}
		else if (strstr(buffer, "exit") != NULL) {
			exit(0);
		}
		else {
			strcpy(buffer_h, buffer);
			// add to history array
			strcpy(history_array[h + 1], buffer);
			h++;
		}
		// split input into args char array
		tok = strtok(buffer, delim);
		k = 0;
		while (tok != NULL) {
			args[k] = tok;
			if (strstr(tok, "&")) {
				bg_run = 1;
				args[k] = NULL;
			}
			else {
				bg_run = 0;
			}
			tok = strtok(NULL, delim);
			k++;
		}
		args[k] = NULL;
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