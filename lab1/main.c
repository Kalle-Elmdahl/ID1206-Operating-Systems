#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int BUFFER_SIZE = 25;
char write_msg[BUFFER_SIZE] = "Hello";
char read_msg[BUFFER_SIZE] = "World!";

int main(int argc, char const *argv[])
{
    int fd[2];
    // fd[0] read
    // fd[1] write

    pipe(fd);
    pid_t result = fork();

    if (result)
    { // Parent
        close(fd[1]);
        read(fd[0], read_msg, BUFFER_SIZE);
        printf("\n\n");
        for (int i = 0; i < BUFFER_SIZE; i++)
            printf("%c", read_msg[i]);

        printf("\n\n");
        wait(NULL);
    }
    else
    { // Child
        close(fd[0]);
        write(fd[1], write_msg, BUFFER_SIZE);
        // int test = system("ls /");
        // printf("I am child: %d\n", test);
    }

    return 0;
}