#include "main.h"
/**
 * _strncpy - Copies a string up to a given length.
 * @dest: The destination string to be copied to.
 * @src: The source string to be copied.
 * @n: The number of characters to be copied.
 * Return: A pointer to the destination string.
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *m = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}

	return (m);
}

/**
 * _strncat - Concatenates two strings
 * @dest: The first string (destination).
 * @src: The second string (source).
 * @n: The maximum number of bytes to be used from src.
 * Return: A pointer to the concatenated string (dest).
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *m = dest;

	i = 0;
	while (dest[i] != '\0')
		i++;

	j = 0;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';

	return (m);
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 * Return: A pointer to the memory area of 's' where 'c' is
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
