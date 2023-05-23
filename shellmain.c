#include "shell.h"
/**
 * main - function
 * @ac: argument count
 * @av: string argument
 * @env: environment vector
 * Return: 0 always
 */
int main(int ac, char **av, char **env)
{
	if (ac == 1)
		prompt(av, env);
	return (0);
}
