#include <stdlib.h>
#include "shell.h"

al_t *add_al_end(al_t **head, char *name, char *val);
void free_al_list(al_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);
/**
 * add_al_end - function
 * @head: parameters
 * @name: parameter
 * @val: parameter 1
 * Return: 0 always
 */
al_t *add_al_end(al_t **head, char *name, char *val)
{
	al_t *new_node = malloc(sizeof(al_t));
	al_t *last;

	if (!new_node)
		return (NULL);

	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->val = val;
	_strcpy(new_node->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}


/**
 * add_node_end - function
 * @head: parameters pointer
 * @dir: directory
 * Return: nodes
 */
list_t *add_node_end(list_t **head, char *dir)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *last;

	if (!new_node)
		return (NULL);

	new_node->dir = dir;
	new_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * free_al_list - Function
 * @head: parameters
 */
void free_al_list(al_t *head)
{
	al_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->val);
		free(head);
		head = next;
	}
}

/**
 * free_list - Function
 * @head: parameter
 */
void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}




