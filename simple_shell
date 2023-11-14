#include "shell_func.h"

/**
 * is_errorshell_atoi - Converts a string to an integer.
 * Parameters:
 * @s: The string to be converted.
 * Return: 0 if no numbers in string, converted number otherwise,
 * -1 on error.
 */
int is_errorshell_atoi(char *s)
{
	int i = 0;
	unsigned long int resu = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			resu *= 10;
			resu += (s[i] - '0');
			if (resu > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (resu);
}

/**
 * print_error - Prints an error message.
 * Parameters:
 * @infomat: The parameter & return infomat struct.
 * @estr: String containing specified error type.
 * Return: None.
 */
void print_error(shell_infomat_t *infomat, char *estr)
{
	is_eputs(infomat->fname);
	is_eputs(": ");
	print_d(infomat->line_count, STDERR_FILENO);
	is_eputs(": ");
	is_eputs(infomat->argument_value[0]);
	is_eputs(": ");
	is_eputs(estr);
}

/**
 * print_d - Prints a decimal (integer) number (base 10).
 * Parameters:
 * @input: The input.
 * @f_d: The file descriptor to write to.
 * Return: Number of characters printed.
 */
int print_d(int input, int f_d)
{
	int (*__putcharacter)(char) = _putcharacter;
	int i, count = 0;
	unsigned int _abs_, current;

	if (f_d == STDERR_FILENO)
		__putcharacter = is_eput_character;
	if (input < 0)
	{
		_abs_ = -input;
		__putcharacter('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putcharacter('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putcharacter('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - Converter function, a clone of itoa.
 * Parameters:
 * @number: The number.
 * @base: The base.
 * @flags: Argument flags.
 * Return: String.
 */
char *convert_number(long int number, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = number;

	if (!(flags & CONVERT_UNSIGNED) && number < 0)
	{
		n = -number;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * is_remove_comments - Replaces first instance of '#' with '\0'.
 * Parameters:
 * @buf: Address of the string to modify.
 * Return: Always 0.
 */
void is_remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
