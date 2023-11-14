#include "shell_func.h"

/**
 * bfree_shell - Frees a pointer and sets the address to NULL.
 * Parameters:
 * @ptr: Address of the pointer to free
 * Return: 1 if freed, otherwise 0.
 */
int bfree_shell(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}


========================================



shell_paser.c



#include "shell_func.h"

/**
 * is_command - Determines if a file is an executable command.
 * Parameters:
 * @infomat: The infomat struct
 * @path: Path to the file
 * Return: 1 if true, 0 otherwise
 */
int is_command(shell_infomat_t *infomat, char *path)
{
	struct stat st;

	(void)infomat;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * *duplicate_characters -  Determines the function
 * Duplicates characters as it continues.
 * Parameters:
 * @pathstr: The PATH string.
 * @start: Starting index.
 * @is_stop: Stopping index.
 * Return: Pointer to new buffer
 */
char *duplicate_charaters(char *pathstr, int start, int is_stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < is_stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - Finds this command in the PATH string.
 * Parameters:
 * @infomat: The infomat struct
 * @pathstr: The PATH string
 * @command: The command to find
 * Return: Full path of command if found, or NULL
 */
char *find_path(shell_infomat_t *infomat, char *pathstr, char *command)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlengths(command) > 2) && starts_with(command, "./"))
	{
		if (is_command(infomat, command))
			return (command);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicate_charaters(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (is_command(infomat, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
