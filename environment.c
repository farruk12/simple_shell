#include "main.h"

/**
 * my_environment - Prints the current environment.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int my_enviroment(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenvs - Gets the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Env var name.
 * Return: The value of the environment variable, or NULL if not found.
 */
char *_getenvs(info_t *info, const char *name)
{
	list_t *node  = info->env;
	char *t;

	while (node)
	{
		t  = starts_with(node->str, name);
		if (t && *t)
			return (t);

		node = node->next;
	}
	return (NULL);
}
/**
 * mys_setenv - Initialize a new environment variable or modify existing one
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int mys_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		my_inputs("Wrong argument amount\n");
		return (1);
	}
	if (_setenviroment(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}
/**
 * mys_unsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * Description: This function removes one or more environment variables.
 * Return: Always 0.
 */
int mys_unsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		my_inputs("Few arguments.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
	{
		_unsetenviroment(info, info->argv[j]);
	}

	return (0);
}

/**
 * displays_env - Populates an environment linked list
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */

int displays_env_list(info_t *info)
{
	list_t *n = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
	{
		add_node_end(&n, environ[i], 0);
	}
	info->env = n;

	return (0);
}
