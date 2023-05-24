#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_SIZE 100

int main(void) {
    char command[MAX_COMMAND_SIZE];

    while (1) {
        printf("#cisfun$ ");
        fgets(command, sizeof(command), stdin);

        // Remove newline character
        command[strcspn(command, "\n")] = '\0';

        if (strlen(command) == 0) {
            continue; // Ignore empty commands
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (access(command, X_OK) == 0) {
                execve(command, NULL, NULL);
                perror("execve");
            } else {
                printf("%s: command not found\n", command);
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
