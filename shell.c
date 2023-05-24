#include "shell.h"
/**
 * shell - Executes a command in a new process.
 * @argv: The command and its arguments.
 *
 * Return: Always returns 0.
 */

int shell(char **argv)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(argv[0], argv, environ);
		perror("Error:");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}
