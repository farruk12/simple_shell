#include "main.h"

/**
 * freed - frees a pointer and sets it to NULL
 * @ptr: poniter to address to free
 * Return: 1 if pointer was freed, otherwise 0
 */
int freed(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
