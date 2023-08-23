#include "shell.h"

void child_process_terminal(char **words, char *command, char **env,
                            int cnt, char **av, char *line)
{
    bool isabs_f;
    ssize_t bytes_written;
  
    if (words[0] != NULL)
    {
        isabs_f = is_absolute_path(words[0]);
        if (isabs_f == false)
        {
            command = full_command(words[0]);
            if (command != NULL)
            {
                if (execve(command, words, env) == -1)
                    exit(2);
            }
            else
            {
                bytes_written = write(STDERR_FILENO, av[0], strlen(av[0]));
                bytes_written = write(STDERR_FILENO, ": ", 2);
                bytes_written = write(STDERR_FILENO, line, strlen(line));
                bytes_written = write(STDERR_FILENO, ": command not found\n", 20);
                if (bytes_written == -1)
                {};
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
                        bytes_written = write(STDERR_FILENO, av[0], strlen(av[0]));
                        bytes_written = write(STDERR_FILENO, ": ", 2);
                        bytes_written = write(STDERR_FILENO, line, strlen(line));
                        bytes_written = write(STDERR_FILENO, ": No such file or directory\n", 28);
                        if (bytes_written == -1)
                        {};
                        exit(127);
                    }
                }
            }
            else
            {
                print_error(av, cnt, line, isabs_f);
                exit(127);
            }
        }
    }
    else
    {
        exit(0);
    }
}
