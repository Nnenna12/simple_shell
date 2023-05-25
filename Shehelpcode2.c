#include "shell.h"
void free_arg(char **args, char **fnt);
char *get_pid(void);
char *get_env_val(char *ben, int wen);
void variable_replacement(char **args, int *exec_ret);
/**
 * free_arg - function
 * @args: string of argument
 * @fnt: beginning of string
 */
void free_arg(char **args, char **fnt)
{
	size_t j;

	for (j = 0; args[j] || args[j + 1]; j++)
		free(args[j]);

	free(fnt);
}

/**
 * get_pid - function
 * Return: buffer
 */
char *get_pid(void)
{
	size_t j = 0;
	char *buff;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Wont read file");
		return (NULL);
	}
	buff = malloc(120);
	if (!buff)
	{
		close(file);
		return (NULL);
	}
	read(file, buff, 120);
	while (buff[j] != ' ')
		j++;
	buff[j] = '\0';

	close(file);
	return (buff);
}

/**
 * get_env_val - function
 * @ben: parameter
 * @wen: Parameters
 * Return: 0 always
 */
char *get_env_val(char *ben, int wen)
{
	char **var_adr;
	char *replacement = NULL, *temp, *var;

	var = malloc(wen + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, ben, wen);

	var_adr = _getenv(var);
	free(var);
	if (var_adr)
	{
		temp = *var_adr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}
	return (replacement);
}


/**
 * variable_replacement - function
 * @ln: parameter
 * @exec_ret: parameters
 */
void variable_replacement(char **ln, int *exec_ret)
{
	int j, k = 0, wen;
	char *replacement = NULL, *old_ln = NULL, *new_ln;

	old_ln = *ln;
	for (j = 0; old_ln[j]; j++)
	{
		if (old_ln[j] == '$' && old_ln[j + 1] &&
				old_ln[j + 1] != ' ')
		{
			if (old_ln[j + 1] == '$')
			{
				replacement = get_pid();
				k = j + 2;
			}
			else if (old_ln[j + 1] == '?')
			{
				replacement = _ito(*exec_ret);
				k = j + 2;
			}
			else if (old_ln[j + 1])
			{
				for (k = j + 1; old_ln[k] &&
						old_ln[k] != '$' &&
						old_ln[k] != ' '; k++)
					;
				for (k = j + 1; old_ln[k] &&
						old_ln[k] != '$' &&
						old_ln[k] != ' '; k++)
					;
				replacement = get_env_val(&old_ln[j + 1], wen);
			}
			new_ln = malloc(j + _strlen(replacement) +
					_strlen(&old_ln[k]) + 1);
			if (!ln)
				return;
			new_ln[0] = '\0';
			_strncat(new_ln, old_ln, j);
			if (replacement)
			{
				_strcat(new_ln, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_ln, &old_ln[k]);
			free(old_ln);
			*ln = new_ln;
			old_ln = new_ln;
			j = -1;
		}
	}
}
