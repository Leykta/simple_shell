#include "shell.h"

/**
 * stringToken - Splits str with ending chars
 * @line: Pointer that points to array we get from getline.
 * @endStr: It marks sub-str.
 *
 * Return: A pointer to the created token
 */

char *stringToken(char *line, char *endStr)
{
	int tmp2;
	static char *arrayChar;
	char *arrayCharHolder;

	if (line != NULL)
		arrayChar = line;
	for (; *arrayChar != '\0'; arrayChar++)
	{
		for (tmp2 = 0; endStr[tmp2] != '\0'; tmp2++)
		{
			if (*arrayChar == endStr[tmp2])
			break;
		}
		if (endStr[tmp2] == '\0')
			break;
	}
	arrayCharHolder = arrayChar;
	if (*arrayCharHolder == '\0')
		return (NULL);
	for (; *arrayChar != '\0'; arrayChar++)
	{
		for (tmp2 = 0; endStr[tmp2] != '\0'; tmp2++)
		{
			if (*arrayChar == endStr[tmp2])
			{
				*arrayChar = '\0';
				arrayChar++;
				return (arrayCharHolder);
			}
		}
	}
	return (arrayCharHolder);
}
