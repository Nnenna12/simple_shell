#include "shell.h"
#include <sys/wait.h>

int _helperfunction();
/**
 * _helperfunction - function
 * Return: 0 always
 */
int _helperfunction()
{
	char *str = NULL;
	int j;
	ssize_t fig_char;
	ssize_t m = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("icandoit$ ");
		fig_char = getline(&str, &m, stdin);
		if (fig_char == -1)
		{
			free(str);
			exit(EXIT_FAILURE);
		}
		j = 0;
		while (str[j])
		j++;
		{
			if (str[j] == '\n')
				str[j] = 0;
		}
		return (0);
	}
}
/**
 * prompt - function
 * @env: environment vector
 * @av: argument vector
 * Return: 0 always
 */
void prompt(char **av, char **env)
{
	char *argv[] = {NULL, NULL};
	pid_t ch_id;
	char *str;
	int status;

	argv[0] = str;
	ch_id = fork();
	if (ch_id == -1)
	{
		free(str);
		exit(EXIT_FAILURE);
	}
	if (ch_id == 0)
	{
		if (execve(argv[0], argv, env) == -1)
			printf("%s; No such file or directory\n", av[0]);
	}
	else
		wait(&status);
}
