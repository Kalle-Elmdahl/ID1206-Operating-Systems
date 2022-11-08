#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    pid_t result = fork();

    if (result)
    { // Parent
        mqd_t mq_open(NULL);
    }
    else
    { // Child
    }
}