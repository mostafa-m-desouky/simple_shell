#include "shell.h"
/**
 * _memfree - a program function that frees a pointer
 * @mptr: a pointer to the free memory
 * Return: free memory
 */
int _memfree(void **mptr)
{
	if (mptr && *mptr)
	{
		free(*mptr);
		*mptr = NULL;
		return (1);
	}
	return (0);
}
