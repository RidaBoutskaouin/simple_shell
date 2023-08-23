#include "shell.h"



void print_error(char **av, int cnt, char *line, bool isabs)
{
    ssize_t bytes_written;
    char count_str = cnt + '0';

    bytes_written = write(STDERR_FILENO, av[0], strlen(av[0]));
    bytes_written = write(STDERR_FILENO, ": line ", 7);
    bytes_written = write(STDERR_FILENO, &count_str, 1);
    bytes_written = write(STDERR_FILENO, ": ", 2);
    bytes_written = write(STDERR_FILENO, line, strlen(line));
    if (bytes_written == -1)
    {};

    if (isabs == false) {
        bytes_written = write(STDERR_FILENO, ": command not found\n", 20);
        if (bytes_written == -1)
        {};
    } else if (isabs == true) {
        bytes_written = write(STDERR_FILENO, ": No such file or directory\n", 28);
        if (bytes_written == -1)
        {};
    }
}
