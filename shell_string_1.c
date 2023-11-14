#include "shell_func.h"

/**
 * _strcpy - Copies a string.
 * Parameters:
 * @is_destination: The destination
 * @src: The source
 * Return: Pointer to the destination
 */
char *_strcpy(char *is_destination, char *src)
{
	int i = 0;

	if (is_destination == src || src == 0)
		return (is_destination);
	while (src[i])
	{
		is_destination[i] = src[i];
		i++;
	}
	is_destination[i] = 0;
	return (is_destination);
}

/**
 * _strdup - Duplicates a string.
 * Parameters:
 * @str: The string to duplicate
 * Return: Pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *resu;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	resu = malloc(sizeof(char) * (length + 1));
	if (!resu)
		return (NULL);
	for (length++; length--;)
		resu[length] = *--str;
	return (resu);
}

/**
 * _puts - Prints an input string.
 * Parameters:
 * @str: The string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putcharacter(str[i]);
		i++;
	}
}

/**
 * _putcharacter - Writes the character c to stdout.
 * Parameters:
 * @c: The character to print
 * Return: On success, 1. On error, -1 is returned,
 * and errno is set appropriately.
 */
int _putcharacter(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
