#include "shell.h"
/**
 * list_length_linked - a program function that checks length of list
 * @t: pointer to node
 * Return: length of list
 */
size_t list_length_linked(const list_t *t)
{
	size_t a = 0;

	for (; t; t = t->next)
	{
		a++;
	}
	return (a);
}
/**
 * list_strings - a program function that lists strings
 * @head: pointer to node
 * Return: string
 */
char **list_strings(list_t *head)
{
	char **st, *str;
	list_t *node = head;
	size_t a = list_length_linked (head), x;

	if (head == NULL || a == NULL)
		return (NULL);

	st = malloc(sizeof(char *) * (a + 1));

	if (st == NULL)
		return (NULL);

	a = 0;
	while (node)
	{
		str = malloc(_strlen(node->str) + 1);
		if (str == NULL)
		{
			x = 0;
			while (x < a)
			{
				free(st[x]);
				x++;
			}
			free(st);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		st[a] = str;
		node = node->next;
		a++;
	}
	st[a] = NULL;
	return (st);
}
/**
 * print_list_all - a program function that prints a list
 * @t: pointer
 * Return: list
 */
size_t print_list_all(const list_t *t)
{
	size_t a = 0;

	for (; t != NULL; t = t->next)
	{
		_puts(convert_number(t->count, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(t->str ? t->str : "(nil)";
		_puts("\n");
		a++;
	}
	return (a);
}
/**
 * node_pointer - a program function that starts the node
 * @node: pointer to the head
 * @prev: matching string
 * @s: character input
 * Return: node or NULL
 */
list_t *node_pointer(char prev, char s, list_t *node)
{
	char *b = NULL;

	for (; node; node = node->next)
	{
		b = pointer(node->str, prev);
		if (b && ((s == -1) || (*b == s)))
		{
			return (node);
		}
		return (NULL);
	}
}
/**
 * get_node - a program function that gets node
 * @head: start pointer
 * @node: pointer at start
 * Return: node
 */
ssize_t get_node(list_t *node, list_t *head)
{
	size_t a = 0;

	for (; head; head = head->next, a++)
	{
		if (head == node)
			return (a);
	}
	return (-1);
}
