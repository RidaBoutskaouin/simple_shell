#include "shell.h"

ssize_t _getline(char **line, size_t *lenth, FILE *stream)
{
	
	size_t buffer_size = 0, chars_read = 0;
	char c;
	char *buffer;

	(void)stream;
	buffer = NULL;
	if (line == NULL || lenth == NULL)
		return (-1);

	buffer = *line;

	while ((c = _getchar()) != -1)
	{
		if (chars_read + 1 >= buffer_size)
		{
			buffer_size += 128;
			buffer = realloc(buffer, buffer_size);
			if (buffer == NULL)
				return (-1);
		}
		buffer[chars_read++] = c;
		
		if ((c == '\n') || (c == ';'))
			break;
	}

	if (chars_read == 0)
		return (-1);

	buffer[chars_read] = '\0';
	*line = buffer;
	*lenth = buffer_size;

	return (chars_read);
}
