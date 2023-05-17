#include "shell.h"

/**
 * is_cmd - dtermines if a file is an executable command
 * @info: info struct
 * @path: path to the file
 * Return: 1 success, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;
	(void)info;

	if (path && !stat(path, &st) && (st.st_mode & S_IFREG))
		return (1);

	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	char *ptr = but;
	int i;

	for (i = start; i < stop; i++)
	{
		if (pathstr[i] != ':')
		{
			*ptr = pathstr[i];
			ptr++;
		}
	}
	*ptr = '\0';
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: info struct
 * @pathstr: PATH string
 * @cmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}

	for (;;)
	{
		char *next_colon = strchr(pathstr + i, ':');
		int len = (next_colon ? next_colon - pathstr : strlen(pathstr)) - i;

		path = dup_chars(pathstr, i, i + len);

		if (!*path)
			_strcat(path, cmd);
		else
		{
			_strcat(path, "/");
			_strcat(path, cmd);
		}

		if (is_cmd(info, path))
			return (path);
		if (!next_colon)
			break;

		i += len + 1;
	}
	return (NULL);
i}
