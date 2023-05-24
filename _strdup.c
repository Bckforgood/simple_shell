#include "shell.h"
/**
 * _strdup - Duplicates a string.
 * @s: The string to duplicate.
 *
 * Return: Pointer to the newly allocated duplicate string.
 */
char *_strdup(char *s)
{
	int i = 0;
	char *p;

	while (s[i])
	{
		i++;
	}
	i++;
	p = malloc(sizeof(char) * i);
	if (!p)
	{
		free(p);
		return (NULL);
	}
	_memcpy(p, s, i);
	return (p);
}
/**
 * _memcpy - Copies memory area from source to destination.
 * @d: Pointer to the destination memory area.
 * @s: Pointer to the source memory area.
 * @n: Number of bytes to copy.
 *
 * Return: Pointer to the destination memory area.
 */
char *_memcpy(char *d, char *s, unsigned int n)
{
	int i = 0;
	int j = n;

	for (; i < j; i++)
	{
		d[i] = s[i];
	}
	return (d);
}
