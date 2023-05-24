#include "shell.h"

#define MAX_ARGUMENTS 100
#define MAX_COMMAND_LENGTH 100

/**
 * prompt - Display the shell prompt
 */
void prompt(void)
{
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "(#cisfun) ", 10);
}

/**
 * read_line - Read a line of input from the user
 * @line: Pointer to the line buffer
 * @len: Pointer to the line buffer length
 * Return: The number of characters read (including the newline character)
 */
ssize_t read_line(char **line, size_t *len)
{
    ssize_t input = getline(line, len, stdin);

    if (input == -1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "\n", 1);
        free(*line);
    }
    return input;
}

/**
 * tokenize_line - Tokenize the input line into arguments
 * @line: The input line
 * Return: An array of pointers to the arguments
 */
char **tokenize_line(char *line)
{
    char **argv = malloc(sizeof(char *) * MAX_ARGUMENTS);
    char *token;
    unsigned int i = 0;

    if (argv == NULL)
        return NULL;

    token = strtok(line, " \n");
    if (!token)
    {
        free(argv);
        return NULL;
    }

    while (token)
    {
        argv[i] = token;
        i++;
        token = strtok(NULL, " \n");
    }
    argv[i] = NULL;

    return argv;
}

/**
 * execute_command - Execute the given command
 * @argv: The command and arguments
 * @env: The environment variables
 */
void execute_command(char **argv, char **env)
{
    struct stat fs;
    char error_msg[MAX_COMMAND_LENGTH + 30];

    if (access(argv[0], F_OK) == 0)
    {
        if (stat(argv[0], &fs) != -1)
        {
            if (S_ISDIR(fs.st_mode))
            {
                sprintf(error_msg, "%s: is a directory\n", argv[0]);
                write(STDERR_FILENO, error_msg, strlen(error_msg));
            }
            else
                shell(argv);
        }
    }
    else
        Path(env, argv);
}

/**
 * shell_loop - Main loop of the shell
 * @env: The environment variables
 */
void shell_loop(char **env)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t input;
    char **argv;

    while (1)
    {
        prompt();

        input = read_line(&line, &len);
        if (input == -1)
            break;

        if (*line == '\n')
            continue;

        argv = tokenize_line(line);
        if (argv == NULL)
            continue;

        if (_strcmp("exit", argv[0]) == 0)
        {
            free(line);
            free(argv);
            break;
        }

        execute_command(argv, env);

        free(argv);
    }

    free(line);
}

/**
 * main - Entry point of the shell program
 * @ac: Number of arguments
 * @av: Array of arguments
 * @env: The environment variables
 *
 * Return: Always 0
 */
int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;

    shell_loop(env);

    return (0);
}

