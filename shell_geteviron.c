#include "shell_func.h"

/**
 * get_environ - Returns a copy of the string array
 * representing our environment.
 * Parameters:
 * @infomat: Structure containing potential arguments
 * (used for function prototype consistency)
 * Return: String array copy of the environment.
 */
char **get_environ(shell_infomat_t *infomat)
{
	if (!infomat->environ || infomat->env_changed)
	{
		infomat->environ = shell_list_to_strings(infomat->env);
		infomat->env_changed = 0;
	}

	return (infomat->environ);
}

/**
 * _unmount_env_shell - Remove an environment variable.
 * Parameters:
 * @infomat: Structure containing potential arguments
 * (used for function prototype consistency).
 * @var: The string environment variable property.
 * Return: 1 if deletion successful, 0 otherwise.
 */
int _unmount_env_shell(shell_infomat_t *infomat, char *var)
{
	shell_list_t *node = infomat->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			infomat->env_changed = remove_node_at_index(&(infomat->env), i);
			i = 0;
			node = infomat->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (infomat->env_changed);
}

/**
 * _mount_env_shell - Initialize a new environment
 * variable or modify an existing one.
 * Parameters:
 * @infomat: Structure containing potential arguments
 * (used for function prototype consistency).
 * @var: The string environment variable property.
 * @value: The string environment variable value.
 * Return: Always 0.
 */
int _mount_env_shell(shell_infomat_t *infomat, char *var, char *value)
{
	char *buf = NULL;
	shell_list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlengths(var) + _strlengths(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = infomat->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			infomat->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(infomat->env), buf, 0);
	free(buf);
	infomat->env_changed = 1;
	return (0);
}
