#include "shell.h"

/**
 * command_exists - Checks if a command exists in the PATH.
 * @command: The command to check.
 *
 * Return: True if the command exists, false otherwise.
 */
bool command_exists(const char *command)
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

        if (access(command_path, F_OK) == 0)
        {
            free(path_copy);
            free(command_path);
            return true;
        }

        free(command_path);
        path_dir = strtok(NULL, ":");
    }

    free(path_copy);
    return false;
}
