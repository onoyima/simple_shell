#include "shell_func.h"

/**
 * is_history - Displays the history list, one command per line,
 * preceded with line numbers, starting at 0.
 * Parameters:
 * @infomat: Structure containing potential arguments.
 *	Used to maintain constant function prototype.
 * Return: Always 0.
 */
int is_history(shell_infomat_t *infomat)
{
	display_list(infomat->history);
	return (0);
}

/**
 * empty_alias - The Function Sets an alias to a string.
 * Parameters:
 * @infomat: Parameter struct.
 * @str: The string alias.
 * Return: Always 0 on success, 1 on error.
 */
int empty_alias(shell_infomat_t *infomat, char *str)
{
	char *p, c;
	int resu;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	resu = remove_node_at_index(&(infomat->alias),
		get_node_index(infomat->alias, node_starts_with(infomat->alias, str, -1)));
	*p = c;
	return (resu);
}

/**
 * mount_alias - Sets an alias to a string without much stress.
 * Parameters:
 * @infomat: Parameter struct.
 * @str: The string alias.
 * Return: Always 0 on success, 1 on error.
 */
int mount_alias(shell_infomat_t *infomat, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (empty_alias(infomat, str));

	empty_alias(infomat, str);
	return (add_node_end(&(infomat->alias), str, 0) == NULL);
}

/**
 * display_alias_view - Prints an alias string.
 * Parameters:
 * @node: The alias node.
 * Return: Always 0 on success, 1 on error.
 */
int display_alias_view(shell_list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putcharacter(*a);
		_putcharacter('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * owned_myalias - Mimics the 'alias' shell builtin (man alias).
 * Parameters:
 * @infomat: Structure containing potential arguments.
 *		Used to maintain constant function prototype.
 * Return: Always 0.
 */
int owned_myalias(shell_infomat_t *infomat)
{
	int i = 0;
	char *p = NULL;
	shell_list_t *node = NULL;

	if (infomat->argument_count == 1)
	{
		node = infomat->alias;
		while (node)
		{
			display_alias_view(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; infomat->argument_value[i]; i++)
	{
		p = _strchr(infomat->argument_value[i], '=');
		if (p)
			mount_alias(infomat, infomat->argument_value[i]);
		else
	display_alias_view(node_starts_with(infomat->alias,
				infomat->argument_value[i], '='));
	}

	return (0);
}
