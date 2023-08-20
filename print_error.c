#include "shell.h"



void print_error(char **av, int cnt, char *line, bool isabs)
{
    char count_str = cnt + '0';

    write(STDERR_FILENO, av[0], strlen(av[0]));
	write(STDERR_FILENO, ": line ", 7);
    write(STDERR_FILENO, &count_str, 1);
    write(STDERR_FILENO, ": ", 2);
    write(STDERR_FILENO, line, strlen(line));

    if (isabs == false)
        write(STDERR_FILENO, ": command not found\n", 20);
    else if (isabs == true)
        write(STDERR_FILENO, ": No such file or directory\n", 28);
}