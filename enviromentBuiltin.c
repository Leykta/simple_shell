#include "shell.h"

/**
 * displayEnviroment - displays environment where the shell executes
 * @prog: argument of program data
 *
 * Return: 0 on sucess.
 */

int displayEnviroment(progData *prog)
{
	int tmp1;
	char copy[50] = {'\0'};
	char *cpVar = NULL;

	if (prog->tkn[1] == NULL)
		printEnv(prog);
	else
	{
		for (tmp1 = 0; prog->tkn[1][tmp1]; tmp1++)
		{
			if (prog->tkn[1][tmp1] == '=')
			{
				cpVar = duplicateString(getKey(copy, prog));
				if (cpVar != NULL)
					setKey(copy, prog->tkn[1] + tmp1 + 1, prog);

				printEnv(prog);
				if (getKey(copy, prog) == NULL)
				{
					printString(prog->tkn[1]);
					printString("\n");
				}
				else
				{
					setKey(copy, cpVar, prog);
					free(cpVar);
				}
				return (0);
			}
			copy[tmp1] = prog->tkn[1][tmp1];
		}
		errno = 2;
		perror(prog->cmdName);
		errno = 127;
	}
	return (0);
}

/**
 * unsetEnviromentVariable - unsets enviroment variable.
 * @prog: argument of program data
 *
 * Return: 0 on success.
 */

int unsetEnviromentVariable(progData *prog)
{
	if (prog->tkn[1] == NULL)
		return (0);
	if (prog->tkn[2] != NULL)
	{
		errno = E2BIG;
		perror(prog->cmdName);
		return (5);
	}
	removeKey(prog->tkn[1], prog);
	return (0);
}

/**
 * setEnviromentVariable - sets enviroment variable.
 * @prog: argument of program data
 *
 * Return: 0 on sucess.
 */

int setEnviromentVariable(progData *prog)
{
	if (prog->tkn[1] == NULL || prog->tkn[2] == NULL)
		return (0);
	if (prog->tkn[3] != NULL)
	{
		errno = E2BIG;
		perror(prog->cmdName);
		return (5);
	}
	setKey(prog->tkn[1], prog->tkn[2], prog);
	return (0);
}

