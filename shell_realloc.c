#include "shell_func.h"

/**
 * is_memset - Fills memory with a constant byte.
 * Parameters:
 * @s: Pointer to the memory area
 * @b: The byte to fill *s with
 * @n: The amount of bytes to be filled
 * Return: Pointer to the memory area s
 */
char *is_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * shell_ffree - Frees a string of strings.
 * Parameters:
 * @pp: String of strings
 */
void shell_ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * is__realloc - Reallocates a block of memory.
 * Parameters:
 * @ptr: Pointer to previous malloc'ated block
 * @forma_size: Byte size of previous block
 * @fresh_size: Byte size of new block
 * Return: Pointer to the old block if successful, NULL otherwise.
 */
void *is__realloc(void *ptr, unsigned int forma_size, unsigned int fresh_size)
{
	char *p;

	if (!ptr)
		return (malloc(fresh_size));
	if (!fresh_size)
		return (free(ptr), NULL);
	if (fresh_size == forma_size)
		return (ptr);

	p = malloc(fresh_size);
	if (!p)
		return (NULL);

	forma_size = forma_size < fresh_size ? forma_size : fresh_size;
	while (forma_size--)
		p[forma_size] = ((char *)ptr)[forma_size];
	free(ptr);
	return (p);
}
