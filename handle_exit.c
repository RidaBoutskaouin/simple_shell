#include "shell.h"

/**
 * handle_exit - Handles the exit command
 * @i: Number of arguments
 * @words: Array of argument strings
 *
 * Return: void
 */

void handle_exit(int i, char **words, char **av, int cnt, char *line)
{
	int exit_status = 0;

	if (i == 2 && strcmp(words[0], "exit") == 0)
	{
		if (isValidNumber(words[1]) == 1)
		{
			exit_status = atoi(words[1]);
			free(line);
			line = NULL;
			free(words);
			words = NULL;
			exit(exit_status);
		}
		else
		{
			if (atoi(words[1]) < 0)
			{
				print_error_exit(av, cnt, words);
				free(line);
				line = NULL;
				free(words);
				words = NULL;
				exit(2);
			}
			else
			{
				print_error_exit(av, cnt, words);
				free(line);
				line = NULL;
				free(words);
				words = NULL;
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
