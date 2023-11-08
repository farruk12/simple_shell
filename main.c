#include "main.h"

/**
 * vhsh - main shell loop
 * @info: info info struct
 * @av: argument vector from main function
 * Return: returns 0 on success and 1 on error
 */
int vhsh(info_t *info, char **av)
{
	ssize_t k = 0;
	int builtin_ret =0;
	
	while (k != -1 && builtin_ret != -2)
	{
		clear_information(info);
		if (interactive_mode(info))
			_puts("#cisfun$ ");
		my_inputchar(FLUSH);
		k = get_input(info);
		if (k != -1)
		{
			set_information(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_command(info);
		}
		else if (interactive_mode(info))
			_putchar('\n');
		free_information(info, 0);
	}
	write_histo(info);
	free_information(info, 1);
	if (!interactive_mode(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - function to find a builtin command.
 * @info: info struct.
 * Return: 0 if builtin executed successfully,
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;

	builtin_table builtintbl[] = {
		{"exit", exits_func},
		{"env", my_enviroment},
		{"history", _history},
		{"setenv", mys_setenv},
		{"unsetenv", mys_unsetenv},
		{"cd", cd_func},
		{"alias", _alias},
		{"help", _help},
		{NULL, NULL}};
	for (i = 0; builtintbl[i].type; i++)
		if (my_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}
/**
 * find_comand - finds a ccommand in path
 * @info: info struct
 * Return: returns nothing.
 */
void find_command(info_t *info)
{
	char *path = NULL;
	int i, num_args;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, num_args = 0; info->arg[i]; i++)
	{
		if (!check_delimiter(info->arg[i], " \t\n"))
			num_args++;
	}
	if (!num_args)
		return;
	path = find_paths(info, _getenvs(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((check_interactive_mode(info) || _getenvs(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
		{
			fork_command(info);
		}
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}
/**
 * fork_command - forks an exec thread to run command.
 * @info: info struct.
 * Return: returns nothing.
 */
void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environment(info)) == -1)
		{
			free_information(info, 1);
			if (errno == EACCES)
				exit(126); 
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
			print_error(info, "Permission denied\n");
		}
	}
}
