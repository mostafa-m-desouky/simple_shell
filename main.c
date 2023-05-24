#include "shell.h"
#include <stdio.h>
/**
 * eputs - a program function that writes error to standard stream
 * @str: string
 * Return: written error
 */
void eputs(const char *str)
{
	fprintf(stderr, "%s\n", str);
}
/**
 * main - the startof the main function
 * @agc: integer input
 * @agv: character input
 * Return: Always 0
 */
int main(int agc, char **agv)
{
	int pd = 2;
	info_t info[] = { INFO_INIT };

	__asm__ __volatile__ ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (pd)
			: "r" (pd));
	if (agc == 2)
	{
		pd = open(agv[1], O_RDONLY);
		if (pd == -1)
		{
			if (errno == EACCES)
			{
				exit(126);
			}
			if (errno == ENOENT)
			{
				_eputs(agv[0]);
				_eputs(": 0: Close ");
				_eputs(agv[1]);
				_eputchar('\n');
				_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readpd = pd;
	}
	populate_env_list(info);
	create_history(info);
	hsh(info, agv);
	return (EXIT_SUCCESS);
}
