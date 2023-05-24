#include "shell.h"

/**
 * searchPrg - Search a command in directory
 * @prog: argument of program data
 *
 * Return: 0 if success, errcode on failure
 */

int searchPrg(progData *prog)
{
	int tmp1 = 0, messageRet = 0;
	char **dirs;

	if (!prog->cmdName)
		return (2);

	if (prog->cmdName[0] == '/' || prog->cmdName[0] == '.')
		return (check_file(prog->cmdName));

	free(prog->tkn[0]);
	prog->tkn[0] = stringConcatenate(duplicateString("/"), prog->cmdName);
	if (!prog->tkn[0])
		return (2);

	dirs = splitPath(prog);

	if (!dirs || !dirs[0])
	{
		errno = 127;
		return (127);
	}
	for (tmp1 = 0; dirs[tmp1]; tmp1++)
	{
		dirs[tmp1] = stringConcatenate(dirs[tmp1], prog->tkn[0]);
		messageRet = check_file(dirs[tmp1]);
		if (messageRet == 0 || messageRet == 126)
		{
			errno = 0;
			free(prog->tkn[0]);
			prog->tkn[0] = duplicateString(dirs[tmp1]);
			arrayPointer(dirs);
			return (messageRet);
		}
	}
	free(prog->tkn[0]);
	prog->tkn[0] = NULL;
	arrayPointer(dirs);
	return (messageRet);
}

/**
 * splitPath - split the path in directories
 * @prog: argument of program data
 *
 * Return: array of path directories
 */

char **splitPath(progData *prog)
{
	int tmp1 = 0;
	int dirCount = 2;
	char **tkn = NULL;
	char *PATH;

	PATH = getKey("PATH", prog);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = duplicateString(PATH);

	for (tmp1 = 0; PATH[tmp1]; tmp1++)
	{
		if (PATH[tmp1] == ':')
			dirCount++;
	}

	tkn = malloc(sizeof(char *) * dirCount);
	tmp1 = 0;
	tkn[tmp1] = duplicateString(stringToken(PATH, ":"));
	while (tkn[tmp1++])
	{
		tkn[tmp1] = duplicateString(stringToken(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tkn);

}

/**
 * check_file - Search if a file exist or if it is a directory and
 * checks for excecution permision.
 * @fullPath: pointer to the full file name
 *
 * Return: 0 on success, or error code if it exists.
 */

int check_file(char *fullPath)
{
	struct stat someFile;

	if (stat(fullPath, &someFile) != -1)
	{
		if (S_ISDIR(someFile.st_mode) ||  access(fullPath, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
