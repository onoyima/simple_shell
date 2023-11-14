#include "shell_func.h"

/**
 * _strlengths - Returns the length of a string.
 * Parameters:
 * @s: The string whose length is to be checked
 * Return: Integer length of the string
 */
int _strlengths(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - Performs lexicographic comparison of two strings.
 * Parameters:
 * @str1: The first string.
 * @str2: The second string.
 * Return: Negative if str1 < str2, positive if str1 >
 *	str2, zero if str1 == str2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - Checks if 'needle' starts with 'haystack'.
 * Parameters:
 * @haystack: String to search
 * @needle: The substring to find
 * Return: Address of the next character of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Concatenates two strings.
 * Parameters:
 * @is_destination: The destination buffer
 * @src: The source buffer
 * Return: Pointer to the destination buffer
 */
char *_strcat(char *is_destination, char *src)
{
	char *resu = is_destination;

	while (*is_destination)
		is_destination++;
	while (*src)
		*is_destination++ = *src++;
	*is_destination = *src;
	return (resu);
}
