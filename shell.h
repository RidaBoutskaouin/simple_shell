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
#include <stdbool.h>


bool is_absolute_path(const char *path);
void print_error(char **av, int cnt, char *line, bool isabs);
char *get_env(const char *name);
char *full_command(char *user_cmd);
char _getchar(void);
ssize_t _getline(char **line, size_t *lenth, FILE *stream);
char *get_current_working_directory();
void print_env_vars();

char *_strchr(char *str, char c);
char *_strtok(char *str, char *seps);
void print_error_exit(char **av, int cnt, char **words);
int isValidNumber(const char *str);
void handle_exit(int i, char **words, char **av, int cnt, char *line);
char *edge_cases(int num_chars, int status, char *line, char *abs_cmd);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void child_process_terminal(char **words, char *command, char **env, int cnt, char **av, char *line);
char **fill_array(char *clean_line, char *line, char *delims, char **words, int i);

#endif /* SHELL_H */
