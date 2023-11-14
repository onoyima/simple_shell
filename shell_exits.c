#include "shell_func.h"

/**
 * _strncpy - Copies a string.
 * Parameters:
 * @is_destination: The destination string to be copied to.
 * @src: The source string.
 * @n: The number of characters to be copied.
 * Return: The concatenated string.
 */
char *_strncpy(char *is_destination, char *src, int n)
{
	int i, j;
	char *s = is_destination;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		is_destination[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			is_destination[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - Concatenates two strings.
 * Parameters:
 * @is_destination: The first string.
 * @src: The second string.
 * @n: The maximum number of bytes to be used.
 * Return: The concatenated string.
 */
char *_strncat(char *is_destination, char *src, int n)
{
	int i, j;
	char *s = is_destination;

	i = 0;
	j = 0;
	while (is_destination[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		is_destination[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		is_destination[i] = '\0';
	return (s);
}

/**
 * _strchr - Locates a character in a string.
 * Parameters:
 * @s: The string to be parsed.
 * @c: The character to look for.
 * Return: A pointer to the memory area s.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
