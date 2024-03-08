#include <stdio.h>
#include <pthread.h>
void *printMessage(void *message) {
    printf("Thread says: %s\n", (char *)message);
    pthread_exit(NULL);
}
void *printNumbers(void *arg) {
    int *limit = (int *)arg;
    for (int i = 1; i <= *limit; ++i) {
        printf("%d ", i);
    }
    printf("\n");
    pthread_exit(NULL);
}
int main() {
    pthread_t thread1, thread2;
    char message[] = "Hello from the thread!";
    if (pthread_create(&thread1, NULL, printMessage, (void *)message) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    int limit = 5;
    if (pthread_create(&thread2, NULL, printNumbers, (void *)&limit) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    if (pthread_equal(thread1, thread2)) {
        printf("Threads are equal\n");
    } else {
        printf("Threads are not equal\n");
    }
    pthread_exit(NULL);
    return 0;
}

