#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	char *ret;
	int length = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc((length + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - print an input string
 * @str: the string to be printed
 * Return Nothing
 */
void _puts(char *str)
{
	int i;

	if (!str)
		return;

	for (i = 0; str[i] != '\0'; i++)
		_putchar(str[i]);
}

/**
 * _putchar - writes the character c to stdout
 * @c: the character to print
 * Return: on success 1.
 * on error, -1 is returned, and errno is set appropriately
 */
int _putchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;

	if (c != BUF_FLUSH)
	{
		buf[i++] = c;
		if (i >= WRITE_BUF_SIZE || c == '\n')
		{
			write(1, buf, i);
			i = 0;
		}
	}
	else
	{
		write(1, buf, i);
		i = 0;
	}

	return (1);
}
