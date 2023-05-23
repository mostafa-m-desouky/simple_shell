#include "shell.h"
/**
 * add_node_start - a program function that add a node at the
 * start of list
 * @head: pointer to the node
 * @str: string input
 * @count: number of node
 * Return: added node
 */
list_t *add_node_start(list_t **head, int count, const char *str)
{
	list_t *current_head;

	if (head == NULL)
		return (NULL);
	current_head = malloc(sizeof(list_t));
	if (!current_head)
		return (NULL);
	_memset((void *)current_head, 0, sizeof(list_t));
	current_head->count = count;
	if (str)
	{
		current_head->str = _strdup(str);
		if (!current_head->str)
			free(current_head);
			return (NULL);
	}
	current_head->next = *head;
	*head = current_head;
	return (current_head);
}
/**
 * add_node_end - a program function that add a node at the end
 * of the list
 * @head:pointer to the node
 * @str: string
 * @count: number of input
 * Return: end node
 */
list_t *add_node_end(list_t **head, int count, const char *str)
{
	list_t *node, *current_node;

	if (!head)
		return (NULL);

	node = *head;
	current_node = malloc(sizeof(list_t));
	if (!current_node)
	{
		current_node->str = _strdup(str);
		if (current_node->str == NULL)
		{
			free(current_node);
			return (NULL);
		}
	}
	if (node)
	{
		for (; node->next; node = node->next)
			;
		node->next = current_node;
	}
	else
	{
		*head = current_node;
	}
	return (current_node);
}
/**
 * print_list - a program function that prints a list
 * @t: pointer to the node
 * Return: list
 */
size_t print_list(const list_t *t)
{
	size_t a = 0;

	for (; t; t = t->next, a++)
	{
		_puts(t->str ? t->str : "(nil)";
		_puts("\n");
	}
	return (a);

}
/**
 * delete_node_idx - a program function that deletes a node at index
 * @head: pointer to the node
 * @idx: position of node
 * Return: deleted node
 */
int delete_node_idx(list_t **head, unsigned int idx)
{
	list_t *node = *head, *ex_node;
	unsigned int a = 0;

	if (head == NULL || !*head)
		return (0);
	if (idx == 0)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
	}
	node = *head;
	ex_node = NULL;

	for (a = 0; node != NULL; a++, ex_node = node, node = node->next)
	{
		if (idx == 0)
		{
			ex_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
	}
	return (0);
}
/**
 * free_list_all -  a program fuunction that frees a list
 * @head_node: pointer address
 * Return: freed list
 */
void free_list_all(list_t **head_node)
{
	if (!head_node || *head_node == NULL)
		return;

	list_t *node = *head_node;

	head = *head_node;

	for (node = head; node != NULL; node = next_node)
	{
		next_node = node->next
		free(node->str);
		free(node);
	}
	*head_node = NULL;
}
