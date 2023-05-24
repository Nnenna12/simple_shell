#include "shell.h"
char *get_arg(char *ln, int *exec_ret);
int call_arg(char **args, char **front, int *exec_ret);
int run_arg(char **args, char **fnt, int *exec_ret);
int handle_arg(int *exec_ret);
int check_arg(char **args);
/**
 * get_arg - function
 * @ln: command
 * @exec_ret: executed command
 * Return: ret
 */
char *get_arg(char *ln, int *exec_ret)
{
	size_t m = 0;
	ssize_t r;
	char *prompt = "$ ";

	if (ln)
		free(ln);
	r = _getline(&ln, &n, STDIN_FILENO);
	if (r == -1)
		return (NULL);
	if (r == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_arg(ln, exec_ret));
	}

	ln[r - 1] = '\0';
	variable_replacement(&ln, exec_ret);
	handle_line(&ln, r);

	return (ln);
}

/**
 * call_arg - function
 * @args: array of arguments
 * @fnt: beginning of argument
 * @exec_ret: executed command
 * Return: ret
 */
int call_arg(char **args, char **fnt, int *exec_ret)
{
	int ret, dex;

	if (!args[0])
		return (*exec_ret);
	for (dex = 0; args[dex]; dex++)
	{
		if (_strncmp(args[dex], "||", 2) == 0)
		{
			free(args[dex]);
			args[dex] = NULL;
			args = replace_als(args);
			ret = run_arg(args, fnt, exec_ret);
			if (*exec_ret != 0)
			{
				args = &args[++dex];
				dex = 0;
			}
			else
			{
				for (dex++; args[dex]; dex++)
					free(args[dex]);
				return (ret);
			}
		}
		else if (_strncmp(args[dex], "&&", 2) == 0)
		{
			free(args[dex]);
			args[dex] = NULL;
			args = replace_als(args);
			ret = run_arg(args, fnt, exec_ret);
			if (*exec_ret == 0)
			{
				args = &args[++dex];
				dex = 0;
			}
			else
			{
				for (dex++; args[dex]; dex++)
					free(args[dex]);
				return (ret);
			}
		}
	}
	args = replace_als(args);
	ret = run_arg(args, front, exec_ret);
	return (ret);
}

/**
 * run_arg - function
 * @args: array of arguments
 * @fnt: beginning of argument
 * @exec_ret: executed command
 * Return: ret
 */
int run_arg(char **args, char **fnt, int *exec_ret)
{
	int ret, j;
	int (*builtin)(char **args, char **fnt);

	builtin = get_builtin(args[0]);
	if (builtin)
	{
		ret = builtin(args + 1, fnt);
		if (ret != EXIT)
			*exec_ret = ret;
	}
	else
	{
		*exec_ret = execute(args, fnt);
		ret = *exec_ret;
	}

	hist++;
	for (j = 0; args[j]; j++)
		free(args[j]);

	return (ret);
}

/**
 * handle_arg - function to handle argument
 * @exec_ret: executed commmand
 * Return: 0 always.
 */
int handle_arg(int *exec_ret)
{
		int ret = 0, dex;
		char **args, *ln = NULL, **fnt;

		ln = get_arg(ln, exec_ret);
		if (!ln)
			return (END_OF_FILE);

		args = _strtok(ln, " ");
		free(ln);
		if (!args)
			return (ret);
		if (check_arg(args) != 0)
		{
			*exec_ret = 2;
			free_arg(args, args);
			return (*exec_ret);
		}
		fnt = args;

		for (dex = 0; args[dex]; dex++)
		{
			if (_strncmp(args[dex], ";", 1) == 0)
			{
				free(args[dex]);
				args[dex] = NULL;
				ret = call_arg(args, fnt, exec_ret);
				args = &args[++dex];
				dex = 0;
			}
		}
		if (args)
			ret = call_arg(args, fnt, exec_ret);
		free(fnt);
		return (ret);
}

/**
 * check_arg - Checks
 * @args: argument string
 * Return: 0 always
 */
int check_arg(char **args)
{
	size_t j;
	char *cur, *dex;

	for (j = 0; args[j]; j++)
	{
		cur = args[j];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (j == 0 || cur[1] == ';')
				return (create_error(&args[j], 2));
			dex = args[j + 1];
			if (dex && (dex[0] == ';' || dex[0] == '&' || dex[0] == '|'))
				return (create_error(&args[j + 1], 2));
		}
	}
	return (0);
}
