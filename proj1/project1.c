#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 80 // Max command length

int main(void) {
	// variables for command parsing
	char* args;
	const char* delim = " ";
	char buffer[MAX_LINE];

	// run time variables
	int should_run = 1;

	while (should_run) {
		printf("project1>");
		fflush(stdout);
		// get input command line
		fgets(buffer, sizeof(buffer), stdin);
		// remove new line at the end
		buffer[strcspn(buffer, "\n")] = 0;
		// split input into args char array
		args = strtok(buffer, delim);
		/*while (args != NULL) {
			printf("%s\n", args);
			args = strtok(NULL, delim);
		}*/
	}
	return 0;
}