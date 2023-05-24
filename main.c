#include "shell.h"
/**
 * check_cmd - checks and executes commands
 * @argv: command and argument
 * @env: the environment of variables
 *
 * Return: always 0
 */
int check_cmd(char **argv, char **env)
{
	struct stat fs;

	if (access(argv[0], F_OK) == 0)
	{
		if (stat(argv[0], &fs) != -1)
		{
			if (fs.st_mode == 16877)
			{
				write(1, "bash :", 7);
				write(1, argv[0], (sizeof(argv[0])));
				write(1, " : is a directory\n", 19);
			}
			else
				shell(argv);
		}
	}
	else
		Path(env, argv);
	return (0);
}
/**
 * main - entry point of the shell
 * @ac: number of arguments
 * @av: array of arguments
 * @env: the environment of variables
 *
 * Return: always 0
 */
int mainw(__attribute__((unused)) int ac,
		__attribute__((unused)) char **av, char **env)
{
	char *line = NULL;
	ssize_t input;
	size_t len = 0;
	char **argv;
	unsigned int i = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 5);
		input = getline(&line, &len, stdin);
		if (input == -1)
		{
			if (isatty(STDIN_FILENO))
				write(1, "\n", 1);
			free(line);
			break;
		}
		if (*line == '\n')
			continue;
		argv = malloc(sizeof(char) * input * 5);
		if (argv == NULL)
			return (0);
		argv[0] = strtok(line, " \n");
		if (!argv[0])
			continue;
		while (argv[i])
		{	i++;
			argv[i] = strtok(NULL, " \n");
		}
		if (_strcmp("exit", argv[0]) == 0)
		{	free(line);
			free(argv);
			break;
		}
		check_cmd(argv, env);
		free(argv);
		i = 0;
	}
	return (0);
}
