#include "shell.h"

char **fill_array(char *clean_line, char *line, char *delims, char **words, int i)
{
    clean_line = strtok(line, delims);
    while (clean_line != NULL)
    {
        words[i] = clean_line;
        i++;
        clean_line = strtok(NULL, delims);
    }
    words[i] = NULL;

    return (words);
}
