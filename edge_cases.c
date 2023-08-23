#include "shell.h"

char *edge_cases(int num_chars, int status, char *line, char *abs_cmd)
{
    
    if (line[num_chars - 1] == '\n')
        line[num_chars - 1] = '\0';
    
    if (num_chars == -1)
    {
        free(line);
        exit(status >> 8);
    }

    if (strcmp(line, "env") == 0 || strcmp(line, "printenv") == 0)
    {
        print_env_vars();
	free(line);
	line = NULL;
        exit(0);
    }

    if (strcmp(line, "exit") == 0)
    {
        free(line);
        line = NULL;
        exit(status >> 8);
    }

    if ((line[0] == '.' && line[1] == '/') || (line[0] == '.' && line[1] == '.'))
    {
        abs_cmd = malloc(strlen(get_current_working_directory()) + strlen(line) + 2);

        strcpy(abs_cmd, get_current_working_directory());
        strcat(abs_cmd, "/");
        strcat(abs_cmd, line);
        free(line);
        line = NULL;
        line = abs_cmd;
    }
    
    return (line);
}
