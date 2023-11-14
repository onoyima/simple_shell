#include "shell_func.h"

/**
 * is_interactive - Returns true if shell is in interactive mode.
 * Parameters:
 * @infomat: Struct address.
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int is_interactive(shell_infomat_t *infomat)
{
	return (isatty(STDIN_FILENO) && infomat->read_f_d <= 2);
}

/**
 * is_delimeter - Checks if a character is a delimiter.
 * Parameters:
 * @c: The character to check.
 * @delimeter: The delimiter string.
 * Return: 1 if true, 0 if false.
 */
int is_delimeter(char c, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == c)
			return (1);
	return (0);
}

/**
 * is_alphabetic - Checks for an alphabetic character.
 * Parameters:
 * @c: The character to input.
 * Return: 1 if c is alphabetic, 0 otherwise.
 */

int is_alphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * is_shell_atoi - Converts a string to an integer.
 * Parameters:
 * @s: The string to be converted.
 * Return: 0 if no numbers in string,
 * converted number otherwise.
 */

int is_shell_atoi(char *s)
{
	int i, sign = 1, flag = 0, outcome;
	unsigned int resu = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			resu *= 10;
			resu += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		outcome = -resu;
	else
		outcome = resu;

	return (outcome);
}
