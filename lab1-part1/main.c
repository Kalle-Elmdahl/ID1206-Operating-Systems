#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    char *ls_args[] = {"ls", "/", NULL};
    char *wc_args[] = {"wc", "-l", NULL};

    int fd[2];
    // fd[0] read
    // fd[1] write

    pipe(fd);
    pid_t result = fork();

    if (result)
    { // Parent
        // Close unused write pipe-end
        close(fd[1]);

        // Redirect standard input with read pipe-end
        dup2(fd[0], 0);

        // Execute command wc
        execvp("wc", wc_args);
    }
    else
    { // Child

        // Close unsused read pipe-end
        close(fd[0]);

        // Redirect standard output to write pipe-end
        dup2(fd[1], 1);

        // Execute command ls
        execvp("ls", ls_args);
    }

    return 0;
}