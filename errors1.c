#include "main.h"

/**
 * _erroratoi - Converts a string to an integer.
 * @s: The string to be converted.
 * Return: The converted number if successful, or -1 on error.
 */
int _erroratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');

			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
/**
 * print_error - Prints an error message to the standard error.
 * @info: Pointer to the parameter & return info struct.
 * @estr: String containing the specified error type.
 * Return: Returns nothing.
 */
void print_error(info_t *info, char *estr)
{
	my_inputs(info->fname);
	my_inputs(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	my_inputs(": ");
	my_inputs(": ");
	my_inputs(info->argv[0]);
	my_inputs(": ");
	my_inputs(estr);
}
/**
 * print_decimal - Function prints a decimal (integer) number (base 10).
 * @input: The input number to print.
 * @fd: The file descriptor to write to (STDOUT_FILENO or STDERR_FILENO).
 * Return: The number of characters printed.
 */
int print_decimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = my_inputchar;

	if (input < 0)
	{
		_abs_ = -input;
		__putchar ('-');
		count++;
	}
	else
		_abs_ = input;

	current = _abs_;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}
/**
 * convert_num - Converts a number to a string
 * @num: The number to be converted
 * @base: The base for conversion.
 * @flags: Argument flags to control conversion behavior.
 * Return: A string representation of the number in the specified base.
 */
char *convert_num(long int num, int base, int flags)
{
	static char buf[50];
	static char *arr;
	char *p;
	char s = 0;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		s = '-';
	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buf[49];
	*p = '\0';

	do {
		*--p = arr[n % base];
		n /= base;
	} while (n != 0);

	if (s)
		*--p = s;

	return (p);
}
/**
 * rm_comments - Replaces the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 * Return: Always 0.
 */
void rm_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}
