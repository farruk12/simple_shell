#include "main.h"

/**
 * _history_file - Gets the history file path.
 * @info: Pointer to the parameter struct.
 * Return: Returns the allocated string containing the h
 */
char *_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenvs(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (my_strlen(dir) + my_strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	_strcpy(buf, dir);
	_strcat(buf, dir);
	_strcat(buf, HIST_FILE);

	return (buf);
}
/**
 * write_histo - creates a file
 * @info: pointer to the parameter struct
 * Return: 1 on success, else -1 on failure
 */
int write_histo(info_t *info)
{
	ssize_t fd;
	char *filename = _history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		puts_filed(node->str, fd);
		_putfiled('\n', fd);
	}
	_putfiled(FLUSH, fd);
	close(fd);

	return (1);
}
/**
 * read_histo - reads history from a file and builds a histroy ist
 * @info: pointer to parameter struct
 * Return: The number of history lines read
 */
int read_histo(info_t *info)
{
	int j, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = _history_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (j = 0; j < fsize; j++)
	{
		if (buf[j] == '\n')
		{
			buf[j] = 0;
			build_history_list(info, buf + last, linecount++);
			last = j + 1;
		}
	}
	if (last != j)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_histo(info);
	return (info->histcount);
}
/**
 * build_history_list - Adds an entry to a history linked list.
 * @info: Structure containing potential arguments used to maintain history
 * @buf: The buffer containing the history command to add.
 * @linecount: The history linecount, histcount.
 * Return: Always 0.
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	add_node_end(&node, buf, linecount);
	if (!info->history)
		info->history = node;

	return (0);
}
/**
 * renumber_histo - renumbers the histo linked list
 * @info: structure containing potential arguments;
 * Return: the new histcount
 */
int renumber_histo(info_t *info)
{
	list_t *node = info->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (info->histcount = j);
}
