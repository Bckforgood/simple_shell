#include"shell.h"
/**
 * Path - Search for a command in the PATH environment variable and execute it.
 * @env: The environment variables.
 * @argv: The command and its arguments.
 *
 * Return: Always returns 0.
 */
int Path(char **env, char **argv)
{
	unsigned int i, j = 0;
	char *path, *ele, *ch = "/", *str = NULL;
	struct stat st;
	char result[100];

	str = argv[0];
	i = 0;
	while (env[i] != NULL)
	{
		path = _strdup(env[i]);
		if (_strcmp("PATH", strtok(path, "=")) == 0)
			break;
		i++;
	}
	ele = malloc(sizeof(env[i]));
	if (ele == NULL)
		return 0;
	ele =  strtok(NULL, ":");

	while (ele)
	{
		_strcpy(result, ele);
		_strcat(result, ch);
		_strcat(result, str);
		if (stat(result, &st) == 0)
		{	argv[0] = result;
			shell(argv);
			ele = '\0';
			return 0;
		}
		j++;
		ele = strtok(NULL, ":");
	}
	return 0;
}

