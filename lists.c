#include "main.h"

/**
 * add_node - Adds a node to the start of the list
 * @head: Address of pointer to the start node
 * @str: str of new node
 * @n: Node index
 * Return: pointer to new added node
 */
list_t *add_node(list_t **head, const char *str, int n)
{
	list_t *newHead;

	if (!head)
		return (NULL);
	newHead = malloc(sizeof(list_t));
	if (!newHead)
		return (NULL);
	_memset((void *)newHead, 0, sizeof(list_t));
	newHead->num = n;
	if (str)
	{
		newHead->str = _strdup(str);
		if (!newHead->str)
		{
			free(newHead);
			return (NULL);
		}
	}
	newHead->next = *head;
	*head = newHead;
	return (newHead);
}

/**
 * add_node_end - adds node to end of list
 * @head: address pointer to head
 * @str: str of the new node
 * @n: node index
 * Return: pointer to newly added node
 */
list_t *add_node_end(list_t **head, const char *str, int n)
{
	list_t *newNode, *node;

	if (!head)
		return (NULL);
	node = *head;
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);
	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = n;
	if (str)
	{
		newNode->str = _strdup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newNode;
	}
	else
		*head = newNode;

	return (newNode);
}

/**
 * print_list_str - prints only the str element of linked list
 * @j: pointer to 1st node on list
 * Return: Size of list
 */
size_t print_list_str(const list_t *j)
{
	size_t k = 0;

	while (j)
	{
		_puts(j->str ? j->str : "(nil)");
		_puts("\n");
		j = j->next;
		k++;
	}
	return (k);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: Address of pointer to 1st node
 * @index: index of node to delete
 * Return: 1 success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prevNode;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prevNode->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prevNode = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list -  frees all nodes of linked list
 * @headptr: address of pointer to head
 * Return: void
 */
void free_list(list_t **headptr)
{
	list_t *node, *head, *nextNode;

	if (!headptr || *headptr)
		return;
	head = *headptr;
	node = head;
	while (node)
	{
		nextNode = node->next;
		free(node->str);
		free(node);
		node = nextNode;
	}
	*headptr = NULL;
}
