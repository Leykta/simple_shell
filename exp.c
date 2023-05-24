#include "shell.h"

/**
 * varExpand - Expands variables
 * @prog: argument of program data
 *
 * Return: nothing, but sets errno.
 */

void varExpand(progData *prog)
{
	int tmp1, tmp2;
	char str[MEMORYCAPACITY] = {0}, strExpand[MEMORYCAPACITY] = {'\0'}, *tmp;

	if (prog->inputPointer == NULL)
		return;
	addBuffer(str, prog->inputPointer);
	for (tmp1 = 0; str[tmp1]; tmp1++)
		if (str[tmp1] == '#')
			str[tmp1--] = '\0';
		else if (str[tmp1] == '$' && str[tmp1 + 1] == '?')
		{
			str[tmp1] = '\0';
			longToStr(errno, strExpand, 10);
			addBuffer(str, strExpand);
			addBuffer(str, prog->inputPointer + tmp1 + 2);
		}
		else if (str[tmp1] == '$' && str[tmp1 + 1] == '$')
		{
			str[tmp1] = '\0';
			longToStr(getpid(), strExpand, 10);
			addBuffer(str, strExpand);
			addBuffer(str, prog->inputPointer + tmp1 + 2);
		}
		else if (str[tmp1] == '$' && (str[tmp1 + 1] == ' ' || str[tmp1 + 1] == '\0'))
			continue;
		else if (str[tmp1] == '$')
		{
			for (tmp2 = 1; str[tmp1 + tmp2] && str[tmp1 + tmp2] != ' '; tmp2++)
				strExpand[tmp2 - 1] = str[tmp1 + tmp2];
			tmp = getKey(strExpand, prog);
			str[tmp1] = '\0', strExpand[0] = '\0';
			addBuffer(strExpand, str + tmp1 + tmp2);
			tmp ? addBuffer(str, tmp) : 1;
			addBuffer(str, strExpand);
		}
	if (!stringCompare(prog->inputPointer, str, 0))
	{
		free(prog->inputPointer);
		prog->inputPointer = duplicateString(str);
	}
}

/**
 * aliasExpand - expands aliases
 * @prog: argument of program data
 *
 * Return: nothing, but sets errno.
 */

void aliasExpand(progData *prog)
{
	int tmp1, tmp2, exp = 0;
	char str[MEMORYCAPACITY] = {0}, strExpand[MEMORYCAPACITY] = {'\0'}, *tmp;

	if (prog->inputPointer == NULL)
		return;

	addBuffer(str, prog->inputPointer);

	for (tmp1 = 0; str[tmp1]; tmp1++)
	{
		for (tmp2 = 0; str[tmp1 + tmp2] && str[tmp1 + tmp2] != ' '; tmp2++)
			strExpand[tmp2] = str[tmp1 + tmp2];
		strExpand[tmp2] = '\0';

		tmp = getAlias(prog, strExpand);
		if (tmp)
		{
			strExpand[0] = '\0';
			addBuffer(strExpand, str + tmp1 + tmp2);
			str[tmp1] = '\0';
			addBuffer(str, tmp);
			str[getStringLength(str)] = '\0';
			addBuffer(str, strExpand);
			exp = 1;
		}
		break;
	}
	if (exp)
	{
		free(prog->inputPointer);
		prog->inputPointer = duplicateString(str);
	}
}

/**
 * addBuffer - append string at end of the buffer
 * @buffer: buffer to be filled
 * @addStr: string to be copied in the buffer
 *
 * Return: nothing, but sets errno.
 */

int addBuffer(char *buffer, char *addStr)
{
	int num, tmp1;

	num = getStringLength(buffer);
	for (tmp1 = 0; addStr[tmp1]; tmp1++)
	{
		buffer[num + tmp1] = addStr[tmp1];
	}
	buffer[num + tmp1] = '\0';
	return (num + tmp1);
}

