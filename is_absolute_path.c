#include "shell.h"



bool is_absolute_path(const char *path) {
	if (path != NULL && path[0] == '/')
		return true;

	return false;
}
