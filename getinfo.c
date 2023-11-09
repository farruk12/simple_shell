#include "main.h"

/**
 * clear_information - clear the fields of info_t struct
 * @info: pointer to the info_t struct
 */
void clear_information(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_information - initializes the info_t struct
 * @info: pointer to the info_t struct
 * @av: argument vector
 */
void set_information(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = split_string(info->arg, " \t");

		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}
/**
 * free_information - Frees fields in the info_t struct.
 * @info: Pointer to the info_t struct.
 * @all: True if freeing all fields, false otherwise.
 */
void free_information(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);

		if (info->env)
			free_list(&(info->env));

		if (info->history)
			free_list(&(info->history));

		if (info->alias)
			free_list(&(info->alias));

		ffree(info->environ);
		info->environ = NULL;
		freed((void **)info->cmd_buf);
		if (info->readfd > 2)
		{
			close(info->readfd);
		}
		_putchar(FLUSH);
	}
}
