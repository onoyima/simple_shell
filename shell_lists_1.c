#include "shell_func.h"

/**
 * list_length - Determines the length of a linked list.
 * Parameters:
 * @h: Pointer to the first node
 * Return: Size of the list
 */
size_t list_length(const shell_list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * shell_list_to_strings - Returns an array of
 * strings from the list's str.
 * Parameters:
 * @head: Pointer to the first node
 * Return: Array of strings
 */
char **shell_list_to_strings(shell_list_t *head)
{
	shell_list_t *node = head;
	size_t i = list_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlengths(node->str) + 1);
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
 * display_list - Prints all elements of a shell_list_t linked list.
 * Parameters:
 * @h: Pointer to the first node
 * Return: Size of the list
 */
size_t display_list(const shell_list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->number, 10, 0));
		_putcharacter(':');
		_putcharacter(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - Returns the node whose string starts with a prefix.
 * Parameters:
 * @node: Pointer to list head
 * @prefix: String to match
 * @c: The next character after prefix to match
 * Return: Matching node or null
 */
shell_list_t *node_starts_with(shell_list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets the index of a node.
 * Parameters:
 * @head: Pointer to list head
 * @node: Pointer to the node
 * Return: Index of node or -1
 */
ssize_t get_node_index(shell_list_t *head, shell_list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
