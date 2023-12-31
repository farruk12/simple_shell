#include "main.h"

/**
 * n_eputs - Prints input string to stderr.
 * @str: String
 * Return: void
 */
void n_eputs(char *str)
{
	int j = 0;

	if (!str)
		return;

	while (str[j] != '\0')
	{
		n_putchar(str[j]);
		j++;
	}
}

/**
 * n_eputchar - Writes char to stderr.
 * @v: char to printed
 * Return: 1 on success, error, -1 and errno
 */
int n_eputchar(char v)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;

	if (v == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	if (v != BUF_FLUSH)
	{
		buf[i++] = v;
	}
		return (1);
}

/**
 * n_putfd - Writes char to  file descriptor
 * @v: Character
 * @fd: File descriptor to write to.
 * Return: On success 1, On error, -1 is returned and errno
 */
int n_putfd(char v, int fd)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (v == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(fd, buf, n);
		n = 0;
	}

	if (v != BUF_FLUSH)
	{
		buf[n++] = v;
	}
		return (1);
}

/**
 * n_putsfd - Prints input string to file descriptor.
 * @str: String
 * @fd: File descriptor to write into.
 * Return: no. of characters
 */
int n_putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str)
	{
		i += n_putfd(*str++, fd);
	}

	return (i);
}
