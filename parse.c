#include "main.h"

/**
 * is_cmd - Determines if a file is an executable file
 * @info: The info struct
 * @p: Path to the file to be checked
 * Return: 1 if the file is an executable file, 0 otherwise
 */
int is_cmd(info_t *info, char *p)
{
	struct stat st;

	(void)info;

	if (!p || stat(p, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * aduplicate_chars - Duplicates characters from a string.
 * @pathstr: The source string.
 * @start: Starting index from where to copy characters.
 * @stop: Stopping index (exclusive) indicating the end of copying.
 * Return: Pointer to the new buffer containing the duplicated characters.
 */
char *aduplicate_chars(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
	{
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	}
	buf[k] = 0;
	return (buf);
}
/**
 * find_path - Finds the specified command in the PATH string.
 * @info: Pointer to the info struct.
 * @pathstr: The PATH string containing directories separated by ':'.
 * @cmd: The command to find.
 *
 * Return: The full path of the command if found, or NULL if not found.
 */
char *find_paths(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	if ((my_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = aduplicate_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}

	return (NULL);
}
