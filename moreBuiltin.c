#include "shell.h"

/**
 * exitShell - exits the program on status
 * @prog: argument of program data
 *
 * Return: 0 on sucess.
 */

int exitShell(progData *prog)
{
	int tmp1;

	if (prog->tkn[1] != NULL)
	{
		for (tmp1 = 0; prog->tkn[1][tmp1]; tmp1++)
			if ((prog->tkn[1][tmp1] < '0' || prog->tkn[1][tmp1] > '9')
				&& prog->tkn[1][tmp1] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _atoi(prog->tkn[1]);
	}
	freeAlldata(prog);
	exit(errno);
}

/**
 * changeDirectory - change working directory.
 * @prog: argument of program data
 *
 * Return: 0 on sucess.
 */

int changeDirectory(progData *prog)
{
	char *homeDirectory = getKey("HOME", prog), *oldDirectory = NULL;
	char prevDirectory[128] = {0};
	int errMessage = 0;

	if (prog->tkn[1])
	{
		if (stringCompare(prog->tkn[1], "-", 0))
		{
			oldDirectory = getKey("OLDPWD", prog);
			if (oldDirectory)
				errMessage = setWD(prog, oldDirectory);
			printString(getKey("PWD", prog));
			printString("\n");

			return (errMessage);
		}
		else
		{
			return (setWD(prog, prog->tkn[1]));
		}
	}
	else
	{
		if (!homeDirectory)
			homeDirectory = getcwd(prevDirectory, 128);

		return (setWD(prog, homeDirectory));
	}
	return (0);
}

/**
 * setWD - set working directory
 * @prog: argument of program data
 * @dirNew: new path set as a working directory
 *
 * Return: 0 on sucess.
 */

int setWD(progData *prog, char *dirNew)
{
	char prevDirectory[128] = {0};
	int errorMessage = 0;

	getcwd(prevDirectory, 128);

	if (!stringCompare(prevDirectory, dirNew, 0))
	{
		errorMessage = chdir(dirNew);
		if (errorMessage == -1)
		{
			errno = 2;
			return (3);
		}
		setKey("PWD", dirNew, prog);
	}
	setKey("OLDPWD", prevDirectory, prog);
	return (0);
}

/**
 * displayHelp - displays environment where shell executes
 * @prog: argument of program data
 *
 * Return: 0 on success.
 */

int displayHelp(progData *prog)
{
	int tmp1, len = 0;
	char *arr[6] = {NULL};

	arr[0] = HELPMESSAGE;

	if (prog->tkn[1] == NULL)
	{
		printString(arr[0] + 6);
		return (1);
	}
	if (prog->tkn[2] != NULL)
	{
		errno = E2BIG;
		perror(prog->cmdName);
		return (5);
	}
	arr[1] = EXITHELPMESSAGE;
	arr[2] = ENVIROMENTHELPMESSAGE;
	arr[3] = SETENVIROMENTHELPMESSAGE;
	arr[4] = UNSETENVIROMENTHELPMESSAGE;
	arr[5] = CHANGEDIRECTORYHELPMESSAGE;

	for (tmp1 = 0; arr[tmp1]; tmp1++)
	{
		len = getStringLength(prog->tkn[1]);
		if (stringCompare(prog->tkn[1], arr[tmp1], len))
		{
			printString(arr[tmp1] + len + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(prog->cmdName);
	return (0);
}

/**
 * manageAlias - add, pop or display aliases
 * @prog: argument of program data
 *
 * Return: 0 on sucess.
 */

int manageAlias(progData *prog)
{
	int tmp1 = 0;

	if (prog->tkn[1] == NULL)
		return (printAlias(prog, NULL));

	while (prog->tkn[++tmp1])
	{
		if (charCount(prog->tkn[tmp1], "="))
			setAlias(prog->tkn[tmp1], prog);
		else
			printAlias(prog, prog->tkn[tmp1]);
	}

	return (0);
}
