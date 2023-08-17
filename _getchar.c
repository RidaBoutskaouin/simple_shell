#include "shell.h"

char _getchar(void)
{
	char c;
	ssize_t to_read;

	to_read = read(STDIN_FILENO, &c, 1);
	if (to_read == 1)
		return (c);
	else
		return (-1);
}
