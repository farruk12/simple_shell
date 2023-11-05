#include "main.h"

int main(void)
{
	char *buffer = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t child;
	int status;
	char *argv[2];

	printf("#cisfun$ ");
	while ((read = getline(&buffer, &len, stdin)) != -1)
	{
		if (buffer[read - 1] == '\n')
			buffer[read - 1] = '\0';


		child = fork();
		if (child == -1)
		{
			perror("error");
			return (-1);
		}

		if (child == 0)
		{
			argv[0] = buffer;
			argv[1] = NULL;
			execve(argv[0], argv, NULL);
			perror("./shell");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			printf("#cisfun$ ");
		}
	}

	free(buffer);
	return (0);
}
