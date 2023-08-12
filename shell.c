#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>


/**
 * main - Entry point of the program
 * @ac: The number of command-line arguments
 * @av: Array of command-line argument strings
 * @env: Array of environment variable strings
 *
 * Return: 0
 */

int main(int ac, char **av, char **env)
{
	(void) ac,
	(void) av;
	char *line = NULL, *argv[] = {NULL};
	size_t size_line = 0;
	int num_chars = 0, status = 0;
	pid_t my_pid;
	bool is_stream = false;

	while (true && !is_stream)
	{
		if (isatty(STDIN_FILENO) == 0)  /* the input is from the stream */
			is_stream = true;
		if (is_stream == false)
			write(1, "$ ", 2);
		num_chars = getline(&line, &size_line, stdin);
		if (num_chars == -1)
		{
			perror("getline error");
			exit(EXIT_FAILURE); }

		line[num_chars - 1] = '\0';
		my_pid = fork();
		if (my_pid == -1)
		{
			perror("fork error");
			exit(EXIT_FAILURE); }
		if (my_pid == 0)
		{
			if (execve(line, argv, env) == -1)
			{
				perror("execve error");
				exit(EXIT_FAILURE); }
		} else
			wait(&status);

		free(line);
		line = NULL;
	}
	free(line);
	return (EXIT_SUCCESS);
}

