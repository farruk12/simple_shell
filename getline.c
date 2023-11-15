#include "main.h"

/**
 * input_buf - Buffers chained commands for processing.
 * @info: pointer to the parameter struct.
 * @buf: Adress of buffer
 * @len: Address of en variable.
 * Return: The number of bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t read = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;

		signal(SIGINT, sigint_handler);

#if USE_GETLINE
	read = getline(buf, &len_p, stdin);
#else
	read = _getline(info, buf, &len_p);
#endif

		if (read > 0)
		{
			if ((*buf)[read - 1] == '\n')
			{
				(*buf)[read - 1] = '\0';
				read--;
			}
			info->linecount_flag = 1;
			rm_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			if (_strchr(*buf, ';'))
			{
				*len = read;
				info->cmd_buf = buf;
			}
		}
	}
	return (read);
}

/**
 * get_input - gets a line of input without newline character
 * @info: Pointer to the parameter struct
 * Return: Number of bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t read = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(FLUSH);
	read = input_buf(info, &buf, &len);
	if (read == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;
		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (my_strlen(p));
	}
	*buf_p = buf;
	return (read);
}
/**
 * read_buf - Reads a buffer from the input file descriptor.
 * @info: Pointer to the parameter struct
 * @buf: Buffer to store raed data.
 * @i: Pointer to the size of the buffer
 * Return: The number of bytes read from input file descriptor
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;

	return (r);
}

/**
 * _getline - Gets the next line of input from STDIN.
 * @info: Pointer to the parameter struct
 * @ptr: Address of a pointer to buffer, preallocated or NULL
 * @length: Size of preallocated ptr buffer if not NULL
 * Return: The number of characters read from input stream
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, str = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		str = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, str, str ? str + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (str)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	str += k - i;
	i = k;
	p = new_p;
	if (length)
		*length = str;
	*ptr = p;

	return (str);
}
/**
 * sigint_handler - handles the SIGINT signal
 * @sig_num: The signal number
 * Return: void
 */
void sigint_handler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH);
}
