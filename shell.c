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
/**
  * exitShell - fun exit shell with status
  * @argv: args passed in by user
  * @line: line
  * Return: 0 or exit status
  */
int exitShell(char *argv[], char *line)
{
    int exitStatus = 0;
    int i = 0;

    if (argv[1] == NULL || (!_strcmp(argv[1], "0")))
    {
        free(line);
        exit(0);
    }
    else
    {
        while (argv[1][i] != '\0')
        {
            if (argv[1][i] < '0' || argv[1][i] > '9')
            {
                char error_message[50] = "hsh: exit: ";
                strcat(error_message, argv[1]);
                strcat(error_message, ": numeric argument required\n");
                write(STDERR_FILENO, error_message, strlen(error_message));
                free(line);
                exit(2);
            }
            exitStatus = exitStatus * 10 + (argv[1][i] - '0');
            i++;
        }
    }
    return (exitStatus);
}
