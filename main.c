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
    struct stat fs;

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

    if (access(argv[0], F_OK) == 0)
    {
        if (stat(argv[0], &fs) != -1)
        {
            if (S_ISDIR(fs.st_mode))
            {
                write(STDOUT_FILENO, "bash :", 7);
                write(STDOUT_FILENO, argv[0], strlen(argv[0]));
                write(STDOUT_FILENO, " : is a directory\n", 19);
            }
            else
                shell(argv);
        }
    }
    else
        Path(env, argv);
    return 0;
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
        argv = malloc(sizeof(char *) * input * 5);
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
        {
            free(line);
            free(argv);
            break;
        }
        check_cmd(argv, env);
        free(argv);
        i = 0;
    }
    return 0;
}

