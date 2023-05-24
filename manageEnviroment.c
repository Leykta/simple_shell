#include "shell.h"

/**
 * getKey - gets key value of environment variable
 * @card: the environment variable
 * @prog: argument of program data
 *
 * Return: a pointer on success, NULL on failure
 */

char *getKey(char *card, progData *prog)
{
	int tmp1, lenOfKey = 0;

	if (card == NULL || prog->envr == NULL)
		return (NULL);

	lenOfKey = getStringLength(card);
	for (tmp1 = 0; prog->envr[tmp1]; tmp1++)
	{
		if (stringCompare(card, prog->envr[tmp1], lenOfKey) &&
		 prog->envr[tmp1][lenOfKey] == '=')
		{
			return (prog->envr[tmp1] + lenOfKey + 1);
		}
	}
	return (NULL);
}

/**
 * setKey - override value of environment variable
 * or create it if does not exist.
 * @card: name of the variable to set
 * @holder: new value
 * @prog: argument of program data
 *
 * Return: 1 on NULL, 2 on an error or 0 on sucess.
 */

int setKey(char *card, char *holder, progData *prog)
{
	int tmp1, lenOfKey = 0, newKey = 1;

	if (card == NULL || holder == NULL || prog->envr == NULL)
		return (1);

	lenOfKey = getStringLength(card);

	for (tmp1 = 0; prog->envr[tmp1]; tmp1++)
	{
		if (stringCompare(card, prog->envr[tmp1], lenOfKey) &&
		 prog->envr[tmp1][lenOfKey] == '=')
		{
			newKey = 0;
			free(prog->envr[tmp1]);
			break;
		}
	}
	prog->envr[tmp1] = stringConcatenate(duplicateString(card), "=");
	prog->envr[tmp1] = stringConcatenate(prog->envr[tmp1], holder);

	if (newKey)
	{
		prog->envr[tmp1 + 1] = NULL;
	}
	return (0);
}

/**
 * removeKey - Remove a key from environment variable
 * @card: key to remove
 * @prog: argument of program data
 *
 * Return: 1 on success, 0 on failure.
 */

int removeKey(char *card, progData *prog)
{
	int tmp1, lenOfKey = 0;

	if (card == NULL || prog->envr == NULL)
		return (0);

	lenOfKey = getStringLength(card);

	for (tmp1 = 0; prog->envr[tmp1]; tmp1++)
	{
		if (stringCompare(card, prog->envr[tmp1], lenOfKey) &&
		 prog->envr[tmp1][lenOfKey] == '=')
		{
			free(prog->envr[tmp1]);

			tmp1++;
			for (; prog->envr[tmp1]; tmp1++)
			{
				prog->envr[tmp1 - 1] = prog->envr[tmp1];
			}
			prog->envr[tmp1 - 1] = NULL;
			return (1);
		}
	}
	return (0);
}

/**
 * printEnv - display working enviroment
 * @prog: argument of program data
 *
 * Return: Returns nothing.
 */

void printEnv(progData *prog)
{
	int tmp2;

	for (tmp2 = 0; prog->envr[tmp2]; tmp2++)
	{
		printString(prog->envr[tmp2]);
		printString("\n");
	}
}

