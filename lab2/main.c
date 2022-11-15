#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int buffer = 0;
pthread_mutex_t lock;
void *thread_func() {
    int *modifications = malloc(sizeof(int));
    for (*modifications = 0; pthread_mutex_lock(&lock) || buffer < 15; (*modifications)++, buffer++, pthread_mutex_unlock(&lock))
        printf("TID: %d\t PID: %d\t Buffer: %d\n", (int)pthread_self(), getpid(), buffer);
    pthread_mutex_unlock(&lock);
    return (void *)modifications;
}
int main() {
    pthread_t threads[3];
    pthread_mutex_init(&lock, NULL);
    for (int i = 0; i < 3; pthread_create(&threads[i++], NULL, thread_func, NULL));
    for (int i = 0, *mod; i < 3; printf("TID %d worked on the buffer %d times\n", (int)threads[i++], *mod))
        pthread_join(threads[i], (void **)&mod);
    return 0;
}