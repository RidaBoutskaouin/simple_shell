#ifndef MAIN_H
#define MAIN_H

bool is_absolute_path(const char *path);
char *get_env(const char *name);
char *full_command(char *user_cmd);

#endif
