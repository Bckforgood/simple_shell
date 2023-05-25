#include <unistd.h>

/**
 * _puts - write the string c to stdout
 * @c: The string to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _puts(char *c)
{	int i = 0;

	while (c[i])
		i++;

	return (write(1, c, i));
}
