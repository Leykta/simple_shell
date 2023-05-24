#include "shell.h"

/**
 * runCommand - Runs a command with its entire path variables.
 * @prog: argument of program data
 *
 * Return: 0 on success,-1 on failure.
 */

int runCommand(progData *prog)
{
	int valueRet = 0, cmdStat;
	pid_t place;

	valueRet = executeBuiltin(prog);
	if (valueRet != -1)
		return (valueRet);

	valueRet = searchPrg(prog);
	if (valueRet)
	{
		return (valueRet);
	}
	else
	{
		place = fork();
		if (place == -1)
		{
			perror(prog->cmdName);
			exit(EXIT_FAILURE);
		}
		if (place == 0)
		{
			valueRet = execve(prog->tkn[0], prog->tkn, prog->envr);
			if (valueRet == -1)
				perror(prog->cmdName), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&cmdStat);
			if (WIFEXITED(cmdStat))
				errno = WEXITSTATUS(cmdStat);
			else if (WIFSIGNALED(cmdStat))
				errno = 128 + WTERMSIG(cmdStat);
		}
	}
	return (0);
}
