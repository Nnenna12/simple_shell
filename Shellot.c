#include "shell.h"
char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);
char *get_location(char *cmd);

/**
 * get_location - function
 * @cmd: parameter
 * Return: 0 always
 */
char *get_location(char *cmd)
{
	char **path, *temp;
	list_t *dirs, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_path_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(_strlen(dirs->dir) + _strlen(cmd) + 2);
		if (!temp)
			return (NULL);

		_strcpy(temp, dirs->dir);
		_strcat(temp, "/");
		_strcat(temp, cmd);

		if (stat(temp, &st) == 0)
		{
			free_list(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}
	free_list(head);

	return (NULL);
}

/**
 * fill_path_dir - function
 * @path: parameter.
 * Return: 0 always
 */
char *fill_path_dir(char *path)
{
	int i, wen = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				wen += _strlen(pwd) + 1;
			else
				wen++;
		}
		else
			wen++;
	}
	path_copy = malloc(sizeof(char) * (wen + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}


/**
 *  get_path_dir - function
 *  @path: parameter
 * Return: 0 always
 */
list_t *get_path_dir(char *path)
{
	int dex;
	char **dirs, *path_copy;
	list_t *head = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = _strtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (dex = 0; dirs[dex]; dex++)
	{
		if (add_node_end(&head, dirs[dex]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}
	free(dirs);
	return (head);
}
