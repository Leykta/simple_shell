#include "shell.h"

/**
 * getStringLength - Gives length of a str.
 * @tmpStr: pointer to the str.
 *
 * Return: length of string, 0 on failure.
 */

int getStringLength(char *tmpStr)
{
	int num = 0;

	if (tmpStr == NULL)
		return (0);

	while (tmpStr[num++] != '\0')
	{
	}
	return (--num);
}

/**
 * duplicateString - Replicates a str
 * @tmpStr: str gonna be Replicated
 *
 * Return: pointer to the array
 */

char *duplicateString(char *tmpStr)
{
	char *ans;
	int num, tmp1;

	if (tmpStr == NULL)
		return (NULL);

	num = getStringLength(tmpStr) + 1;
	ans = malloc(sizeof(char) * num);

	if (ans == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (tmp1 = 0; tmp1 < num ; tmp1++)
	{
		ans[tmp1] = tmpStr[tmp1];
	}
	return (ans);
}

/**
 * stringCompare - differentiate between two str
 * @tmpStr1: first str shorter one
 * @tmpStr2: second str longer one
 * @number: Num of chars to be compared, 0 if infinite
 *
 * Return: 1 if they are equal or 0 if they are different
 */

int stringCompare(char *tmpStr1, char *tmpStr2, int number)
{
	int tmp1;

	if (tmpStr1 == NULL && tmpStr2 == NULL)
		return (1);

	if (tmpStr1 == NULL || tmpStr2 == NULL)
		return (0);

	if (number == 0)
	{
		if (getStringLength(tmpStr1) != getStringLength(tmpStr2))
			return (0);
		for (tmp1 = 0; tmpStr1[tmp1]; tmp1++)
		{
			if (tmpStr1[tmp1] != tmpStr2[tmp1])
				return (0);
		}
		return (1);
	}
	else
	{
		for (tmp1 = 0; tmp1 < number ; tmp1++)
		{
			if (tmpStr1[tmp1] != tmpStr2[tmp1])
			return (0);
		}
		return (1);
	}
}

/**
 * stringConcatenate - Merge str.
 * @tmpStr1: First str
 * @tmpStr2: Second str
 *
 * Return: Merged str
 */

char *stringConcatenate(char *tmpStr1, char *tmpStr2)
{
	char *ans;
	int num1 = 0, num2 = 0;

	if (tmpStr1 == NULL)
		tmpStr1 = "";
	num1 = getStringLength(tmpStr1);

	if (tmpStr2 == NULL)
		tmpStr2 = "";
	num2 = getStringLength(tmpStr2);
	ans = malloc(sizeof(char) * (num1 + num2 + 1));
	if (ans == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (num1 = 0; tmpStr1[num1] != '\0'; num1++)
		ans[num1] = tmpStr1[num1];
	free(tmpStr1);

	for (num2 = 0; tmpStr2[num2] != '\0'; num2++)
	{
		ans[num1] = tmpStr2[num2];
		num1++;
	}

	ans[num1] = '\0';
	return (ans);
}


/**
 * stringReverse - inverts a str
 *
 * @tmpStr: points to str.
 * Return: Returns nothing.
 */

void stringReverse(char *tmpStr)
{

	int tmp1 = 0, num = getStringLength(tmpStr) - 1;
	char Temp;

	while (tmp1 < num)
	{
		Temp = tmpStr[tmp1];
		tmpStr[tmp1++] = tmpStr[num];
		tmpStr[num--] = Temp;
	}
}
