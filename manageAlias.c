#include "shell.h"

/**
 * printAlias - add, pop or display aliases
 * @prog: argument of program data
 * @strChar: name of the alias gonna be displayed
 *
 * Return: 0 on sucess
 */

int printAlias(progData *prog, char *strChar)
{
	int tmp1, tmp2, lenAlias;
	char arr[250] = {'\0'};

	if (prog->aliasList)
	{
		lenAlias = getStringLength(strChar);
		for (tmp1 = 0; prog->aliasList[tmp1]; tmp1++)
		{
			if (!strChar || (stringCompare(prog->aliasList[tmp1], strChar, lenAlias)
				&&	prog->aliasList[tmp1][lenAlias] == '='))
			{
				for (tmp2 = 0; prog->aliasList[tmp1][tmp2]; tmp2++)
				{
					arr[tmp2] = prog->aliasList[tmp1][tmp2];
					if (prog->aliasList[tmp1][tmp2] == '=')
						break;
				}
				arr[tmp2 + 1] = '\0';
				addBuffer(arr, "'");
				addBuffer(arr, prog->aliasList[tmp1] + tmp2 + 1);
				addBuffer(arr, "'\n");
				printString(arr);
			}
		}
	}

	return (0);
}

/**
 * getAlias - add, pop or display aliases
 * @prog: argument of program data
 * @strChar: name of needed alias.
 *
 * Return: 0 on sucess.
 */

char *getAlias(progData *prog, char *strChar)
{
	int tmp1, lenAlias;

	if (strChar == NULL || prog->aliasList == NULL)
		return (NULL);

	lenAlias = getStringLength(strChar);

	for (tmp1 = 0; prog->aliasList[tmp1]; tmp1++)
	{
		if (stringCompare(strChar, prog->aliasList[tmp1], lenAlias) &&
			prog->aliasList[tmp1][lenAlias] == '=')
		{
			return (prog->aliasList[tmp1] + lenAlias + 1);
		}
	}
	return (NULL);
}

/**
 * setAlias - add, or override alias
 * @strChar: alias gonna be set
 * @prog: argument of program data
 *
 * Return: 0 on sucess.
 */

int setAlias(char *strChar, progData *prog)
{
	int tmp1, tmp2;
	char arr[250] = {'0'}, *temp = NULL;

	if (strChar == NULL ||  prog->aliasList == NULL)
		return (1);

	for (tmp1 = 0; strChar[tmp1]; tmp1++)
		if (strChar[tmp1] != '=')
			arr[tmp1] = strChar[tmp1];
		else
		{
			temp = getAlias(prog, strChar + tmp1 + 1);
			break;
		}

	for (tmp2 = 0; prog->aliasList[tmp2]; tmp2++)
		if (stringCompare(arr, prog->aliasList[tmp2], tmp1) &&
			prog->aliasList[tmp2][tmp1] == '=')
		{
			free(prog->aliasList[tmp2]);
			break;
		}

	if (temp)
	{
		addBuffer(arr, "=");
		addBuffer(arr, temp);
		prog->aliasList[tmp2] = duplicateString(arr);
	}
	else
		prog->aliasList[tmp2] = duplicateString(strChar);
	return (0);
}
