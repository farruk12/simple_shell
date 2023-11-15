#include "main.h"

/**
 * n_bfree - frees a pointer 
 * @p: address of the pointer to free
 * Return: 1 if freed success.
 */
int n_bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
