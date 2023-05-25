#include "shell.h"
int wont_open(char *file_pth);
int proc_file_commands(char *file_path, int *exe_ret);
/**
 * wont_open - function
 * @file_pth: Path to the supposed file
 * Return: 13
 */
int wont_open(char *file_pth)
{
	char *error, *hist_str;
	int wen;

	hist_str = _ito(hist);
	if (!hist_str)
		return (13);

	wen = _strlen(name) + _strlen(hist_str) + _strlen(file_pth) + 16;
	error = malloc(sizeof(char) * (wen + 1));
	if (!error)
	{
		free(hist_str);
		return (13);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Won't open ");
	_strcat(error, file_pth);
	_strcat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, wen);
	free(error);
	return (13);
}

/**
 * file_commands - function
 * @file_pth: Path to the file.
 * @exec_ret: executed file
 * Return: 13
 */
int file_commands(char *file_pth, int *exec_ret)
{
	ssize_t file, b_read, j;
	unsigned int ln_size = 0;
	unsigned int old_size = 120;
	char *ln, **args, **fnt;
	char buff[120];
	int ret;

	hist = 0;
	file = open(file_pth, O_RDONLY);
	if (file == -1)
	{
		*exec_ret = wont_open(file_pth);
		return (*exec_ret);
	}
	ln = malloc(sizeof(char) * old_size);
	if (!ln)
		return (-1);
	do {
		b_read = read(file, buff, 119);
		if (b_read == 0 && ln_size == 0)
			return (*exec_ret);
		buff[b_read] = '\0';
		ln_size += b_read;
		ln = _realloc(ln, old_size, ln_size);
		_strcat(ln, buff);
		old_size = ln_size;
	} while (b_read);
		for (j = 0; ln[j] == '\n'; j++)
			ln[j] = ' ';
		for (; j < ln_size; j++)
		{
			if (ln[j] == '\n')
			{
				ln[j] = ';';
				for (j += 1; j < ln_size && ln[j] == '\n'; j++)
					ln[j] = ' ';
			}
		}
		variable_replacement(&ln, exec_ret);
		handle_line(&ln, ln_size);
		args = _strtok(ln, " ");
		free(ln);
		if (!args)
			return (0);
		if (check_arg(args) != 0)
		{
			*exec_ret = 2;
			free_arg(args, args);
			return (*exec_ret);
		}
		fnt = args;
		for (j = 0; args[j]; j++)
		{
			if (_strncmp(args[j], ";", 1) == 0)
			{
				free(args[j]);
				args[j] = NULL;
				ret = call_arg(args, fnt, exec_ret);
				args = &args[++j];
				j = 0;
			}
		}
		ret = call_arg(args, fnt, exec_ret);

		free(fnt);
		return (ret);
}

