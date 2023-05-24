#include "shell.h"
#include <stdio.h>
/**
 * print_lowercase - function that print alphabet
 * @b: parameter to be printed
 * Return: 1 if successful, 0 otherwise
 */
int print_lowercase(int b)
{
	if ((b >= 97 && b <= 122) || (b >= 65 && b <= 90))
		return (1);
	else
		return (0);
}
