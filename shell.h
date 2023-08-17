#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

bool is_absolute_path(const char *path);
char *get_env(const char *name);
char *full_command(char *user_cmd);
char _getchar(void);
ssize_t _getline(char **line, size_t *lenth, FILE *stream);
char *get_current_working_directory();

#endif
