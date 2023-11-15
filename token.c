#include "main.h"

/**
 * split_string - splits a string into words
 * @str: input string to be split
 * @delim: delimeter srting used for spliting
 * Return: a pointer to an array of strings
 *
 */
char **split_string(char *str, char *delim)
{
	int i, x, y, z, numword = 0;
	char **words;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
	{
		if (!check_delim(str[i], delim) &&
			(check_delim(str[i + 1], delim) || !str[i + 1]))
			numword++;
	}
	if (numword == 0)
		return (NULL);

	words = malloc((1 + numword) * sizeof(char *));
	if (!words)
		return (NULL);
	for (i = 0, x = 0; x < numword; x++)
	{
		while (check_delim(str[i], delim))
			i++;
		y = 0;
		while (!check_delim(str[i + y], delim) && str[i + y])
			y++;
		words[x] = malloc((y + 1) * sizeof(char));
		if (!words[x])
		{
			for (y = 0; y < x; y++)
				free(words[y]);
			free(words);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			words[x][z] = str[i++];
		words[x][z] = '\0';
	}
	words[x] = NULL;
	return (words);
}
/**
 * split_string2 - split string into words
 * @str: input string for delim
 * @dd: the delim char
 * Return: a pointer to an array o strings
 */
char **split_string2(char *str, char dd)
{
	int i, x, k, m, numword = 0;
	char **strings;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] != dd && str[i + 1] == dd) ||
			(str[i] != dd && !str[i + 1]) || str[i + 1] == dd)
			numword++;
	}
	if (numword == 0)
		return (NULL);
	strings = malloc((1 + numword) * sizeof(char *));
	if (!strings)
		return (NULL);
	for (i = 0, x = 0; x < numword; x++)
	{
		while (str[i] == dd && str[i])
			i++;
		k = 0;
		while (str[i + k] != dd && str[i + k] && str[i + k] != dd)
			k++;
		strings[x] = malloc((k + 1) * sizeof(char));
		if (!strings[x])
		{
			for (k = 0; k < x; k++)
				free(strings[k]);
			free(strings);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			strings[x][m] = str[i++];
		strings[x][m] = 0;
	}
	strings[x] = NULL;
	return (strings);
}
