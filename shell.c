#include "shell.h"


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

	char *line = NULL, *clean_line, delims[] = " \t\n", **words = NULL,
	*command = NULL;

	char *abs_cmd = NULL;

	size_t size_line = 0;
	int num_chars = 0, status = 0, i = 0, cnt = 0;
	pid_t my_pid;

	bool is_stream = isatty(STDIN_FILENO); /* 1 if terminal, 0 if stream */

	if (is_stream == 0) {
		/* from stream 
		   Read input from a stream */
		do {
			num_chars = getline(&line, &size_line, stdin);
			if (num_chars == -1) {
				break;
			}

			if (strcmp(line, "env\n") == 0) {
				print_env_vars();
				exit(0);
			}

			if (strcmp(line, "exit\n") == 0)
				exit(status >> 8);

			if ((line[0] == '.' && line[1] == '/') || (line[0] == '.' && line[1] == '.')) {
				abs_cmd = malloc(strlen(get_current_working_directory()) + strlen(line) + 1);
				strcpy(abs_cmd, get_current_working_directory());
				strcat(abs_cmd, "/");
				strcat(abs_cmd, line);
				free(line);
				line = abs_cmd;
			}

			/* Remove newline character from the end of the line */
			if (line[num_chars - 1] == '\n')
				line[num_chars - 1] = '\0';

			words = malloc(sizeof(char *) * 1024);
			if (words == NULL)
				perror("malloc error");

			/*this part is for splitiing the whole command */
			clean_line = strtok(line, delims);
			while (clean_line != NULL) {
				words[i] = clean_line;
				i++;
				clean_line = strtok(NULL, delims);
			}
			words[i] = NULL;
			/*--- */

			/* fork */
			pid_t my_pid = fork();
			if (my_pid == -1) {
				perror("fork error");
				exit(EXIT_FAILURE);
			}

			if (my_pid == 0) {
				if (words[0] != NULL) {
					bool isabs = is_absolute_path(words[0]);
					if (isabs == false) {
						command = full_command(words[0]);
						if (command != NULL) {
							if (execve(command, words, env) == -1)
								exit(2);
							cnt = cnt + 1;
						} else {
							// printf("%s: line %i: %s: ", av[0], cnt, line); sh: line 1: envsa: command not found

							write(STDERR_FILENO, av[0], strlen(av[0]));
							write(STDERR_FILENO, ": line ", 7);
							char count_str = cnt + '0';
							write(STDERR_FILENO, &count_str, 1);
							write(STDERR_FILENO, ": ", 2);
							write(STDERR_FILENO, line, strlen(line));
							write(STDERR_FILENO, ": ", 2);
							perror("");
							exit(127);
						}
					} else {
						command = words[0];
						if (command != NULL) {
							if (execve(command, words, env) == -1)
								exit(2);
							// exit_status = 0;
							cnt++;
						} else {
							// printf("%s: line %i: %s: ", av[0], cnt, line);
							write(STDERR_FILENO, av[0], strlen(av[0]));
							write(STDERR_FILENO, ": line ", 7);
							char count_str = cnt + '0';
							write(STDERR_FILENO, &count_str, 1);
							write(STDERR_FILENO, ": ", 2);
							write(STDERR_FILENO, line, strlen(line));
							write(STDERR_FILENO, ": ", 2);
							perror("");
							exit(127);

						}
					}
				} else {
					break;
				}
			} else {
				wait(&status);
				free(words);
				free(command);
				i = 0;
			}
		} while (num_chars != -1);
	} else {
		// from terminal
		// Read multiple commands from a stream (piped input)
		while (true) {
			write(1, "$ ", 2);

			num_chars = getline(&line, &size_line, stdin);

			if (num_chars == -1) {
				perror("getline error");
				break;
			}

			if (strcmp(line, "exit\n") == 0)
			{
				free(line);
				exit(0);
			}

			if (strcmp(line, "env\n") == 0) {
				print_env_vars();
				exit(0);
			}

			if (line[0] == '.' && line[1] == '/') {
				abs_cmd = malloc(strlen(get_current_working_directory()) + strlen(line) + 1);
				strcpy(abs_cmd, get_current_working_directory());
				strcat(abs_cmd, "/");
				strcat(abs_cmd, line);
				free(line);
				line = abs_cmd;
			}

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
			my_pid = fork();
			if (my_pid == -1) {
				perror("fork error");
				exit(EXIT_FAILURE);
			}

			if (my_pid == 0) {
				if (words[0] != NULL) {
					bool isabs = is_absolute_path(words[0]);
					if (isabs == false) {
						command = full_command(words[0]);
						if (command != NULL) {
							execve(command, words, env);
							exit(EXIT_SUCCESS);
						} else {
							perror("Command Not Found!");
							exit(EXIT_FAILURE);
						}
					} else {
						command = words[0];
						if (command != NULL) {
							execve(command, words, env);
							exit(EXIT_SUCCESS);
						} else {
							perror("Command Not Found!");
							exit(EXIT_FAILURE);
							break;
						}
					}
				} else {
					break;
				}
			} else {
				wait(&status);
				free(words);
				// free(command);
				free(line);
				// free(abs_cmd);
				i = 0;
			}

			line = NULL;
			words = NULL;
			abs_cmd = NULL;
		}

		free(line);
	}

	return (EXIT_SUCCESS);
}
