#include "shell_func.h"

/**
 * shell_hash - Main shell loop.
 * Parameters:
 * @infomat: Pointer to the parameter & return infomat struct
 * @av: The argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int shell_hash(shell_infomat_t *infomat, char **av)
{
	ssize_t r = 0;
	int shell_is_builtin_shell_resu = 0;

	while (r != -1 && shell_is_builtin_shell_resu != -2)
	{
		clear_infomat(infomat);
		if (is_interactive(infomat))
			_puts("$ ");
		is_eput_character(BUF_FLUSH);
		r = resurieve_input(infomat);
		if (r != -1)
		{
			set_infomat(infomat, av);
			shell_is_builtin_shell_resu = find_is_builtin_shell(infomat);
			if (shell_is_builtin_shell_resu == -1)
				find_command(infomat);
		}
		else if (is_interactive(infomat))
			_putcharacter('\n');
		free_infomat(infomat, 0);
	}
	write_history(infomat);
	free_infomat(infomat, 1);
	if (!is_interactive(infomat) && infomat->status)
		exit(infomat->status);
	if (shell_is_builtin_shell_resu == -2)
	{
		if (infomat->error_number == -1)
			exit(infomat->status);
		exit(infomat->error_number);
	}
	return (shell_is_builtin_shell_resu);
}

/**
 * find_is_builtin_shell - Finds a built-in shell command.
 * Parameters:
 * @infomat: Pointer to the parameter & return infomat struct
 * Return: -1 if built-in shell not found,
 *         0 if built-in shell executed successfully,
 *         1 if built-in shell found but not successful,
 *         -2 if built-in shell signals exit()
 */
int find_is_builtin_shell(shell_infomat_t *infomat)
{
	int i, built_in_resu = -1;
	is_builtin_shell_table is_builtin_shelltbl[] = {
		{"exit", is_my_own_exit},
		{"env", owned_env},
		{"help", shell_myhelp},
		{"history", is_history},
		{"mount_env_shell", mount_env_shell},
		{"unmount_env_shell", unmount_env_shell},
		{"cd", shell_my_own_cd},
		{"alias", owned_myalias},
		{NULL, NULL}
	};

	for (i = 0; is_builtin_shelltbl[i].type; i++)
		if (_strcmp(infomat->argument_value[0], is_builtin_shelltbl[i].type) == 0)
		{
			infomat->line_count++;
			built_in_resu = is_builtin_shelltbl[i].func(infomat);
			break;
		}
	return (built_in_resu);
}

/**
 * find_command - Finds a command in PATH.
 * Parameters:
 * @infomat: Pointer to the parameter & return infomat struct
 * Return: Void
 */
void find_command(shell_infomat_t *infomat)
{
	char *path = NULL;
	int i, k;

	infomat->path = infomat->argument_value[0];
	if (infomat->line_count_flag == 1)
	{
		infomat->line_count++;
		infomat->line_count_flag = 0;
	}
	for (i = 0, k = 0; infomat->argument[i]; i++)
		if (!is_delimeter(infomat->argument[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(infomat, is_getenv(infomat, "PATH="),
			infomat->argument_value[0]);
	if (path)
	{
		infomat->path = path;
		fork_command(infomat);
	}
	else
	{
		if ((is_interactive(infomat) || is_getenv(infomat, "PATH=")
			|| infomat->argument_value[0][0] == '/') && is_command(infomat,
				infomat->argument_value[0]))
			fork_command(infomat);
		else if (*(infomat->argument) != '\n')
		{
			infomat->status = 127;
			print_error(infomat, "not found\n");
		}
	}
}

/**
 * fork_command - Forks an exec thread to run a command.
 * Parameters:
 * @infomat: Pointer to the parameter & return infomat struct
 * Return: Void
 */
void fork_command(shell_infomat_t *infomat)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(infomat->path, infomat->argument_value,
					get_environ(infomat)) == -1)
		{
			free_infomat(infomat, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(infomat->status));
		if (WIFEXITED(infomat->status))
		{
			infomat->status = WEXITSTATUS(infomat->status);
			if (infomat->status == 126)
				print_error(infomat, "Permission denied\n");
		}
	}
}
