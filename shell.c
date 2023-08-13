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
 * main - Entry point for the program
 * @ac: Number of arguments
 * @av: Array of argument strings
 * @env: Array of environment strings
 *
 * Return: EXIT_SUCCESS upon successful completion
 */

int main(int ac, char **av, char **env) {
	(void)ac;
	(void)av;

	char *line = NULL, *clean_line, *argv[] = {NULL}, delims[] = " \t\n",
	     **words = NULL;

	size_t size_line = 0;
	int num_chars = 0, status = 0, i = 0;
	pid_t my_pid;

	bool is_stream = isatty(STDIN_FILENO); // 1 if terminal , 0 if stream

	if (is_stream == 0) { // from stream
		// Read input from a stream
		do {
			int num_chars = getline(&line, &size_line, stdin);
			if (num_chars == -1) {
				break;
			}

			// Remove newline character from the end of the line
			if (line[num_chars - 1] == '\n')
				line[num_chars - 1] = '\0';

			words = malloc(sizeof(char *) * 1024);
			if (words == NULL)
				perror("malloc error");

			clean_line = strtok(line, delims);

			/*this part is for splitiing the whole command */
			while (clean_line != NULL) {
				words[i] = clean_line;
				i++;
				clean_line = strtok(NULL, delims);
			}

			words[i] = NULL;

			/*--- */

			// Execute the command
			pid_t my_pid = fork();
			if (my_pid == -1) {
				perror("fork error");
				exit(EXIT_FAILURE);
			}

			if (my_pid == 0) {
				if (words[0] != NULL) {
					if (execve(words[0], words, env) == -1) {
						perror("execve error");
						exit(EXIT_FAILURE);
					}
				} else {
					break;
				}
			} else {
				int status;
				wait(&status);
			}
		} while (num_chars != -1);
	} else { // from terminal
		// Read multiple commands from a stream (piped input)
		while (true) {
			printf("$ ");

			num_chars = getline(&line, &size_line, stdin);

			if (num_chars == -1) {
				perror("getline error");
				break;
			}

			if (line[num_chars - 1] == '\n')
				line[num_chars - 1] = '\0';

			my_pid = fork();
			if (my_pid == -1) {
				perror("fork error");
				exit(EXIT_FAILURE);
			}

			if (my_pid == 0) {
				if (execve(line, argv, env) == -1) {
					perror("execve error");
					exit(EXIT_FAILURE);
				}
			} else
				wait(&status);

			free(line);
			line = NULL;
		}

		free(line);
		return (EXIT_SUCCESS);
	}
}
