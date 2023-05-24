#include "shell.h"

/**
 * recData - releasing memory
 * @prog: argument of program data
 *
 * Return: returns nothing
 */

void recData(progData *prog)
{
	if (prog->tkn)
		arrayPointer(prog->tkn);
	if (prog->inputPointer)
		free(prog->inputPointer);
	if (prog->cmdName)
		free(prog->cmdName);

	prog->inputPointer = NULL;
	prog->cmdName = NULL;
	prog->tkn = NULL;
}

/**
 * freeAlldata - releasing memory
 * @prog: argument of program data
 *
 * Return: retruns nothing
 */

void freeAlldata(progData *prog)
{
	if (prog->descFile != 0)
	{
		if (close(prog->descFile))
			perror(prog->name);
	}
	recData(prog);
	arrayPointer(prog->envr);
	arrayPointer(prog->aliasList);
}

/**
 * arrayPointer - realeasing memory
 * @list: array of pointers
 *
 * Return: returns nothing
 */

void arrayPointer(char **list)
{
	int tmp1;

	if (list != NULL)
	{
		for (tmp1 = 0; list[tmp1]; tmp1++)
			free(list[tmp1]);

		free(list);
		list = NULL;
	}
}
