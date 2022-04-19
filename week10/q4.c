#include <stdio.h>
#include <pthread.h>

void *thread_run(void *data) {
    char *string = data;

    while (1) {
        printf("%s\n", string);
    }

    return NULL;
}

int main(void) {
    // create a thread
    pthread_t thread;
    char *there = "there!";
    pthread_create(&thread, NULL, thread_run, there);

    pthread_t thread2;
    char *world = "world";
    pthread_create(&thread2, NULL, thread_run, world);

    // print out hello infinitely
    while (1) {
        printf("Hello\n");
    }
}
