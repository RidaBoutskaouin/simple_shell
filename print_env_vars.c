#include "shell.h"

/**
 * print_env_vars - Prints all environment variables
 * Return: void
 */

void print_env_vars()
{
    ssize_t bytes_written;
    extern char **environ;
    int i = 0;

    for (i = 0; environ[i] != NULL; i++)
    {
        bytes_written = write(STDOUT_FILENO, environ[i], strlen(environ[i]));
        bytes_written = write(STDOUT_FILENO, "\n", 1);
        if (bytes_written == -1)
        {};
    }
}
