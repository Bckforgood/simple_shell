#include "shell.h"
/**
 * _strcat - Concatenates two strings.
 * @d: The destination string.
 * @s: The source string.
 *
 * Return: A pointer to the resulting string.
 */
char *_strcat(char *d, char *s)
{
	int i = 0, j = 0;

	while (d[i] != '\0')
	{
		i++;
	}
	while (s[j])
	{
		d[i] = s[j];
		j++;
		i++;
	}
	d[i] = '\0';
	return (d);
}
