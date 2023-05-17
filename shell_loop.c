#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: argument vector from main()
 * Return: 0 Success, 1 on error,
 */
int hsh(info_t *info, char **av)
{
	ssize_t input_size = 0;
	int builtin_ret = 0;

	while (input_size != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (is_interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		input_size = get_input(info);
		if (input_size != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (buildin_ret == -1)
				find_cmd(info);
		}
		else if (is_interactive(info))
			_putchar('\n');
		freeOinfo(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!is_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: parameter & return info struct
 * Return: -1 if builtin not found
 * 0 if builtin executed successfully,
 * 1 if builtin  found but not  successful,
 * -2 if builtin singnals exit()
 */
int find_builtin(info_t *info)
{
	const char *name = info->argv[0];
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = buildintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter and return info struct
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, m;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line - count++;
		info->linecount_flag = 0;
	}
	/*counter the number of arguments (excluding whitespace)*/
	for (i = 0, m = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], "\t\n"))
			m++;
	/*if thre are no argument, return immediately*/
	if (m == 0)
		return;

	/*check if the command is in the path environment variable*/
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path != NULL)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a exec thread to run cmd
 * @info: the parameter & return info struct
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

