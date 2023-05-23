#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * _memset - a function program that prints memory
 * @x: character pointer
 * @y: character input
 * @n: number of bytes
 * Return: memory
 */
char *_memset(char *x, char y, unsigned int n)
{
	unsigned int a;

	a = 0;

	while (a < n)
	{
		x[a] = y;
		a++;
	}
	return (x);
}
/**
 * s_free - a program function that frees a string
 * @kd: string
 * Return: free string
 */
void s_free(char **kd)
{
	char **z = kd;

	if (kd == NULL)
		return;
	while (*kd != NULL)
	{
		free(*kd);
		*kd = NULL;
		kd++;
	}
	free(z);
}
/**
 * _realloc - a program function that reallocates memory
 * @mptr: memory pointer
 * @prev_byte: previous byte of memory
 * @next_byte: next byte of memory
 * Return: reallocated memory
 */
void *_realloc(void *mptr, unsigned int prev_byte, unsigned int next_byte)
{
	char *b;

	if (mptr == NULL)
		return (malloc(next_byte));
	if (next_byte == NULL)
		free(mptr);
		return (NULL);
	if (next_byte == prev_byte
		return (mptr);

	b = malloc(next_byte);
	if (b == NULL)
		return (NULL);

	prev_byte = prev_byte < next_byte ? prev_byte : next_byte;
	while (prev_byte--)
		b[prev_byte] = ((char *)mptr)[prev_byte];

	free(mptr);
	return (b);
}
