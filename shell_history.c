#include "shell_func.h"

/**
 * get_history_file - Gets the history file path.
 * Parameters:
 * @infomat: Parameter struct
 * Return: Allocated string containing the history file path
 */

char *get_history_file(shell_infomat_t *infomat)
{
	char *buf, *dir;

	dir = is_getenv(infomat, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlengths(dir) + _strlengths(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - Creates a file or appends to an existing file.
 * Parameters:
 * @infomat: The parameter struct
 * Return: 1 on success, else -1
 */
int write_history(shell_infomat_t *infomat)
{
	ssize_t f_d;
	char *filename = get_history_file(infomat);
	shell_list_t *node = NULL;

	if (!filename)
		return (-1);

	f_d = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (f_d == -1)
		return (-1);
	for (node = infomat->history; node; node = node->next)
	{
		is_putsf_d(node->str, f_d);
		_putf_d('\n', f_d);
	}
	_putf_d(BUF_FLUSH, f_d);
	close(f_d);
	return (1);
}

/**
 * read_history - Reads history from a file.
 * Parameters:
 * @infomat: The parameter struct
 * Return: hist_count on success, 0 otherwise
 */
int read_history(shell_infomat_t *infomat)
{
	int i, last = 0, line_count = 0;
	ssize_t f_d, rdlengths, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(infomat);

	if (!filename)
		return (0);

	f_d = open(filename, O_RDONLY);
	free(filename);
	if (f_d == -1)
		return (0);
	if (!fstat(f_d, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlengths = read(f_d, buf, fsize);
	buf[fsize] = 0;
	if (rdlengths <= 0)
		return (free(buf), 0);
	close(f_d);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(infomat, buf + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(infomat, buf + last, line_count++);
	free(buf);
	infomat->hist_count = line_count;
	while (infomat->hist_count-- >= HIST_MAX)
		remove_node_at_index(&(infomat->history), 0);
	renumber_history(infomat);
	return (infomat->hist_count);
}

/**
 * build_history_list - Adds entry to a history linked list.
 * Parameters:
 * @infomat: Structure containing potential arguments.
 * @buf: Buffer
 * @line_count: The history line_count, hist_count
 * Return: Always 0
 */
int build_history_list(shell_infomat_t *infomat, char *buf, int line_count)
{
	shell_list_t *node = NULL;

	if (infomat->history)
		node = infomat->history;
	add_node_end(&node, buf, line_count);

	if (!infomat->history)
		infomat->history = node;
	return (0);
}

/**
 * renumber_history - Renumbers the history linked list after changes.
 * Parameters:
 * @infomat: Structure containing potential arguments.
 * Return: The new hist_count
 */
int renumber_history(shell_infomat_t *infomat)
{
	shell_list_t *node = infomat->history;
	int i = 0;

	while (node)
	{
		node->number = i++;
		node = node->next;
	}
	return (infomat->hist_count = i);
}
