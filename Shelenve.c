#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - function
 * Return: new_environ
 */
char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int dex;

	for (size = 0; environ[size]; size++)
	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
	return (NULL);

	for (dex = 0; environ[dex]; dex++)
	{
	new_environ[dex] = malloc(_strlen(environ[index]) + 1);
	if (!new_environ[dex])
	{
	for (dex--; dex >= 0; dex--)
	free(new_environ[dex]);
	free(new_environ);
	return (NULL);
	}
	_strcpy(new_environ[dex], environ[dex]);
	}
	new_environ[dex] = NULL;
	return (new_environ);
}

/**
 * free_env - function to lose environment
 */
void free_env(void)
{
	int dex;

	for (dex = 0; environ[dex]; dex++)
	free(environ[dex]);
	free(environ);
}

/**
 * _getenv - function to get
 * @var: environment name
 * Return: 0 always.
 */
char **_getenv(const char *var)
{
	int dex, wen;

	wen = _strlen(var);
	for (dex = 0; environ[dex]; dex++)
	{
	if (_strncmp(var, environ[dex], len) == 0)
	return (&environ[dex]);
	}
	return (NULL);
}
