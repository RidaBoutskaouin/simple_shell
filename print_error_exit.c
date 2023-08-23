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
	char count_str = cnt + '0';

	write(STDERR_FILENO, av[0], strlen(av[0]));
    	write(STDERR_FILENO, ": ", 2);
    	write(STDERR_FILENO, &count_str, 1);
    	write(STDERR_FILENO, ": exit: ", 8);
    	write(STDERR_FILENO, "Illegal number: ", 16);
    	write(STDERR_FILENO, words[1], strlen(words[1]));
    	write(STDERR_FILENO, "\n", 1);
}
