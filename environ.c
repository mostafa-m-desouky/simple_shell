#include "shell.h"

/**
 * _myenv - out put the current enviroment
 * @info: Arguments used to maintain constant fun prototype
 * Return: 0 (success)
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets value of an environ variable
 * @info: Arguments used to maintain
 * @name: env var name
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *i;

	while (node)
	{
		i = start_with(node->str, name);
		if (i && *i)
			return (i);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv -  create a new environment varianle or
 * modify an existing one
 * @info: Arguments used to maintain constant function prototype.
 * Return: 0 success.
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Error: incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info:  arguments used to maintain constant function protype
 * Return: Always 0.
 */
int _myunsetenv(info_t *info)
{
	int index;

	if (info->argc <= 1)
	{
		_eputs("Error: Too few arguements.\n");
		return (1);
	}
	for (index = 1; index <= info->argc; index++)
	{
		if (_unsetenv(info, info->argv[index]) != 0)
		{
			_eputs(info, "Failed to unset environment variable: ");
			return (1);
		}
	}

	return (0);
}

/**
 * populate_evn_list - aggrigate environment linked list
 * @info: arguments used to maintain constant function prototype
 * Return: 0 success
 */
int populate_evn_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[0]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
