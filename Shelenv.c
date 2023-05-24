#include <stdlib.h>

int shel_env(char **args, char __attribute__((__unused__)) **front);
int shel_setenv(char **args, char __attribute__((__unused__)) **front);
int shel_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shel_env - function
 * @args: array of argument
 * @fnt: beginning of arguments.
 * Return: 0 always
 */
int shel_env(char **args, char __attribute__((__unused__)) **fnt)
{
	int dex;
	char nc = '\n';

	if (!environ)
	return (-1);
	for (dex = 0; environ[dex]; dex++)
	{
	write(STDOUT_FILENO, environ[dex], _strlen(environ[dex]));
	write(STDOUT_FILENO, &nc, 1);
	}
	(void)args;
	return (0);
}

/**
 * shel_setenv - function
 * @args: array of argument
 * @front: beginning of argument
 * Return: 0 always
 */
int shel_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_val;
	size_t size;
	int dex;

	if (!args[0] || !args[1])
	return (create_error(args, -1));
	new_val = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_val)
	return (create_error(args, -1));
	_strcpy(new_val, args[0]);
	_strcat(new_val, "=");
	_strcat(new_val, args[1]);
	env_var = getenv(args[0]);
	if (env_var)
	{
	free(*env_var);
	*env_var = new_val;
	return (0);
	}
	for (size = 0; new_environ[size]; size++)
	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
	free(new_val);
	return (create_error(args, -1));
	}
	for (dex = 0; new_environ[dex]; dex++)
	new_environ[dex] = new_environ[dex];
	free(new_environ);
	new_environ = new_environ;
	new_environ[dex] = new_val;
	new_environ[dex + 1] = NULL;
	return (0);
}

/**
 * shel_unsetenv - function
 * @args: array of argument
 * @front: beginning of argument
 * Return: 0 always.
 */
int shel_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environ;
	size_t size;
	int dex, dex2;

	if (!args[0])
	return (create_error(args, -1));
	env_var = getenv(args[0]);
	if (!env_var)
	return (0);
	for (size = 0; new_environ[size]; size++)
	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
	return (create_error(args, -1));
	for (dex = 0, dex2 = 0; new_environ[dex]; dex++)
	{
	if (*env_var == new_environ[dex])
	{
	free(*env_var);
	continue;
	}
	new_environ[dex2] = new_environ[dex];
	dex2++;
	}
	free(new_environ);
	new_environ = new_environ;
	new_environ[size - 1] = NULL;
	return (0);
}
