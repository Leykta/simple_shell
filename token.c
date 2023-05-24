#include "shell.h"

/**
 * tokStr - It splits single str using a designed ending char
 * @prog: argument of program data
 *
 * Return: Returns nothing
 */

void tokStr(progData *prog)
{
	char *endChar = " \t";
	int tmp1, tmp2, charTotal = 2, num;

	num = getStringLength(prog->inputPointer);
	if (num)
	{
		if (prog->inputPointer[num - 1] == '\n')
			prog->inputPointer[num - 1] = '\0';
	}

	for (tmp1 = 0; prog->inputPointer[tmp1]; tmp1++)
	{
		for (tmp2 = 0; endChar[tmp2]; tmp2++)
		{
			if (prog->inputPointer[tmp1] == endChar[tmp2])
				charTotal++;
		}
	}
	prog->tkn = malloc(charTotal * sizeof(char *));
	if (prog->tkn == NULL)
	{
		perror(prog->name);
		exit(errno);
	}
	tmp1 = 0;
	prog->tkn[tmp1] = duplicateString(stringToken(prog->inputPointer, endChar));
	prog->cmdName = duplicateString(prog->tkn[0]);
	while (prog->tkn[tmp1++])
	{
		prog->tkn[tmp1] = duplicateString(stringToken(NULL, endChar));
	}
}
