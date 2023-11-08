#include "main.h"

/**
 * list_len - Determines the length of a linked list
 * @n: pointer to the first node of the list
 * Return: size of the list
 */
size_t list_len(const list_t *n)
{
	size_t i = 0;

	while (n)
	{
		n = n->next;
		i++;
	}
	return (i);
}
/**
 * list_to_strings - returns an array of strings
 * @h: pointer to the first node of the list
 * Return: array of strings
 */
char **list_to_strings(list_t *h)
{
	list_t *node = h;
	size_t i = list_len(h), j;
	char **strs;
	char *str;

	if (!h || !i)
		return (NULL);

	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(my_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}
/**
 * print_list - prints all elements of a list_t linked list
 * @head: pointer to first node of list
 * Return: size of list
 */
size_t print_list(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(convert_num(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');

		_puts(head->str ? head->str : "(nil)");

		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}
/**
 * node_starts_with - Returns the node whose string starts with the prefix.
 * @n: Pointer to the head of the list.
 * @prefix: String to match as the prefix.
 * @c: The next character after the prefix to match.
 * Return: Pointer to the matching node
 */
list_t *node_starts_with(list_t *n, char *prefix, char c)
{
	char *p = NULL;

	while (n)
	{
		p = starts_with(n->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (n);
		n = n->next;
	}
	return (NULL);
}
/**
 * get_node_index - Gets the index of a node in the linked list.
 * @h: Pointer to the head of the list.
 * @node: Pointer to the node whose index is to be found
 * Return: Index of the node
 */
ssize_t get_node_index(list_t *h, list_t *node)
{
	size_t i = 0;

	while (h)
	{
		if (h == node)
			return (i);
		h = h->next;
		i++;
	}
	return (-1);
}
