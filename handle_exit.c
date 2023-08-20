#include "shell.h"

/**
 * handle_exit - Handles the exit command
 * @i: Number of arguments
 * @words: Array of argument strings
 *
 * Return: void
 */

void handle_exit(int i, char **words, char **av, int cnt)
{
    if (i == 2 && strcmp(words[0], "exit") == 0) // exit -98
			{
				if (isValidNumber(words[1]) == 1)
				{
					exit(atoi(words[1]));
				}
				else
				{
					if (atoi(words[1]) < 0 && atoi(words[1]) == -98)
					{
						exit(158);
					}
					else
					{
						print_error_exit(av, cnt, words); // exit tr5
						exit(2);
					}
				}
			}
			else if (i > 2 && strcmp(words[0], "exit") == 0)
			{
				perror("exit: too many arguments");
				exit(2);
			}
}