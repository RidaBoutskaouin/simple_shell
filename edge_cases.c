#include "shell.h"

char *edge_cases(int num_chars, int status, char *line, char *abs_cmd)
{
    if (num_chars == -1)
    {
        exit(status >> 8);
    }

    if (strcmp(line, "env\n") == 0)
    {
        print_env_vars();
        exit(0);
    }

    if (strcmp(line, "exit\n") == 0)
    {
        free(line);
        exit(status >> 8);
    }

    if ((line[0] == '.' && line[1] == '/') || (line[0] == '.' && line[1] == '.'))
    {
        abs_cmd = malloc(strlen(get_current_working_directory()) + strlen(line) + 1);
        strcpy(abs_cmd, get_current_working_directory());
        strcat(abs_cmd, "/");
        strcat(abs_cmd, line);
        free(line);
        line = abs_cmd;
    }

    if (line[num_chars - 1] == '\n')
        line[num_chars - 1] = '\0';
    
    return (line);
}
