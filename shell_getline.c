#include "shell_func.h"

/**
 * input_buf - Buffers chained commands.
 * Parameters:
 * @infomat: Parameter struct
 * @buf: Address of buffer
 * @lengths: Address of lengths var
 * Return: Bytes read
 */
ssize_t input_buf(shell_infomat_t *infomat, char **buf, size_t *lengths)
{
	ssize_t r = 0;
	size_t lengths_p = 0;

	if (!*lengths) /* if nothing left in the buffer, fill it */
	{
		/*bfree_shell((void **)infomat->command_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &lengths_p, stdin);
#else
		r = _getline(infomat, buf, &lengths_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			infomat->line_count_flag = 1;
			is_remove_comments(*buf);
			build_history_list(infomat, *buf, infomat->hist_count++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*lengths = r;
				infomat->command_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * resurieve_input - Gets a line minus the newline.
 * Parameters:
 * @infomat: Parameter struct
 * Return: Bytes read
 */
ssize_t resurieve_input(shell_infomat_t *infomat)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, lengths;
	ssize_t r = 0;
	char **buf_p = &(infomat->argument), *p;

	_putcharacter(BUF_FLUSH);
	r = input_buf(infomat, &buf, &lengths);
	if (r == -1) /* EOF */
		return (-1);
	if (lengths)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(infomat, buf, &j, i, lengths);
		while (j < lengths) /* iterate to semicolon or end */
		{
			if (is_chain(infomat, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= lengths) /* reached end of buffer? */
		{
			i = lengths = 0; /* reset position and length */
			infomat->command_buf_type = COMMAND_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlengths(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - Reads a buffer.
 * Parameters:
 * @infomat: Parameter struct
 * @buf: Buffer
 * @i: Size
 * Return: r
 */
ssize_t read_buf(shell_infomat_t *infomat, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(infomat->read_f_d, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - Gets the next line of input from STDIN.
 * Parameters:
 * @infomat: Parameter struct
 * @ptr: Address of pointer to buffer, preallocated or NULL
 * @length: Size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _getline(shell_infomat_t *infomat, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, lengths;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == lengths)
		i = lengths = 0;

	r = read_buf(infomat, buf, &lengths);
	if (r == -1 || (r == 0 && lengths == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : lengths;
	new_p = is__realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Blocks ctrl-C.
 * Parameters:
 * @sig_number: The signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_number)
{
	_puts("\n");
	_puts("$ ");
	_putcharacter(BUF_FLUSH);
}
