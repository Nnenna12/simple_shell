#include <stdlib.h>
#include "shell.h"
#include <stddef>

void _realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lnptr(char **lnptr, size_t *n, char *buff, size_t b);
ssize_t _getline(char **lnptr, size_t *n, FILE *stm);
/**
 * _realloc - Allocation of memory
 * @ptr: pointer
 * @old_size: old memo size
 * @new_size: new memo size
 * Return: 0 always
 */
void _realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *memo;
	char *ptr_cpy, *filler;
	unsigned int dex;

	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
	{
		memo = malloc(new_size);
		if (memo == NULL)
			return (NULL);
	}
	ptr_cpy = ptr;
	memo = malloc(sizeof(*ptr_cpy) * new_size);
	if (memo == NULL)
	{
		free(ptr);
		return (NULL);
	}
	filler = memo;

	for (dex = 0; dex < old_size && dex < new_size; dex++)
		filler[dex] = *ptr_cpy++;
	free(ptr);
	return (memo);
}

/**
 * assign_lnptr - function that assign pointer
 * @lnptr: pointer string.
 * @n:  lineptr.
 * @buff: buffer
 * @s: size of buff
 */
void assign_lnptr(char **lnptr, size_t *n, char *buff, size_t s)
{
	if (*lnptr == NULL)
	{
		if (s > 120)
			*n = s;
		else
			*n = 120;
		*lnptr = buff;
	}
	else if (*n < s)
	{
		if (s > 120)
			*n = s;
		else
			*n = 120;
		*lnptr = buff;
	}
	else
	{
		_strcpy(*lnptr, buff);
		free(buff);
	}
}

/**
 * _getline - getline.
 * @lnptr: storage for buff
 * @n: lineptr.
 * @stm: front point
 * Return: The number of bytes read.
 */
ssize_t _getline(char **lnptr, size_t *n, FILE *stm)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buff;
	int r;

	if (input == 0)
		fflush(stm);
	else
		return (-1);
	input = 0;

	buff = malloc(sizeof(char) * 120);
	if (!buff)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buff);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= 120)
			buff = _realloc(buff, input, input + 1);
		buff[input] = c;
		input++;
	}
	buff[input] = '\0';

	assign_lnptr(lnptr, n, buff, input);
	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}
