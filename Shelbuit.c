#include <stdlib.h>

int shel_exit(char **args, char **fnt);
int shel_cd(char **args, char __attribute__((__unused__)) **fnt);
int shel_help(char **args, char __attribute__((__unused__)) **front);
int (*run_builtin(char *cmd))(char **args, char **fnt);

/**
 * run_builtin - built-in command
 * @cmd: command
 * Return: 0 always
 */
int (*run_builtin(char *cmd))(char **args, char **fnt)
{
	builtin_t funcs[] = {
	{ "exit", shel_exit },
	{ "env", shel_help },
	{ "setenv", shel_setenv },
	{ "unsetenv", unsetenv },
	{ "cd", shel_cd },
	{ "al", shel_cd },
	{ "help", shel_help },
	{ NULL, NULL }
	};
	int j;

	for (j = 0; funcs[j].name; j++)
	{
	if (_strcmp(funcs[j].name, cmd) == 0)
	break;
	}
	return (funcs[j].f);
}

/**
 * shel_exit - function
 * @args: argument of string
 * @fnt: beginning of frontal
 * Return: 0 always.
 */
int shel_exit(char **args, char **fnt)
{
	int j = 0, wen_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
	if (args[0][0] == '+')
	{
	j = 1;
	wen_of_int++;
	}
	for (; args[0][j]; j++)
	{
	if (j <= wen_of_int && args[0][j] >= '0' && args[0][j] <= '9')
	num = (num * 10) + (args[0][j] - '0');
	else
	return (create_error(--args, 2));
	}
	}
	else
	{
	return (-3);
	}
	if (num > max - 1)
	return (create_error(--args, 2));
	args -= 1;
	free_args(args, fnt);
	free_env();
	free_al_list(abs);
	exit(num);
}

/**
 * shel_cd - function
 * @args: An array of arguments.
 * @fnt: beginning of argument
 * Return: 0 always
 */
int shel_cd(char **args, char __attribute__((__unused__)) **fnt)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
	return (-1);
	if (args[0])
	{
	if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
	{
	if ((args[0][1] == '-' && args[0][2] == '\0') ||
	args[0][1] == '\0')
	{
	if (getenv("OLDPWD") != NULL)
	(chdir(*_getenv("OLDPWD") + 7));
	}
	else
	{
	free(oldpwd);
	return (create_error(args, 2));
	}
	}
	else
	{
	if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
	&& ((dir.st_mode & S_IXUSR) != 0))
	chdir(args[0]);
	else
	{
	free(oldpwd);
	return (create_error(args, 2));
	}
	}
	}
	else
	{
	if (_getenv("HOME") != NULL)
	chdir(*(_getenv("HOME")) + 5);
	}
	pwd = getcwd(pwd, 0);
	if (!pwd)
	return (-1);
	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
	return (-1);
	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (shellby_setenv(dir_info, dir_info) == -1)
	return (-1);
	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shel_setenv(dir_info, dir_info) == -1)
	return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
	write(STDOUT_FILENO, pwd, _strlen(pwd));
	write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * shel_help - function help
 * @args: array of arguments
 * @front: beginning of args
 * Return: 0 always
 */
int shel_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
	help_all();
	else if (_strcmp(args[0], "al") == 0)
	help_al();
	else if (_strcmp(args[0], "cd") == 0)
	shel_cd();
	else if (_strcmp(args[0], "exit") == 0)
	shel_exit();
	else if (_strcmp(args[0], "env") == 0)
	help_env();
	else if (_strcmp(args[0], "setenv") == 0)
	help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
	unsetenv();
	else if (_strcmp(args[0], "help") == 0)
	shel_help();
	else
	write(STDERR_FILENO, name, _strlen(name));
	return (0);
}
