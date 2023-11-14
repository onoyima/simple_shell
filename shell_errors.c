#include "shell_func.h"

/**
 *is_eputs - Prints an input string.
 * Parameters:
 * @str: The string to be printed.
 * Return: Nothing.
 */
void is_eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		is_eput_character(str[i]);
		i++;
	}
}

/**
 *is_eput_character - Writes the character c to stderr.
 * Parameters:
 * @c: The character to print.
 * Return: On success 1 -1 returned, appropriately.
 */
int is_eput_character(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putf_d - Writes the character c to given f_d.
 * Parameters:
 * @c: The character to print.
 * @f_d: The filedescriptor to write to.
 * Return: On success 1. On error, -1 is returned,
 * and errno is set appropriately.
 */
int _putf_d(char c, int f_d)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(f_d, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *is_putsf_d - Prints an input string.
 * Parameters:
 * @str: The string to be printed.
 * @f_d: The filedescriptor to write to.
 * Return: The number of characters put.
 */
int is_putsf_d(char *str, int f_d)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putf_d(*str++, f_d);
	}
	return (i);
}
