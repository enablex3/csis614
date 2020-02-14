#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

#define MAX_LENGTH 100

bool checkFileStatus(char input_file[MAX_LENGTH]) {
    FILE *file;
    if (file = fopen(input_file, "r")) {
        fclose(file);
        return true;
    }
    else {
        return false;
    }
}

int main(void) {
    char input_file[MAX_LENGTH];
    char output_file[MAX_LENGTH];
    char final_string[MAX_LENGTH * 2];
    bool isFileValid;

    printf("Enter a file in the current directory: ");
    fflush(stdout);

    fgets(input_file, sizeof(input_file), stdin);
    input_file[strcspn(input_file, "\n")] = 0;

    // make sure the file exists
    isFileValid = checkFileStatus(input_file);
    if (isFileValid) {
        // get the output file
        printf("\nEnter the file for which to copy %s content to: ", input_file);
        fflush(stdout);
        fgets(output_file, sizeof(output_file), stdin);
        output_file[strcspn(output_file, "\n")] = 0;
        strcpy(final_string, "cp ");
        strcat(final_string, input_file);
        strcat(final_string, " ");
        strcat(final_string, output_file);
        printf("Executing: %s\n", final_string);
        system(final_string);

    }
    else {
        printf("\nThe file does not exist. Try again.\n");
        exit(1);
    }
    return 0;
}