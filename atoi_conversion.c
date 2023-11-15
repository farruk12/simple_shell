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
	int i, sign = 1, F = 0, value;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && F != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			F = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (F == 1)
			F = 2;
	}

	if (sign == -1)
		value = -result;
	else
		value = result;

	return (value);
}
