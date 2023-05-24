#include "shell.h"

/**
 * check_cmd - Checks and executes a command based on its availability.
 * @argv: The command and its arguments.
 * @env: The environment variables.
 *
 * Return: Always returns 0.
 */
int check_cmd(char **argv, char **env)
{
    /*struct stat fs;*/
    char *command_path = find_command(argv[0]);

    if (_strcmp("env", argv[0]) == 0)
    {
        int i = 0;
        while (env[i] != NULL)
        {
            size_t len = strlen(env[i]);
            write(STDOUT_FILENO, env[i], len);
            write(STDOUT_FILENO, "\n", 1);
            i++;
        }
        return 0;
    }
    if (command_path != NULL)
    {
        argv[0] = command_path;
        shell(argv);
    }
    else
    {
        write(STDOUT_FILENO, "Command not found: ", 19);
        write(STDOUT_FILENO, argv[0], strlen(argv[0]));
        write(STDOUT_FILENO, "\n", 1);
    }

    return 0;

}
/**
 * find_command - Searches for a command in the PATH environment variable.
 * @command: The command to search for.
 * @env: The environment variables.
 *
 * Return: The full path of the command if found, NULL otherwise.
 */
char *find_command(char *command)
{
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *path_dir = strtok(path_copy, ":");

    while (path_dir != NULL)
    {
        char *command_path = malloc(strlen(path_dir) + strlen(command) + 2);
        if (command_path == NULL)
            break;

        sprintf(command_path, "%s/%s", path_dir, command);

        if (access(command_path, X_OK) == 0)
        {
            free(path_copy);
            return command_path;
        }

        free(command_path);
        path_dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}
/**
 * exitShell - Exits the shell program.
 * @argv: The command and its arguments.
 * @line: The input line.
 *
 * Return: Always returns 0.
 */
int exitShell(char *argv[], char *line)
{
    free(line);
    free(argv);
    exit(0);
}
/**
 * main - Entry point of the shell program.
 * @ac: The number of arguments.
 * @av: The array of arguments.
 * @env: The environment variables.
 *
 * Return: Always returns 0.
 */
int main(__attribute__((unused)) int ac, __attribute__((unused)) char **av, char **env)
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
                write(STDOUT_FILENO, "\n", 1);
            free(line);
            break;
        }
        if (*line == '\n')
            continue;
        argv = malloc(sizeof(char) * input * 5);
        if (argv == NULL)
            return 0;
        argv[0] = strtok(line, " \n");
        if (!argv[0])
            continue;
        while (argv[i])
        {
            i++;
            argv[i] = strtok(NULL, " \n");
        }
        if (_strcmp("exit", argv[0]) == 0)
		exitShell(argv, line);
        check_cmd(argv, env);
        free(argv);
        i = 0;
    }
    return 0;
}
