#include <stdlib.h>

char *error_12(char **args);
char *error_13(char **args);

/**
 * error_12 - function
 * @args: array of argument
 * Return: error.
 */
char *error_12(char **args)
{
	char *error, *hist_str;
	int wen;

	hist_str = _ito(hist);
	if (!hist_str)
	return (NULL);
	wen = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (wen + 1));
	if (!error)
	{
	free(hist_str);
	return (NULL);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * error_13 -  function
 * @args: array of argument
 * Return: error
 */
char *error_13(char **args)
{
	char *error, *hist_str;
	int wen;

	hist_str = _ito(hist);
	if (!hist_str)
	return (NULL);
	wen = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (wen + 1));
	if (!error)
	{
	free(hist_str);
	return (NULL);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(hist_str);
	return (error);
}
