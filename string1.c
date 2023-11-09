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
 * start_with - checks if the substring neddle
 * @hay: the string to search
 * @needle: the substring to find
 * Return: address of next char
 */
char *start_with(const char *hay, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *hay++)
			return (NULL);
	}
	return ((char *)hay);
}
/**
 * _puts - prints an input string to stdout
 * @s: The string to be printed
 * Return: nothing
 */
void _puts(char *s)
{
	int i = 0;

	if (!str)
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
