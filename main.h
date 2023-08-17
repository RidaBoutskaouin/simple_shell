#ifndef MAIN_H
#define MAIN_H

bool is_absolute_path(const char *path);
char *get_env(const char *name);
char *full_command(char *user_cmd);
char _getchar(void);
ssize_t _getline(char **line, size_t *lenth, FILE *stream);
char *get_current_working_directory();

#endif
