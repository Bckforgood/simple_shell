#include "shell.h"
/**
 * _strcpy - Copies a string from source to destination.
 * @d: The destination string.
 * @s: The source string.
 *
 * Return: A pointer to the destination string.
 */
char *_strcpy(char *d, char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
