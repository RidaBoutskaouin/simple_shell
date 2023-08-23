#include "shell.h"

/**
 * print_error_exit - Prints error message for exit
 * @av: Array of argument strings
 * @cnt: Count of commands entered
 * @line: Pointer to the line buffer
 *
 * Return: void
 */

void print_error_exit(char **av, int cnt, char **words)
{
	ssize_t bytes_written;
	char count_str = cnt + '0';

	bytes_written = write(STDERR_FILENO, av[0], strlen(av[0]));
	bytes_written = write(STDERR_FILENO, ": line ", 7);
	bytes_written = write(STDERR_FILENO, &count_str, 1);
	bytes_written = write(STDERR_FILENO, ": exit: ", 8);
	bytes_written = write(STDERR_FILENO, words[1], strlen(words[1]));
	bytes_written = write(STDERR_FILENO, ": numeric argument required\n", 28);
	if (bytes_written == -1)
	{};
}
