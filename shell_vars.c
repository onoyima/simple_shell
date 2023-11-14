#include "shell_func.h"

/**
 * is_chain - Checks if the current character in the buffer
 *	is a chaining delimiter.
 * Parameters:
 * @infomat: Pointer to the parameter struct
 * @buf: The character buffer
 * @p: Address of the current position in buf
 * Return: 1 if it's a chaining delimiter, 0 otherwise
 */
int is_chain(shell_infomat_t *infomat, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		infomat->command_buf_type = COMMAND_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		infomat->command_buf_type = COMMAND_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		infomat->command_buf_type = COMMAND_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - Checks if we should continue
 *	chaining based on the last status.
 * Parameters:
 * @infomat: Pointer to the parameter struct
 * @buf: The character buffer
 * @p: Address of the current position in buf
 * @i: Starting position in buf
 * @lengths: Length of buf
 * Return: Void
 */
void check_chain(shell_infomat_t *infomat, char *buf, size_t *p,
	size_t i, size_t lengths)
{
	size_t j = *p;

	if (infomat->command_buf_type == COMMAND_AND)
	{
		if (infomat->status)
		{
			buf[i] = 0;
			j = lengths;
		}
	}
	if (infomat->command_buf_type == COMMAND_OR)
	{
		if (!infomat->status)
		{
			buf[i] = 0;
			j = lengths;
		}
	}

	*p = j;
}

/**
 * replace_alias - Replaces aliases in the tokenized string.
 * Parameters:
 * @infomat: Pointer to the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(shell_infomat_t *infomat)
{
	int i;
	shell_list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(infomat->alias, infomat->argument_value[0], '=');
		if (!node)
			return (0);
		free(infomat->argument_value[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		infomat->argument_value[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Replaces variables in the tokenized string.
 * Parameters:
 * @infomat: Pointer to the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(shell_infomat_t *infomat)
{
	int i = 0;
	shell_list_t *node;

	for (i = 0; infomat->argument_value[i]; i++)
	{
		if (infomat->argument_value[i][0] != '$' || !infomat->argument_value[i][1])
			continue;

		if (!_strcmp(infomat->argument_value[i], "$?"))
		{
			replace_string(&(infomat->argument_value[i]),
				_strdup(convert_number(infomat->status, 10, 0)));
			continue;
		}
		if (!_strcmp(infomat->argument_value[i], "$$"))
		{
			replace_string(&(infomat->argument_value[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(infomat->env, &infomat->argument_value[i][1], '=');
		if (node)
		{
			replace_string(&(infomat->argument_value[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&infomat->argument_value[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Replaces a string.
 * Parameters:
 * @old: Address of the old string
 * @new: New string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
