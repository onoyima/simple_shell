#include "shell_func.h"

/**
 * clear_infomat - Initializes shell_infomat_t struct.
 * Parameters:
 * @infomat: Struct address
 */
void clear_infomat(shell_infomat_t *infomat)
{
	infomat->argument = NULL;
	infomat->argument_value = NULL;
	infomat->path = NULL;
	infomat->argument_count = 0;
}

/**
 * set_infomat - Initializes shell_infomat_t struct.
 * Parameters:
 * @infomat: Struct address
 * @av: Argument vector
 */
void set_infomat(shell_infomat_t *infomat, char **av)
{
	int i = 0;

	infomat->fname = av[0];
	if (infomat->argument)
	{
		infomat->argument_value = strtow(infomat->argument, " \t");
		if (!infomat->argument_value)
		{

			infomat->argument_value = malloc(sizeof(char *) * 2);
			if (infomat->argument_value)
			{
				infomat->argument_value[0] = _strdup(infomat->argument);
				infomat->argument_value[1] = NULL;
			}
		}
		for (i = 0; infomat->argument_value && infomat->argument_value[i]; i++)
			;
		infomat->argument_count = i;

		replace_alias(infomat);
		replace_vars(infomat);
	}
}

/**
 * free_infomat - Frees shell_infomat_t struct fields.
 * Parameters:
 * @infomat: Struct address
 *  @all: True if freeing all fields
 */
void free_infomat(shell_infomat_t *infomat, int all)
{
	shell_ffree(infomat->argument_value);
	infomat->argument_value = NULL;
	infomat->path = NULL;
	if (all)
	{
		if (!infomat->command_buf)
			free(infomat->argument);
		if (infomat->env)
			free_list(&(infomat->env));
		if (infomat->history)
			free_list(&(infomat->history));
		if (infomat->alias)
			free_list(&(infomat->alias));
		shell_ffree(infomat->environ);
			infomat->environ = NULL;
		bfree_shell((void **)infomat->command_buf);
		if (infomat->read_f_d > 2)
			close(infomat->read_f_d);
		_putcharacter(BUF_FLUSH);
	}
}
