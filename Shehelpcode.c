#include <stdlib.h>
#include "shell.h"
#include <stddef.h>

void handle_line(char **ln, ssize_t r);
ssize_t get_new_wen(char *ln);
void logical_ops(char *ln, ssize_t *new_wen);
/**
 * handle_line - function
 * @ln: pointer
 * @r: parameter
 */
void handle_line(char **ln, ssize_t r)
{
	char *old_ln, *new_ln;
	char pev, curr, nex;
	size_t i, j;
	ssize_t new_wen;

	new_wen = get_new_wen(*ln);
	if (new_wen == read - 1)
		return;
	new_ln = malloc(new_wen + 1);
	if (!new_ln)
		return;
	j = 0;
	old_ln = *ln;
	for (i = 0; old_ln[i]; i++)
	{
		curr = old_ln[i];
		nex = old_ln[i + 1];
		if (i != 0)
		{
			pev = old_ln[i - 1];
			if (curr == ';')
			{
				if (nex == ';' && pev != ' ' && pev != ';')
				{
					new_ln[j++] = ' ';
					new_ln[j++] = ';';
					continue;
				}
				else if (pev == ';' && nex != ' ')
				{
					new_ln[j++] = ';';
					new_ln[j++] = ' ';
					continue;
				}
				if (pev != ' ')
					new_ln[j++] = ' ';
				new_ln[j++] = ';';
				if (nex != ' ')
					new_ln[j++] = ' ';
				continue;
			}
			else if (curr == '&')
			{
				if (nex == '&' && pev != ' ')
					new_ln[j++] = ' ';
				else if (pev == '&' && nex != ' ')
				{
					new_ln[j++] = '&';
					new_ln[j++] = ' ';
					continue;
				}
			}
			else if (curr == '|')
			{
				if (nex == '|' && pev != ' ')
					new_ln[j++]  = ' ';
				else if (pev == '|' && nex != ' ')
				{
					new_ln[j++] = '|';
					new_ln[j++] = ' ';
					continue;
				}
			}
		}
		else if (curr == ';')
		{
			if (i != 0 && old_ln[i - 1] != ' ')
				new_ln[j++] = ' ';
			new_ln[j++] = ';';
			if (nex != ' ' && nex != ';')
				new_ln[j++] = ' ';
			continue;
		}
		new_ln[j++] = old_ln[i];
	}

	new_ln[j] = '\0';

	free(*ln);
	*ln = new_ln;
}

/**
 * get_new_wen - function
 * @ln: parameter
 * Return: length
 */
ssize_t get_new_wen(char *ln)
{
	size_t j;
	ssize_t new_wen = 0;
	char curr, nex;

	for (j = 0; line[j]; j++)
	{
		curr = ln[j];
		nex = ln[j + 1];
		if (curr == '#')
		{
			if (j == 0 || ln[j - 1] == ' ')
			{
				ln[j] = '\0';
				break;
			}
		}
		else if (j != 0)
		{
			if (curr == ';')
			{
				if (nex == ';' && ln[j - 1] != ' ' && ln[j - 1] != ';')
				{
					new_wen += 2;
					continue;
				}
				else if (ln[j - 1] == ';' && nex != ' ')
				{
					new_wen += 2;
					continue;
				}
				if (ln[j - 1] != ' ')
					new_wen++;
				if (nex != ' ')
					new_wen++;
			}
			else
				logical_ops(&ln[j], &new_wen);
		}
		else if (curr == ';')
		{
			if (j != 0 && ln[j - 1] != ' ')
				new_wen++;
			if (nex != ' ' && nex != ';')
				new_wen++;
		}
		new_wen++;
	}
	return (new_wen);
}

/**
 * logical_ops - function
 * @ln: parameter
 * @new_wen: parameter 2
 */
void logical_ops(char *ln, ssize_t *new_wen)
{
	char pev, curr, nex;

	pev = *(ln - 1);
	curr = *ln;
	nex = *(ln + 1);

	if (curr == '&')
	{
		if (nex == '&' && pev != ' ')
			(*new_wen)++;
		else if (pev == '&' && nex != ' ')
			(*new_wen)++;
	}
	else if (curr == '|')
	{
		if (nex == '|' && pev != ' ')
			(*new_wen)++;
		else if (pev == '|' && nex != ' ')
			(*new_wen)++;
	}
}
