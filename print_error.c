#include "shell.h"



void print_error(char **av, int cnt, char *line)
{
    char count_str = cnt + '0';

    write(STDERR_FILENO, av[0], strlen(av[0]));
	write(STDERR_FILENO, ": line ", 7);
    write(STDERR_FILENO, &count_str, 1);
    write(STDERR_FILENO, ": ", 2);
    write(STDERR_FILENO, line, strlen(line));
    write(STDERR_FILENO, ": ", 2);
    perror("");
}