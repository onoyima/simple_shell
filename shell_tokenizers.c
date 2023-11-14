#include "shell_func.h"

/**
 * strtow - Splits a string into words. Repeated delimiters are ignored.
 * Parameters:
 * @str: The input string
 * @d: The delimiter string
 * Return: A pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int i, j, k, m, number_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimeter(str[i], d) && (is_delimeter(str[i + 1], d) || !str[i + 1]))
			number_words++;

	if (number_words == 0)
		return (NULL);
	s = malloc((1 + number_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < number_words; j++)
	{
		while (is_delimeter(str[i], d))
			i++;
		k = 0;
		while (!is_delimeter(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * str_to_word2 - Splits a string into words
 * Parameters:
 * @str: The input string
 * @d: The delimiter character
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **str_to_word2(char *str, char d)
{
	int i, j, k, m, number_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			number_words++;
	if (number_words == 0)
		return (NULL);
	s = malloc((1 + number_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < number_words; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
