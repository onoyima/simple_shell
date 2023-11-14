#include "shell_func.h"

/**
 * add_node - Adds a node to the start of the list.
 * Parameters:
 * @head: Address of pointer to head node
 * @str: str field of the node
 * @number: Node index used by history
 * Return: Pointer to the new head of the list
 */
shell_list_t *add_node(shell_list_t **head, const char *str, int number)
{
	shell_list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(shell_list_t));
	if (!new_head)
		return (NULL);
	is_memset((void *)new_head, 0, sizeof(shell_list_t));
	new_head->number = number;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - Adds a node to the end of the list.
 * Parameters:
 * @head: Address of pointer to head node
 * @str: str field of the node
 * @number: Node index used by history
 * Return: Pointer to the new node
 */
shell_list_t *add_node_end(shell_list_t **head, const char *str, int number)
{
	shell_list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(shell_list_t));
	if (!new_node)
		return (NULL);
	is_memset((void *)new_node, 0, sizeof(shell_list_t));
	new_node->number = number;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * display_list_str - Prints only the str element
 * of a shell_list_t linked list.
 * Parameters:
 * @h: Pointer to the first node
 * Return: Size of the list
 */
size_t display_list_str(const shell_list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * remove_node_at_index - Deletes a node at the given index.
 * Parameters:
 * @head: Address of pointer to first node
 * @index: Index of the node to delete
 * Return: 1 on success, 0 on failure
 */
int remove_node_at_index(shell_list_t **head, unsigned int index)
{
	shell_list_t *node, *prev_node;
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
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - Frees all nodes of a list.
 * Parameters:
 * @head_ptr: Address of pointer to head node
 * Return: void
 */
void free_list(shell_list_t **head_ptr)
{
	shell_list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
