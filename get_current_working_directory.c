#include "shell.h"

char *get_current_working_directory()
{
	static char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		return (cwd);
	}

	else
	{
		return (NULL);
	}
}
