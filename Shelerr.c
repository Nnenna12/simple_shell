#include <stdlib>

int num_wen(int n);
char *_ito(int n);
int create_error(char **args, int er);

/**
 * num_wen - function
 * @n: length
 * Return: wen.
 */
int num_wen(int n)
{
	unsigned int n1;
	int wen = 1;

	if (n < 0)
	{
	wen++;
	n1 = n * -1;
	}
	else
	{
	n1 = n;
	}
	while (n1 > 9)
	{
	wen++;
	n1 /= 10;
	}
	return (wen);
}

/**
 * _ito - function.
 * @n: parameter
 * Return: parameter.
 */
char *_ito(int n)
{
	char *buff;
	int wen = num_wen(n);
	unsigned int n1;

	buff = malloc(sizeof(char) * (wen + 1));
	if (!buff)
	return (NULL);
	buff[wen] = '\0';

	if (n < 0)
	{
	n1 = n * -1;
	buff[0] = '-';
	}
	else
	{
	n1 = n;
	}
	wen--;
	do {
	buff[wen] = (n1 % 10) + '0';
	n1 /= 10;
	wen--;
	} while (n1 > 0);
	return (buff);
}


/**
 * create_error - function
 * @args: An array of arguments.
 * @er: error
 * Return: er value.
 */
int create_error(char **args, int er)
{
	char *error;

	switch (er)
	{
	case -1:
	error = error_env(args);
	break;
	case 1:
	error = error_1(args);
	break;
	case 2:
	if (*(args[0]) == 'e')
	error = error_2_exit(++args);
	else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
	error = error_2_syntax(args);
	else
	error = error_2_cd(args);
	break;
	case 12:
	error = error_12(args);
	break;
	case 13:
	error = error_13(args);
	break;
	}
	write(STDERR_FILENO, error, _strlen(error));
	if (error)
	free(error);
	return (er);

}
