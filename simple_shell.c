#include "main.h"

#define MAX_COMMAND_SIZE 100

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
    char command[MAX_COMMAND_SIZE];

    while (1)
    {
        pid_t pid;

        printf("#cisfun$ ");
        fgets(command, sizeof(command), stdin);

        /* Remove newline character */
        command[strcspn(command, "\n")] = '\0';

        if (strlen(command) == 0)
        {
            continue; /* Ignore empty commands */
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            /* Child process */
            if (access(command, X_OK) == 0)
            {
                char *argv[2];
                argv[0] = command;
                argv[1] = NULL;

                execve(command, argv, NULL);
                perror("execve");
                exit(EXIT_FAILURE);
            }
            else
            {
                perror("./shell");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* Parent process */
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
