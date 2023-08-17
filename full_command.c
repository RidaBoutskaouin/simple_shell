#include "shell.h"


char *full_command(char *user_cmd) {
	char *path, *full_command = NULL, *tmp_command = NULL, *part;
	size_t size;
	struct stat bf;

	path = get_env("PATH");
	part = strtok(path, ":");

	while (part != NULL) {
		size = strlen(part) + strlen(user_cmd) + 2;
		tmp_command = malloc(size);

		if (tmp_command == NULL)
			perror("malloc error");

		stpcpy(tmp_command, part);
		strcat(tmp_command, "/");
		strcat(tmp_command, user_cmd);

		if (stat(tmp_command, &bf) == 0) {
			full_command = tmp_command;
			break;
		} else {
			free(tmp_command);
		}

		part = strtok(NULL, ":");
	}

	return (full_command);
}

