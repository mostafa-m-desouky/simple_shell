#include "shell.h"
/**
 * input_buffer - a program function that inputs memory in buffer
 * @info: information
 * @buffer: memory loction
 * @base: input address of base variable
 * Return: buffer
 */
ssize input_buffer(info_t *info, size_t *base, char **buffer)
{
	ssize base_p = 0;
	ssize q = 0;

	if (*base == NULL)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
	q = getline(buffer, &base_b, stdin);
#else
	q = getline(buffer, &base_b, info);
#endif
	if (q > 0)
	{
		if ((*buffer)[q - 1] == '\n')
		{
			(*buffer)[q - 1] == '\0';
			q--;
		}
		info->linecount_flag = 1;
		remove_comments(*buffer);
		list_history(*buffer, info, info->histcount++);
		{
			*base = q;
			info->cmd_buf = buffer;
		}
	}
	}
	return (q);
}
/**
 * getline_input - a program that gets a line input
 * @info: information
 * Return: line
 */
ssize_t getline_input(info_t *info)
{
	ssize_t q = 0;
	char **buffer_b = &(info->arg), *b;
	static char *buffer;
	static size_t a, x, base;

	_putchar(BUF_FLUSH);
	q = input_buffer(&buffer, &base, info);
	if (q == -1)
		return (-1);
	if (base)
	{
		x = a;
		b = buffer + a;
		check_chain(info, buffer, &x, a, base);
		do {
			if (is_chain(info, buffer, &x))
				break;
			x++;
			} while (x < base);
		a = x + 1;
			if (a >= base)
			{
				a = base = 0;
				info->cmd_buf_type = CMD_NORM;
			}
			*buffer_b = b;
			return (_strlen(b));
	}
	*buffer_b = buffer;
	return (q);
}
/**
 * read_buffer - a program function that reads the buffer memory
 * @info: information
 * @buffer:  meory location
 * Return: buffer
 * @a: input size
 */
ssize_t read_buffer(info_t *info, size_t *a, char *buffer)
{
	ssize_t q = 0;

	if (*a)
	{
		return (0);
	}
	q = read(info->readpd, buffer, READ_BUF_SIZE);
	if (q >= 0)
	{
		*a = q;
	}
	return (q);
}
/**
 * _getline - a program function that gets next line input
 * @info: information
 * @ptr: pointer
 * @leng: length of line
 * Return: line or NULL on error
 */
int _getline(info_t *info, size_t *leng, char **ptr)
{
	char *b = NULL, *new_b = NULL, *s;
	size_t m;
	ssize_t q = 0, c = 0;
	static size_t a, base;
	static char buffer[READ_BUF_SIZE];

	b = *ptr;
	if (b && leng)
		c = *leng;
	if (a == base)
		a = base = 0;
	q read_buffer(info, buffer, &base);
	if (q == -1 || (q == 0 && base == 0))
		return (-1);
	s = _strchr(buffer + a, '\n');
	m = s ? 1 + (unsigned int)(s - buffer) : base;
	new_b = realloc(b, c, c ? c + m : m + 1);
	if (new_b == NULL)
		return (b ? free(b), -1 : -1);
	if (c)
		_strncat(new_b, buffer + a, m - a);
	else
		_strncat(new_b, buffer + a, m - a + 1);

	c += m - a;
	a = m;
	b = new_b;

	if (leng)
		*leng = c;
	*ptr = b;
	return (c);
}
/**
 * sigintHandler - a program function that handles signals
 * @sig_count: signal count
 * Return: signal
 */
void sigintHandler(__attribute__((unused))int sig_count)
{
	_puts("\n");
	_puts("$");
	_putchar(BUF_FLUSH);
}
