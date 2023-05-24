#include "shell.h"

/**
 * main - set values for the placeholders
 * @argc: number of values received from the cmd-line
 * @argv: values received from the command line
 * @envr: number of values received from the cmd-line
 *
 * Return: 0 on succes.
 */

int main(int argc, char *argv[], char *envr[])
{
	progData structData = {NULL}, *Temp = &structData;
	char *message = "";

	InitializeData(Temp, argc, argv, envr);

	signal(SIGINT, ctrlHandle);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		message = MESSAGEDISPLAY;
	}
	errno = 0;
	sIsInfo(message, Temp);
	return (0);
}

/**
 * ctrlHandle - Display message in a new line
 * @UNUSED: choice of the prototype
 *
 * Return: Returns nothing
 */

void ctrlHandle(int opr UNUSED)
{
	printString("\n");
	printString(MESSAGEDISPLAY);
}

/**
 * InitializeData - set values for structure fieldsets
 * @prog: argument of program data
 * @argv: List of args pased to the program execution
 * @envr: environ pased to the program execution
 * @argc: num of values received from the cmd-line
 *
 * Return: Returns nothing
 */

void InitializeData(progData *prog, int argc, char *argv[], char **envr)
{
	int tmp1 = 0;

	prog->name = argv[0];
	prog->inputPointer = NULL;
	prog->cmdName = NULL;
	prog->execCount = 0;

	if (argc == 1)
		prog->descFile = STDIN_FILENO;
	else
	{
		prog->descFile = open(argv[1], O_RDONLY);
		if (prog->descFile == -1)
		{
			printError(prog->name);
			printError(": 0: Can't open ");
			printError(argv[1]);
			printError("\n");
			exit(127);
		}
	}
	prog->tkn = NULL;
	prog->envr = malloc(sizeof(char *) * 50);
	if (envr)
	{
		for (; envr[tmp1]; tmp1++)
		{
			prog->envr[tmp1] = duplicateString(envr[tmp1]);
		}
	}
	prog->envr[tmp1] = NULL;
	envr = prog->envr;
	prog->aliasList = malloc(sizeof(char *) * 20);
	for (tmp1 = 0; tmp1 < 20; tmp1++)
	{
		prog->aliasList[tmp1] = NULL;
	}
}

/**
 * sIsInfo - its an iterative process that displays the message
 * @prompt: Message to be printed
 * @prog: argument of program data
 *
 * Return: Returns nothing
 */

void sIsInfo(char *prompt, progData *prog)
{
	int errMSG = 0, strLen = 0;

	while (++(prog->execCount))
	{
		printString(prompt);
		errMSG = strLen = getLine(prog);

		if (errMSG == EOF)
		{
			freeAlldata(prog);
			exit(errno);
		}
		if (strLen >= 1)
		{
			aliasExpand(prog);
			varExpand(prog);
			tokStr(prog);
			if (prog->tkn[0])
			{
				errMSG = runCommand(prog);
				if (errMSG != 0)
					printErrorMessage(errMSG, prog);
			}
			recData(prog);
		}
	}
}

