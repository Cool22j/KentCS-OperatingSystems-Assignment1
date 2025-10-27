// Cayden Jones
//Consumer process for Producer-Consumer problem using shared memory and semaphores.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>

#define BUFFER_SIZE 2
#define SHM_NAME "/shared_table"

sem_t *sem_empty;
sem_t *sem_full;
sem_t *sem_mutex;

int *shared_table;

void* consumer_thread(void* arg) {
    int index = 0;

    while (1) {
        sem_wait(sem_full);
        sem_wait(sem_mutex);

        int item = shared_table[index];
        printf("[Consumer] Consumed item: %d from slot %d\n", item, index);
        fflush(stdout);

        index = (index + 1) % BUFFER_SIZE;

        sem_post(sem_mutex);
        sem_post(sem_empty);

        sleep(2);
    }

    return NULL;
}

int main() {
    sleep(1); // Give producer time to initialize shared memory

    // Open existing shared memory
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    shared_table = (int*) mmap(NULL, BUFFER_SIZE * sizeof(int),
                        PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Open semaphores
    sem_empty = sem_open("/sem_empty", 0);
    sem_full  = sem_open("/sem_full", 0);
    sem_mutex = sem_open("/sem_mutex", 0);

    pthread_t consumer;
    pthread_create(&consumer, NULL, consumer_thread, NULL);
    pthread_join(consumer, NULL);

    return 0;
}
