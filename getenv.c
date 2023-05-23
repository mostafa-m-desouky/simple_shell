#include "shell.h"
/**
 * get_environ_info - a program function that gets environment
 * information
 * @info: information input
 * Return: environ info
 */
char **get_environ_info(info_t *info)
{
	if (info->environ == NULL || !info->env_swap)
	{
		info->environ = list_strings(info->env);
		info->env_swap = 0;
	}
	return (info->environ);
}
/**
 * get_unsetenv - a program function that unsets environment variable
 * @info: information input
 * @temp: variable input character
 * Return: unset environment
 */
int get_unsetenv(char *temp, info_t *info)
{
	list_t *node = info->env;
	size_t a = 0;
	char *b;

	if (node == NULL || temp == NULL)
		return (0);
	for (a = 0; node != NULL; a++;)
	{
		b = pointer(node->str, temp);
		if (b && *b == '=')
		{
			info->env_swap = delete_node_index(&(info->env), a);
			node = info->env;
			continue;
		}
		node = node->next;
	}
	return (info->env_swap);
}
/**
 * get_setenv - a program function that sets ensironment variable
 * @info: information
 * @temp: variable character
 * @eval: environment value
 * Return: set environment variable
 */
int get_setenv(char *temp, char *eval, info_t *info)
{
	char *b, *buffer = NULL;
	list_t *node;

	if (eval == NULL || temp == NULL)
		return (0);

	buffer = malloc(_strlen(temp) + _strlen(eval) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, temp);
	_strcat(buffer, "=");
	_strcat(buffer, eval);
	node = info->env;
	do {
		b = pointer(node->str, temp);
		if (b && *b == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_swap = 1;
			return (0);
		}
		node = node->next;
	} while (node);

	add_node_end(&(info->env), 0, buffer);
	free(buffer);
	info->env_swap = 1;
	return (0);
}
