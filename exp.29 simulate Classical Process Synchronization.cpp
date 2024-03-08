#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
sem_t empty, full, mutex;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
void sleep_ms(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}
void *producer(void *arg) {
    int item;
    for (int i = 0; i < 5; ++i) {
        item = rand() % 100; 
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = item;
        printf("Producer produced item %d at position %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&full);
        sleep_ms(100);
    }
    pthread_exit(NULL);
}
void *consumer(void *arg) {
    int item;
    for (int i = 0; i < 5; ++i) {
        sem_wait(&full);
        sem_wait(&mutex);
        item = buffer[out];
        printf("Consumer consumed item %d from position %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&empty);
        sleep_ms(150);
    }
    pthread_exit(NULL);
}
int main() {
    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_create(&producer_threads[i], NULL, producer, NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_join(producer_threads[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_join(consumer_threads[i], NULL);
    }
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    return 0;
}

