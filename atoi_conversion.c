#include "main.h"

/**
 * check_interactive_mode - function to change string to integer
 * @info: instance of the structure
 * Return: return 1 if shell is in iteractive mode
 */

int check_interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * check_delim - check if character is delimeter
 * @c: the character to check
 * @delim: delimeter string
 * Return: returns 1 if true and also if false
 */
int check_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 * check_alpha - check for an alphabet in a character
 * @c: The character to be checked
 * Return: returns 1 if true and 0 if false
 */

int check_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * our_atoi - convert an integer string to integer
 * @str: the string to be converted
 * Return: returns 0 if there is no numbers in string
 */
int our_atoi(char *str)
{
	int x, d, n, len, f, digit;

	x = 0;
	d = 0;
	n = 0;
	len = 0;
	f = 0;
	digit = 0;

	while (str[len] != '\0')
		len++;

	while (x < len && f == 0)
	{
		if (str[x] == '-')
			++d;

		if (str[x] >= '0' && str[x] <= '9')
		{
			digit = str[x] - '0';
			if (d % 2)
				digit = -digit;
			n = n * 10 + digit;
			f = 1;
			if (str[x + 1] < '0' || str[x + 1] > '9')
				break;
			f = 0;
		}
		x++;
	}

	if (f == 0)
		return (0);

	return (n);
}
