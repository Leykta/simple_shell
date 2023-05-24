#include "shell.h"

/**
 * executeBuiltin - search for a matching builtin then executing it.
 * @prog: argument of program data
 *
 * Return: value on success, -1 on failure.
 */

int executeBuiltin(progData *prog)
{
	int tmp;
	builtins choice[] = {
		{"exit", exitShell},
		{"help", displayHelp},
		{"cd", changeDirectory},
		{"alias", manageAlias},
		{"env", displayEnviroment},
		{"setenv", setEnviromentVariable},
		{"unsetenv", unsetEnviromentVariable},
		{NULL, NULL}
	};

	for (tmp = 0; choice[tmp].builtin != NULL; tmp++)
	{
		if (stringCompare(choice[tmp].builtin, prog->cmdName, 0))
		{
			return (choice[tmp].function(prog));
		}
	}
	return (-1);
}
