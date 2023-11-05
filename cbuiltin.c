#include "main.h"
/**
 * exits_func - Exits the shell
 * @info: structure containing potential arguments
 * Return: exits with a given status
 */
int exits_func(info_t *info)
{
	int exits;

	if (info->argv[1])
	{
		exits = _erroratoi(info->argv[1]);
		if (exits == -1)
		{
			info->status = 2;
			printf_error(info, "invalid number: ");
			_inputs(info->argv[1]);
			_inputchar('\n');
			return (1);
		}
		info->err_num = _erroratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * cd_func - change the current directory of the process
 * @info: strucrure containing potential arguments
 * Return: Always 0
 */
int cd_func(info_t *info)
{
	char *t, *dir, buffer[1024];
	int chdir_func;

	t = getcwd(buffer, 1024);
	if (!t)
		_puts("failed\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_func = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_func = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdir_func = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_func = chdir(info->argv[1]);
	if (chdir_func == -1)
	{
		print_error(info, "failed to cd ");
		_inputs(info->argv[1]);
		_inputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * _help - prints a help message for the shell
 * @info: structure containing potential arguments
 * Return: Always 0
 */
int _help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("Help call works\n");
	if (0)
		_puts(*arg_array);

	return (0);
}
