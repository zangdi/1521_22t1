#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_LEN 1024

void *thread_run(void *data) {
    while (1) {
        printf("feed me input!\n");
        sleep(1);
    }

    return 0;
}

int main(void) {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_run, NULL);

    char line[MAX_LEN];
    while (fgets(line, MAX_LEN, stdin)) {
        printf("you entered: %s", line);
    }

    pthread_cancel(thread);

    return 0;
}
