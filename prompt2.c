#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

#define MAX_COMMAND_LENGTH 100

/**
 * prompt - Display the shell prompt
 */
void prompt(void)
{
    write(STDOUT_FILENO, "$ ", 2);
}

/**
 * execute_command - Execute the given command
 * @command: The command to execute
 */
void execute_command(char *command)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        /* Child process */
        if (execlp(command, command, NULL) == -1)
        {
            char error_msg[MAX_COMMAND_LENGTH + 20];
            sprintf(error_msg, "Command '%s' failed\n", command);
            write(STDERR_FILENO, error_msg, strlen(error_msg));
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Parent process */
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0)
            {
                char error_msg[MAX_COMMAND_LENGTH + 30];
                sprintf(error_msg, "Command '%s' failed with exit status %d\n", command, exit_status);
                write(STDERR_FILENO, error_msg, strlen(error_msg));
            }
        }
    }
}

/**
 * signal_handler - Handle the SIGINT signal (Ctrl+C)
 * @signum: The signal number
 */
void signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        write(STDOUT_FILENO, "\n", 1);
        prompt();
    }
}

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0
 */
int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    ssize_t read_status;

    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        prompt();

        read_status = read(STDIN_FILENO, command, sizeof(command));
        if (read_status == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        else if (read_status == 0)
        {
            /* End of file (Ctrl+D) or error */
            break;
        }

        /* Remove the trailing newline character */
        if (command[read_status - 1] == '\n')
        {
            command[read_status - 1] = '\0';
        }

        execute_command(command);
    }

    return 0;
}

