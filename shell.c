#include "shell.h"
/**
 * shell - executes a cmd in a new pross
 * @argv: command and arguments
 *
 * Return: always return 0
 */
int shell(char **argv)
{
	pit_t pid;
	int stats;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execeve(argv[0], argv, environ);
		perror("Error:");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}
