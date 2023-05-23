#include "shell.h"
/**
 * init_info_struct - a program function that clears information
 * @info: information
 * Return: info
 */
void init_info_struct(info_t *info)
{
	memset(info, 0, sizeof(info_t));
}
/**
 * init_set_info - a program function that sets info_t
 * @info: information
 * @arr: array of arguements
 * Return: info
 */
void init_set_info(char **arr, info_t *info)
{
	info->lname = arr[0];
	if (info->arg)
	{
		info->argv = malloc(sizeof(char *) * 2);
		if (info->argv)
		{
			info->argv[0] = _strdup(info->arg);
			info->argv[1] = NULL;
		}
		int a = 0;

		while (info->argv && info->argv[a])
		{
			a++;
		}
		info->argc = a;

		replace_alias(info);
		replace_vars(info);
	}
}
/**
 * free_info_struct - a program function that frees information
 * @info: information
 * @sfd: integer input
 * Return: freed info
 */
void free_info_struct(int sfd, info_t *info)
{
	s_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (sfd)
	{
		if (info->cmd_buf == NULL)
		{
			free(info->arg);
			info->arg = NULL;
		}
		free_list(&(info->env));
		free_list(&(info->alias));
		free_list(&(info->history));
		s_free(info->environ);
		info->environ = NULL;
		_memfree((void **)info->cmd_buf);
		if (info->readpd > 2)
		{
			close(info->readpd);
		}
		_putchar(BUF_FLUSH);
	}
}

