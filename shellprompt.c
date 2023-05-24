#include "shell.h"
#include <sys/wait.h>
/**
 * prompt - function
 * @env: environment vector
 * @av: argument vector
 * Return: 0 always
 */
void prompt(char **av, char **env)
{
	char *str = NULL;
	int j, status;
	ssize_t num_char;
	size_t n = 0;
	char *argv[] = {NULL, NULL};
	 pid_t ch_id;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("simpleshell$ ");
		num_char = getline(&str, &n, stdin);
		if (num_char == -1)
		{
			free(str);
			exit(EXIT_FAILURE);
		}
		j = 0;
		while (str[j])
		{
			if (str[j] == '\n')
				str[j] = 0;
			j++;
		}
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
}
