#include "main.h"

/**
 * _strcat - concatenates two strings
 * @d: destination buffer
 * @src: the source buffer
 * Return: a pointer to the destiantion buffer
 */
char *_strcat(char *d, char *src)
{
	char *r = d;

	while (*d)
		d++;
	while (*src)
		*d++ = *src++;

	*d = '\0';
	return (r);
}
/**
 * my_strlen - returns the length of a string
 * @str: The string whose length to check
 * Return: integer length of the string
 */
int my_strlen(char *str)
{
	int len = 0;

	if (!str)
		return (0);

	while (*str++)
		len++;

	return (len);
}
/**
 * my_strcmp - perform comparison of two strings
 * @s1: The first string to be compared
 * @s2: The second string to be compared
 * Return:if s1 < s2, postive if s1> s2
 */
int my_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);

		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * starts_with - checks if the substring neddle
 * @hay: the string to search
 * @need: the substring to find
 * Return: address of next char
 */
char *starts_with(const char *hay, const char *need)
{
	while (*need)
	{
		if (*need++ != *hay++)
		return (NULL);
	}
	return ((char *)hay);
}
