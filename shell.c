#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
/**
 * main - Entry point for the program
 * @ac: Number of arguments
 * @av: Array of argument strings
 * @env: Array of environment strings
 *
 * Return: EXIT_SUCCESS upon successful completion
 */

int main(int ac, char **av, char **env)
{
	char *line = NULL, *clean_line = NULL, delims[] = " \t\n;", **words = NULL,
		 *command = NULL, *abs_cmd = NULL;
	int num_chars = 0, status = 0, i = 0, cnt = 0, empty_input = 1, j;
	pid_t my_pid;
	size_t size_line = 0;
	ssize_t bytes_written;
	bool is_stream = isatty(STDIN_FILENO), isabs;

	(void)ac;

	if (is_stream == 0)
	{
		do
		{
			cnt += 1;
			num_chars = _getline(&line, &size_line, stdin);

			empty_input = 1;
			for (j = 0; j < num_chars - 1; j++) {
				if (line[j] != ' ') {
					empty_input = 0;
					break;
				}
			}

			if (empty_input == 1)
			{
				free(line);
				line = NULL;
				continue;
			}

			line = edge_cases(num_chars, status, line, abs_cmd);

			words = malloc(sizeof(char *) * 1024);
			if (words == NULL)
				perror("malloc error");

			clean_line = strtok(line, delims);
			while (clean_line != NULL)
			{
				words[i] = clean_line;
				i++;
				clean_line = strtok(NULL, delims);
			}
			words[i] = NULL;

			handle_exit(i, words, av, cnt, line);

			/* fork */
			my_pid = fork();
			if (my_pid == -1)
			{
				perror("fork error");
				exit(EXIT_FAILURE);
			}

			if (my_pid == 0)
			{
				if (words[0] != NULL)
				{
					isabs = is_absolute_path(words[0]);
					if (isabs == false)
					{
						command = full_command(words[0]);
						if (command != NULL)
						{
							if (execve(command, words, env) == -1)
								exit(2);
						}
						else
						{
							print_error(av, cnt, line, isabs);
							exit(127);
						}
					}
					else
					{
						command = words[0];
						if (command != NULL)
						{
							if (execve(command, words, env) == -1)
							{
								if (errno == ENOENT) {
									print_error(av, cnt, line, isabs);
									exit(2);
								}
							}
							exit(2);
						}
						else
						{
							print_error(av, cnt, line, isabs);
							exit(127);
						}
					}
				}
				else
				{
					exit(0);
				}
			}
			else
			{
				wait(&status);
				free(words);
				if (empty_input != 1)
					free(line);
				free(command);
				i = 0;
			}
			line = NULL;
			words = NULL;
			abs_cmd = NULL;
		} while (num_chars != -1);
	}
	else
	{
		while (true)
		{
			bytes_written = write(1, "$ ", 2);
			if (bytes_written == -1)
			{};

			num_chars = _getline(&line, &size_line, stdin);

			
			for (j = 0; j < num_chars - 1; j++) {
				if (line[j] != ' ') {
					empty_input = 0;
					break;
				}
			}

			if (empty_input == 1)
			{
				free(line);
				line = NULL;
				continue;
			}

			line = edge_cases(num_chars, status, line, abs_cmd);

			words = malloc(sizeof(char *) * 1024);
			if (words == NULL)
				perror("malloc error");

			/*words = fill_array(clean_line, line, delims, words, i);*/
			
			clean_line = strtok(line, delims);
			while (clean_line != NULL)
			{
				words[i] = clean_line;
				i++;
				clean_line = strtok(NULL, delims);
			}
			words[i] = NULL;
			handle_exit(i, words, av, cnt, line);

			my_pid = fork();
			if (my_pid == -1)
			{
				perror("fork error");
				exit(EXIT_FAILURE);
			}

			if (my_pid == 0)
				child_process_terminal(words, command, env, cnt, av, line);
			else
			{
				wait(&status);
				free(words);
				free(line);
				i = 0;
			}

			line = NULL;
			words = NULL;
			abs_cmd = NULL;
		}
		if (empty_input != 1)
			free(line);
	}
	return (0);
}
