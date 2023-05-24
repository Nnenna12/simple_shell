#include "shell.h"
#include <sys/wait.h>
#include <string.h>
#define MAX_COMMAND 10
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
