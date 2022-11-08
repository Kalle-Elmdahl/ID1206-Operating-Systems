#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_NUM_MSG 10
#define MAX_SIZE 1024

int main(int argc, char const *argv[])
{
    mqd_t mqd;
    char *my_mq = "/queue";
    struct mq_attr attr;

    pid_t result = fork();

    if (result)
    { // Parent
        char buf[MAX_SIZE];
        attr.mq_maxmsg = MAX_NUM_MSG;
        attr.mq_msgsize = MAX_SIZE / 2;

        mqd = mq_open(my_mq, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH, &attr);

        if (mqd < 0)
        {
            printf("failed to open server fd\n");
            perror("mq_open");
            return -1;
        }

        mq_receive(mqd, buf, MAX_SIZE, NULL);
        char command[100];
        sprintf(command, "echo  \"%s\" | wc -w", buf);
        system(command);
        mq_unlink(my_mq);
        mq_close(mqd);
    }
    else
    { // Child

        char file_buf[MAX_SIZE];
        attr.mq_maxmsg = MAX_NUM_MSG;
        attr.mq_msgsize = MAX_SIZE;
        mqd = mq_open(my_mq, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH, &attr);

        int fd = open("content.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        ssize_t x = read(fd, file_buf, MAX_SIZE);

        // printf("Message: %s\n", file_buf);

        printf("x: %d \n", x);

        int len = mq_send(mqd, file_buf, strlen(file_buf), 0);

        if (len < 0)
        {
            printf("failed to send to the mqueue\n");
            perror("mq_send");
            return -1;
        }
        mq_unlink(my_mq);
        mq_close(mqd);
    }

    return 0;
}