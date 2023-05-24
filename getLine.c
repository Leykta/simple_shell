#include "shell.h"

/**
* getLine - Reads a line from the command prompt.
* @prog: argument of program data
*
* Return: Number of counting bytes.
*/

int getLine(progData *prog)
{
	char tmp[MEMORYCAPACITY] = {'\0'};
	static char *cmdList[10] = {NULL};
	static char oprList[10] = {'\0'};
	ssize_t byteRead, tmp1 = 0;

	if (!cmdList[0] || (oprList[0] == '&' && errno != 0) ||
		(oprList[0] == '|' && errno == 0))
	{
		for (tmp1 = 0; cmdList[tmp1]; tmp1++)
		{
			free(cmdList[tmp1]);
			cmdList[tmp1] = NULL;
		}

		byteRead = read(prog->descFile, &tmp, MEMORYCAPACITY - 1);
		if (byteRead == 0)
			return (-1);

		tmp1 = 0;
		do {
			cmdList[tmp1] = duplicateString(stringToken(tmp1 ? NULL : tmp, "\n;"));
			tmp1 = logicCheck(cmdList, tmp1, oprList);
		} while (cmdList[tmp1++]);
	}

	prog->inputPointer = cmdList[0];
	for (tmp1 = 0; cmdList[tmp1]; tmp1++)
	{
		cmdList[tmp1] = cmdList[tmp1 + 1];
		oprList[tmp1] = oprList[tmp1 + 1];
	}

	return (getStringLength(prog->inputPointer));
}


/**
* logicCheck - Finds and differentiates for AND and OR operators
* @cmdList: List of commands.
* @tmp1: index in the cmdList to be used
* @oprList: array of logical operators for each previous command
*
* Return: index of the last command in the cmdList.
*/

int logicCheck(char *cmdList[], int tmp1, char oprList[])
{
	char *temp = NULL;
	int tmp2;

	for (tmp2 = 0; cmdList[tmp1] != NULL  && cmdList[tmp1][tmp2]; tmp2++)
	{
		if (cmdList[tmp1][tmp2] == '&' && cmdList[tmp1][tmp2 + 1] == '&')
		{
			temp = cmdList[tmp1];
			cmdList[tmp1][tmp2] = '\0';
			cmdList[tmp1] = duplicateString(cmdList[tmp1]);
			cmdList[tmp1 + 1] = duplicateString(temp + tmp2 + 2);
			tmp1++;
			oprList[tmp1] = '&';
			free(temp);
			tmp2 = 0;
		}

		if (cmdList[tmp1][tmp2] == '|' && cmdList[tmp1][tmp2 + 1] == '|')
		{
			temp = cmdList[tmp1];
			cmdList[tmp1][tmp2] = '\0';
			cmdList[tmp1] = duplicateString(cmdList[tmp1]);
			cmdList[tmp1 + 1] = duplicateString(temp + tmp2 + 2);
			tmp1++;
			oprList[tmp1] = '|';
			free(temp);
			tmp2 = 0;
		}
	}
	return (tmp1);
}
