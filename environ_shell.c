#include "shell_func.h"

/**
 * owned_env - Prints the current environment.
 * Parameters:
 * @infomat: Structure containing potential arguments.
 *		Used to maintain constant function prototype.
 * Return: Always 0.
 */
int owned_env(shell_infomat_t *infomat)
{
	display_list_str(infomat->env);
	return (0);
}

/**
 * *is_getenv - Gets the value of an environment variable.
 * Parameters:
 * @infomat: Structure containing potential arguments.
 *		Used to maintain constant function prototype.
 *	@name: Environment variable name.
 * Return: The value of the environment variable.
 */
char *is_getenv(shell_infomat_t *infomat, const char *name)
{
	shell_list_t *node = infomat->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * mount_env_shell - Initializes a new environment variable
 *		or modifies an existing one.
 * Parameters:
 * @infomat: Structure containing potential arguments.
 *		Used to maintain constant function prototype.
 * Return: Always 0.
 */
int mount_env_shell(shell_infomat_t *infomat)
{
	if (infomat->argument_count != 3)
	{
		is_eputs("Incorrect number of argument\n");
		return (1);
	}
	if (_mount_env_shell(infomat, infomat->argument_value[1],
						infomat->argument_value[2]))
		return (0);
	return (1);
}

/**
 * unmount_env_shell - Removes an environment variable.
 * Parameters:
 * @infomat: Structure containing potential arguments.
 *		 Used to maintain constant function prototype.
 * Return: Always 0.
 */
int unmount_env_shell(shell_infomat_t *infomat)
{
	int i;

	if (infomat->argument_count == 1)
	{
		is_eputs("Too few argument.\n");
		return (1);
	}
	for (i = 1; i <= infomat->argument_count; i++)
		_unmount_env_shell(infomat, infomat->argument_value[i]);

	return (0);
}

/**
 * increase_env_list - Populates the environment linked list.
 * Parameters:
 * @infomat: Structure containing potential arguments.
 *		Used to maintain constant function prototype.
 * Return: Always 0.
 */
int increase_env_list(shell_infomat_t *infomat)
{
	shell_list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	infomat->env = node;
	return (0);
}
