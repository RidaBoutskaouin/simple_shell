#include "shell.h"


char *get_env(const char *name) {
	int i = 0;
	char *var;
	char *ret;

	extern char **environ;

	while (environ[i] != NULL) {
		var = strtok(environ[i], "=");
		if (strcmp(name, var) == 0) {
			ret = strtok(NULL, "\n");
			return (ret);
		}

		i++;
	}

	return (NULL);
}

