#include "shell.h"

/**
 * _inputs - Prints an input string to stderr.
 * @str: String to be printed.
 *
 * Return: Nothing.
 */
void _inputs(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_inputchar(str[i]);
		i++;
	}
}

/**
 * _inputchar - Writes the character c to stderr.
 * @c: The character to print.
 *
 * Return: 1 on success. On error, -1 is returned, and errno is set accordingly.
 */
int _inputchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		/*Flush the buffer to stderr when buffer is full or 'BUF_FLUSH' is passed.*/
		write(2, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
	{
		/*Store the character in the buffer if not 'BUF_FLUSH'.*/
		buf[i++] = c;
	}
		return (1);
}

/**
 * _putfd - Writes the character c to the given fd.
 * @c: Character to print.
 * @fd: Filedescriptor to write to.
 *
 * Return: On success 1. On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		/**Flush the buffer to the specified file descriptor when buffer is full or 'BUF_FLUSH' is passed.*/
		write(fd, buf, n);
		n = 0;
	}

	if (c != BUF_FLUSH)
	{
		/**Store the character in the buffer if not 'BUF_FLUSH'.*/
		buf[n++] = c;
	}
}

/**
 * _putsfd - Prints an input string to the specified file descriptor.
 * @str: String to be printed.
 * @fd: Filedescriptor to write into.
 *
 * Return: The number of characters put.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str)
	{
		/**Call _putfd to print each character and increment the count 'i'.*/
		i += _putfd(*str++, fd);
	}

	return (i);
}
