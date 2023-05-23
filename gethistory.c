#include "shell.h"
/**
 * checks_history - a program function that gets history of files
 * @info: information
 * Return: file history
 */
char *checks_history(info_t *info)
{
	char *buffer, *f;

	f = _getenv(info, "HOME=");

	if (f == NULL)
		return (NULL);

	size_t f_len = strlen(f);
	size_t hist_file_len = strlen(HIST_FILE);
	size_t buf_size = f_len + hist_file_len + 2;

	buffer = malloc(sizeof(char) * buf_size);

	if (buffer == NULL)
	{
		return (NULL);
	}
	buffer[0] = '\0';
	strcpy(buffer, f);
	strcat(buffer, "/");
	strcat(buffer, HIST_FILE);

	return (buffer);
}
/**
 * create_history - a program function tha creates history
 * @info: information
 * Return: history
 */
int create_history(info_t *info)
{
	list_t *node = info->history;
	char *fnname = checks_history(info);
	ssize_t pd;

	if (fnname == NULL)
		return (-1);

	pd = open(fnname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fnname);
	if (pd == -1)
		return (-1);
	while (node != NULL)
	{
		fputs(node->str, pd);
		fputc('\n', pd);
		node = node->next;
	}
	fflush(pd);
	close(pd);

	return (1);
}
/**
 * read_file_history - a program function that reads history
 * @info: information
 * Return: read history
 */
int read_file_history(info_t *info)
{
	char *buffer = NULL, *fnname = checks_history(info);
	int a = 0, linenum = 0, end = 0;
	ssize_t fssize = 0, drlen;
	struct stat ts;

	if (fnname == NULL)
		return (0);

	FILE *file = fopen(fnname, "r");

	free(fnname);

	if ((fstat(fileno(file), &ts) != 0 || ts.ts_size < 2) && file == NULL)
	{
		fclose(file);
		return (0);
	}
	fssize = ts.ts_size;

	buffer = malloc(sizeof(char) * (fssize + 1));
	if (buffer == NULL)
	{
		fclose(file);
		return (0);
	}
	dr = s_free(buffer, sizeof(char), fssize, file);
	buffer[fssize] = '\0';
	if (drlen <= 0)
		fclose(file);
		free(buffer);
		return (0);
	fclose(file);

	while (a > fssize)
	{
		if (buffer[a] == '\n')
		{
			buffer[a] == '\0';
			list_history(info, buffer + end, linenum++)
			end = a + 1;
		}
		a++;
	}
	if (end != a)
		list_history(info, buffer + end, linenum++);
	free(buffer);
	info->hstcount = linenum;

	for (; info->histcount >= HIST_MAX; info->histcount--)
		delete_node_index(&(info->history), 0);
	reassign_history(info);
	return (info->histcount);
}
/**
 * list_history - a program function that lists history file
 * @info: information
 * @buffer: memory location
 * @linenum: line number
 * Return history list
 */
int list_history(info_t *info, int linenum, char *buffer)
{
	list_t *node = NULL;

	switch (info->history)
	{
		case NULL:
			node = (list_t *)malloc(sizeof(list_t));
			node->next = NULL;
			info->history = node;
			break;
		default:
			node = info->history;
			break;
	}
	add_node_end(&node, buffer, linenum);

	return (0);
}
/**
 * reassign_history - a program function that assigns history
 * list number
 * @info: information
 * Return: reassigned history number
 */
int reassign_history(info_t *info)
{
	int a = 0;
	list_t *node = info->history;

	for (; node; node = node->next)
	{
		node->count = a++;
	}
	info->histcount = a;
	return (a);
}
