#include "shell.h"

/**
 * longToStr - change num to a str.
 * @number: num that is gonna be changed.
 * @tmpStr: var to save the num as str.
 * @tmpConstant: base to change num
 *
 * Return: Nothing.
 */

void longToStr(long number, char *tmpStr, int tmpConstant)
{
	int tmp = 0, isNeg = 0;
	long conCat = number;
	char alpha[] = {"0123456789abcdef"};

	if (conCat == 0)
		tmpStr[tmp++] = '0';

	if (tmpStr[0] == '-')
		isNeg = 1;

	while (conCat)
	{
		if (conCat < 0)
			tmpStr[tmp++] = alpha[-(conCat % tmpConstant)];
		else
			tmpStr[tmp++] = alpha[conCat % tmpConstant];
		conCat /= tmpConstant;
	}
	if (isNeg)
		tmpStr[tmp++] = '-';

	tmpStr[tmp] = '\0';
	stringReverse(tmpStr);
}


/**
 * _atoi - change a str to int.
 * @tmpStr: pointer to str origin.
 *
 * Return: int of string or 0.
 */

int _atoi(char *tmpStr)
{
	int check = 1;
	unsigned int digit = 0;

	while (!('0' <= *tmpStr && *tmpStr <= '9') && *tmpStr != '\0')
	{
		if (*tmpStr == '-')
			check *= -1;
		if (*tmpStr == '+')
			check *= +1;
		tmpStr++;
	}

	while ('0' <= *tmpStr && *tmpStr <= '9' && *tmpStr != '\0')
	{
		digit = (digit * 10) + (*tmpStr - '0');
		tmpStr++;
	}
	return (digit * check);
}

/**
 * charCount - count num of character in string.
 * @tmpStr: pointer to str origen.
 * @tmpChar: str with chars to be counted
 *
 * Return: int of string or 0.
 */

int charCount(char *tmpStr, char *tmpChar)
{
	int tmp1 = 0, Temp = 0;

	for (; tmpStr[tmp1]; tmp1++)
	{
		if (tmpStr[tmp1] == tmpChar[0])
			Temp++;
	}
	return (Temp);
}

