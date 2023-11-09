#include "main.h"
/**
 * my_inputs - Prints an input string to stderr.
 * @str: String to be printed.
 * Return: Nothing.
 */
void my_inputs(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		my_inputchar(str[i]);
		i++;
	}
}
/**
 * my_inputchar - Writes the character c to stderr.
 * @c: The character to print.
 * Return: 1 on success. On error, -1 is returned
 */
int my_inputchar(char c)
{
	static char buf[WRITE_BUFFER_SIZE];
	static int i;

	if (c == FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != FLUSH)
	{
		buf[i++] = c;
	}
	return (1);
}
/**
 * _putfiled - Writes the character c to the given fd.
 * @c: Character to print.
 * @fd: Filedescriptor to write to.
 * Return: On success 1. On error, -1 is returned.
 */
int _putfiled(char c, int fd)
{
	static int n;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == FLUSH || n >= WRITE_BUFFER_SIZE)
	{
		write(fd, buf, n);
		n = 0;
	}
	if (c != FLUSH)
	{
		buf[n++] = c;
	}

	return (1);
}
/**
 * puts_filed - Prints an input string to the specified file descriptor.
 * @str: String to be printed.
 * @fd: Filedescriptor to write into.
 * Return: The number of characters put.
 */
int puts_filed(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str)
	{
		i += _putfiled(*str++, fd);
	}
	return (i);
}
