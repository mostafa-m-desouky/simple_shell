#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @buf: the char  buffer
 * @info: the parameter struct
 * @p: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;
	int isChain = 0;

	if (buf[j] == '|')
	{
		if (buf[j + 1] == '|')
		{
			buf[j] = 0;
			j++;
			info->cmd_buf_type = CMD_OR;
			ischain = 1;
		}
	}
	else if (buf[j] == '&')
	{
		if (buf[j + 1] == '&')
		{
			buf[j] = 0;
			j++;
			info->cmd_buf_type = CMD_AND;
			ischain = 1;
		}
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
		ischain = 1;
	}
	*p = j;
	return (isChain);
}

/**
 * check_chain - check we should continue chaining based on last status
 * @info: the parameter struct
 * @len: length of buf
 * @buf: the char buffer
 * @i: starting position in buf
 * @p: address of current position in buf
 * Return: void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t len, size_t i)
{
	size_t j = *p;

	if ((info->cmd_buf_type == CMD_AND && info->status)
			|| (info->cmd_buf_type == CMD_OR && !info->status))
	{
		buf[i] = 0;
		j = len;
	}
	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 * Return: i if replaced, 0 otherwise
 */
int replace_alias(info *info)
{
	int i;
	last_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=')
			if (!p)
				return (0);

		p++; /*move the pointer to the value after the '=' character*/
		char *p_copy = _strdup(p);

		if (!p_copy)
			return (0);

		info->argv[0] = p_copy;
	}

	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	while (info->argv[i] == NULL)
	{
		if (info->argv[i][0] == '$' && info->argv[i][1] != '\0')
		{
			if (!_strcmp(info->argv[i], "$?"))
			{
				replace_string(&(info->argv[i]),
						_strdup(covert_number(info->status, 10, 0)));
			}
			else if (!_strcmp(info->argv[i], "$$"))
			{
				node = node_starts_with(&(info->argv[i]),
						_strdup(covert_number(info->getpid(),
								10, 0)));
			}
			else
			{
				node = node_starts_with(info->env, &(info->argv[i][1]), '=');
				if (node)
				{
					replace_string(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1))
				}
				else
				{
					replace_string(&(info->argv[i]), _strdup(""));
				}
			}
		}
		i++
	}
	return (0);
}

/**
 * replace-string - replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	if (*old != NULL)
	{
		free(*old);
	}
	*old = new;
	return (1);
}
