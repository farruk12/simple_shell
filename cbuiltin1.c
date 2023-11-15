#include "main.h"
/**
 * _history - displays the history list, one command per line
 * @info: structure containing potential arguments
 * Return: Always 0
 */
int _history(info_t *info)
{
	print_list(info->history);
	return (0);
}
/**
 * unset_alias - unsets an alias
 * @info: the parameter struct
 * @str: The string rep the alias to unste
 * Return: Always 0 on success
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int r;

	p = _strchr(str, '=');
	if (!p)
	{
		return (1);
	}
	c = *p;
	*p = 0;
	r = delete_node_at_index(&(info->alias),
			get_node_index(info->alias,
				node_starts_with(info->alias, str, -1)));
	*p = c;
	return (r);
}
/**
 * set_alias - set an alias to a string
 * @info: The parameter struct
 * @str: string rep the alias in format "alias_name=alias_value"
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
	{
		return (1);
	}
	if (!*++p)
	{
		return (unset_alias(info, str));
	}
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}
/**
 * print_alias - prints an alias string
 * @node: The alias node containing the alias string
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		{
			_putchar(*a);
		}
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * my_alias - mimics the alias buitlin
 * @info: structure containing potential arguments
 * Return: Always 0
 */
int my_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
		{
			set_alias(info, info->argv[i]);
		}
		else
		{
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
		}
	}
	return (0);
}
