#include "main.h"

/**
 * _memset - Fills memory with constant byte
 * @buffer: pointer to memory area to be filled
 * @value: byte to fill buffer with
 * @num: number of bytes to filled
 * Return: pointer to memory area
 */

char *_memset(char *buffer, char value, unsigned int num)
{
	unsigned int i;

	if (buffer == NULL || num == 0)
		return (NULL);
	for (i = 0; i < num; i++)
		buffer[i] = value;
	return (buffer);
}

/**
 * ffree - frees string of strings
 * @pp: pointer to string of strings
 * Return: void
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);

	free(a);
}

/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ated block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 * Return: Pointer to the new allocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *po;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
		return (free(ptr), NULL);

	if (new_size == old_size)
		return (ptr);

	po = malloc(new_size);
	if (!po)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		po[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	return (po);
}
