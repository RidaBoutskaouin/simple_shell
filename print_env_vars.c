#include "shell.h"

/**
 * print_env_vars - Prints all environment variables
 * Return: void
 */

void print_env_vars()
{
    extern char **environ;
    int i = 0;

    for (i = 0; environ[i] != NULL; i++)
    {
        (void)write(STDOUT_FILENO, environ[i], strlen(environ[i]));
        (void)write(STDOUT_FILENO, "\n", 1);
    }
}
