#include "main.h"

/**
 * main - entry point
 * @ac: the number of items in av (command-line arguments count)
 * @av: array of strings (command-line arguments)
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = {INFO_INIT};
	int fd = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(fd)
		: "r"(fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				my_inputs(av[0]);
				my_inputs(": 0: Can't open ");
				my_inputs(av[1]);
				my_inputchar('\n');
				my_inputchar(FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}

	displays_env_list(info);
	read_histo(info);
	vhsh(info, av);
	return (EXIT_SUCCESS);
}
