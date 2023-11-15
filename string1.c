#include "main.h"

/**
 * _strdup - deuplicates a string
 * @s: the string to duplicate
 * Return: pointer to dup string
 */
char *_strdup(const char *s)
{
	int len = 0;
	char *ret;

	if (s == NULL)
		return (NULL);

	while (*s++)
		len++;

	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);

	for (len++; len--;)
		ret[len] = *--s;

	return (ret);
}

/**
 * _puts - my puts function
 * @s: my parameter
 * Return: nothing
 */

void _puts(char *s)
{
	int i = 0;

	if (!s)
		return;

	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
}
/**
 * _putchar - write the character c to the stdout
 * @c: the character to print
 * Return: on sucess 1, else 0
 */
int _putchar(char c)
{
	static char buffer[WRITE_BUFFER_SIZE];
	static  int i;

	if (c == FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != FLUSH)
		buffer[i++] = c;

	return (1);
}
/**
 * _strcpy - copies a string from source to destiantion
 * @d: The destiantion buffer
 * @s: The source buffer
 * Return: pointer to destination buffer
 */
char *_strcpy(char *d, char *s)
{
	int i = 0;

	if (d == s || s == 0)
		return (d);

	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';

	return (d);
}
