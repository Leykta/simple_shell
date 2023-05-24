#include "shell.h"

/**
 * printString - Displays an array of characters in the standard output display
 * @tmpStr: argument for str
 *
 * Return: Size of bytes returned.
 */

int printString(char *tmpStr)
{
	return (write(STDOUT_FILENO, tmpStr, getStringLength(tmpStr)));
}

/**
 * printError - Displays an array of chararcters in the standard error display
 * @tmpStr: argument for str
 *
 * Return: Size of bytes returned.
 */

int printError(char *tmpStr)
{
	return (write(STDERR_FILENO, tmpStr, getStringLength(tmpStr)));
}

/**
 * printErrorMessage - Displays an error meassage
 * @prog: argument of program data
 * @errMSG: Message to be displayed
 *
 * Return: Size of bytes returned.
 */

int printErrorMessage(int errMSG, progData *prog)
{
	char strTemp[10] = {'\0'};

	longToStr((long) prog->execCount, strTemp, 10);

	if (errMSG == 2 || errMSG == 3)
	{
		printError(prog->name);
		printError(": ");
		printError(strTemp);
		printError(": ");
		printError(prog->tkn[0]);
		if (errMSG == 2)
			printError(": Invalid number: ");
		else
			printError(": can't change directory to ");
		printError(prog->tkn[1]);
		printError("\n");
	}
	else if (errMSG == 127)
	{
		printError(prog->name);
		printError(": ");
		printError(strTemp);
		printError(": ");
		printError(prog->cmdName);
		printError(": not found\n");
	}
	else if (errMSG == 126)
	{
		printError(prog->name);
		printError(": ");
		printError(strTemp);
		printError(": ");
		printError(prog->cmdName);
		printError(": Permission denied\n");
	}
	return (0);
}
