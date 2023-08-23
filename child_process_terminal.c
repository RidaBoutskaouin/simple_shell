#include "shell.h"

void child_process_terminal(char **words, char *command, char **env,
                            int cnt, char **av, char *line)
{
    bool isabs_f;
  
    if (words[0] != NULL)
    {
        isabs = is_absolute_path(words[0]);
        if (isabs == false)
        {
            command = full_command(words[0]);
            if (command != NULL)
            {
                if (execve(command, words, env) == -1)
                    exit(2);
            }
            else
            {
                write(STDERR_FILENO, av[0], strlen(av[0]));
                write(STDERR_FILENO, ": ", 2);
                write(STDERR_FILENO, line, strlen(line));
                write(STDERR_FILENO, ": command not found\n", 20);
                exit(127);
            }
        }
        else
        {
            command = words[0];
            if (command != NULL)
            {
                if (execve(command, words, env) == -1)
                {
                    if (errno == ENOENT)
                    {
                        write(STDERR_FILENO, av[0], strlen(av[0]));
                        write(STDERR_FILENO, ": ", 2);
                        write(STDERR_FILENO, line, strlen(line));
                        write(STDERR_FILENO, ": No such file or directory\n", 28);
                        exit(127);
                    }
                }
            }
            else
            {
                print_error(av, cnt, line, isabs);
                exit(127);
            }
        }
    }
    else
    {
        exit(0);
    }
}
