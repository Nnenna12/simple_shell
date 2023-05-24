#include <stdlib.h>

int shel_al(char **args, char __attribute__((__unused__)) **fnt);
void set_al(char *var_name, char *val);
void print_al(al_t *al);

/**
 * shel_al - commands
 * @args: array of arguments.
 * @fnt: Beginning of bar
 * Return: 0 always
 */
int shel_al(char **args, char __attribute__((__unused__)) **fnt)
{
	al_t *temp = abs;
	int j, ret = 0;
	char *val;

	if (!args[0])
	{
	while (temp)
	{
	print_al(temp);
	temp = temp->next;
	}
	return (ret);
	}
	for (j = 0; args[j]; j++)
	{
	temp = als;
	val = _strchr(args[j], '=');
	if (!val)
	{
	while (temp)
	{
	if (_strcmp(args[j], temp->name) == 0)
	{
	print_al(temp);
	break;
	}
	temp = temp->next;
	}
	if (!temp)
	ret = create_error(args + i, 1);
	}
	else
	set_al(args[j], val);
	}
	return (ret);
}

/**
 * set_al - function
 * @var_name: name
 * @val: Value
 */
void set_al(char *var_name, char *val)
{
	al_t *temp = abs;
	int wen, j, k;
	char *new_val;

	*val = '\0';
	val++;
	wen = _strlen(val) - _strspn(val, "'\"");
	new_val = malloc(sizeof(char) * (wen + 1));
	if (!new_val)
	return;
	for (j = 0, k = 0; val[j]; j++)
	{
	if (val[j] != '\'' && val[j] != '"')
	new_val[k++] = val[j];
	}
	new_val[k] = '\0';
	while (temp)
	{
	if (_strcmp(var_name, temp->name) == 0)
	{
	free(temp->val);
	temp->val = new_val;
	break;
	}
	temp = temp->next;
	}
	if (!temp)
	add_al_end(&als, var_name, new_val);
}

/**
 * print_al - Prints the al
 * @al: Pointer.
 */
void print_al(al_t *al)
{
	char *al_str;
	int wen = _strlen(al->name) + _strlen(al->val) + 4;

	al_str = malloc(sizeof(char) * (wen + 1));
	if (!al_str)
	return;
	_strcpy(al_str, al->name);
	_strcat(al_str, "='");
	_strcat(al_str, al->val);
	_strcat(al_str, "'\n");

	write(STDOUT_FILENO, al_str, wen);
	free(al_str);
}
/**
 * replace_al - function
 * @args: argument of string
 * Return: args
 */
char **replace_al(char **args)
{
	al_t *temp;
	int j;
	char *new_val;

	if (_strcmp(args[0], "al") == 0)
	return (args);
	for (j = 0; args[j]; j++)
	{
	temp = als;
	while (temp)
	{
	if (_strcmp(args[j], temp->name) == 0)
	{
	new_val = malloc(sizeof(char) * (_strlen(temp->val) + 1));
	if (!new_val)
	{
	free_args(args, args);
	return (NULL);
	}
	_strcpy(new_val, temp->val);
	free(args[j]);
	args[j] = new_val;
	J--;
	break;
	}
	temp = temp->next;
	}
	}
	return (args);
}
