#include "shell_func.h"

/**
 * is_my_own_exit - Exits the shell.
 * Parameters:
 * @infomat: Structure containing potential arguments.
 *	Used to maintain constant function prototype.
 * Return: Exits with status (0) if infomat.argument_value[0] != "exit".
 */
int is_my_own_exit(shell_infomat_t *infomat)
{
	int is_stop_check;

	if (infomat->argument_value[1])  /* If there is an exit argument */
	{
		is_stop_check = is_errorshell_atoi(infomat->argument_value[1]);
		if (is_stop_check == -1)
		{
			infomat->status = 2;
			print_error(infomat, "Illegal number: ");
			is_eputs(infomat->argument_value[1]);
			is_eput_character('\n');
			return (1);
		}
		infomat->error_number = is_errorshell_atoi(infomat->argument_value[1]);
		return (-2);
	}
	infomat->error_number = -1;
	return (-2);
}

/**
 * shell_my_own_cd - Changes the current directory of the process.
 * Parameters:
 * @infomat: Structure containing potential arguments.
 *	Used to maintain constant function prototype.
 * Return: Always 0.
 */

int shell_my_own_cd(shell_infomat_t *infomat)
{
	char *s, *dir, buffer[1024];
	int chdir_resu;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!infomat->argument_value[1])
	{
		dir = is_getenv(infomat, "HOME=");
		if (!dir)
			chdir_resu = /* TODO: what should this be? */
				chdir((dir = is_getenv(infomat, "PWD=")) ? dir : "/");
		else
			chdir_resu = chdir(dir);
	}
	else if (_strcmp(infomat->argument_value[1], "-") == 0)
	{
		if (!is_getenv(infomat, "OLDPWD="))
		{
			_puts(s);
			_putcharacter('\n');
			return (1);
		}
		_puts(is_getenv(infomat, "OLDPWD=")), _putcharacter('\n');
		chdir_resu = /* TODO: what should this be? */
			chdir((dir = is_getenv(infomat, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_resu = chdir(infomat->argument_value[1]);
	if (chdir_resu == -1)
	{
		print_error(infomat, "can't cd to ");
		is_eputs(infomat->argument_value[1]), is_eput_character('\n');
	}
	else
	{
		_mount_env_shell(infomat, "OLDPWD", is_getenv(infomat, "PWD="));
		_mount_env_shell(infomat, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * shell_myhelp - Displays a help message. Function not yet implemented.
 * Parameters:
 * @infomat: Structure containing potential arguments.
 *			Used to maintain constant function prototype.
 * Return: Always 0.
 */
int shell_myhelp(shell_infomat_t *infomat)
{
	char **argument_array;

	argument_array = infomat->argument_value;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argument_array); /* temp att_unused workaround */
	return (0);
}
