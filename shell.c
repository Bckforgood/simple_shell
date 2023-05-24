#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

/**
 * main - Entry point of the shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t input;
	char *prompt = "#cisfun$ ";
	char **argv;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, strlen(prompt));

		input = getline(&line, &len, stdin);
		if (input == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			break;
		}

		if (input == 1 && line[0] == '\n')
			continue;

		line[input - 1] = '\0'; /* Remove the newline character */

		argv = malloc(sizeof(char *) * 2);
		if (argv == NULL)
		{
			perror("Allocation error");
			exit(EXIT_FAILURE);
		}

		argv[0] = line;
		argv[1] = NULL;

		if (strcmp("exit", argv[0]) == 0)
		{
			free(line);
			free(argv);
			break;
		}

		if (access(argv[0], F_OK) == 0)
		{
			pid_t pid = fork();

			if (pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				execve(argv[0], argv, environ);
				perror("Error");
				exit(EXIT_FAILURE);
			}
			else
			{
				waitpid(pid, NULL, 0);
			}
		}
		else
		{
			printf("%s: command not found\n", argv[0]);
		}

		free(argv);
	}

	return (0);
}

