//Cayden Jones
//Producer process for Producer-Consumer problem using shared memory and semaphores.

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

void* producer_thread(void* arg) {
    int item = 1;
    int index = 0;

    while (1) {
        sem_wait(sem_empty);
        sem_wait(sem_mutex);

        shared_table[index] = item;
        printf("[Producer] Produced item: %d at slot %d\n", item, index);
        fflush(stdout);

        index = (index + 1) % BUFFER_SIZE;
        item++;

        sem_post(sem_mutex);
        sem_post(sem_full);

        sleep(1);
    }

    return NULL;
}

int main() {
    // Create shared memory
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, BUFFER_SIZE * sizeof(int));
    shared_table = (int*) mmap(NULL, BUFFER_SIZE * sizeof(int),
                        PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Initialize semaphores
    sem_empty = sem_open("/sem_empty", O_CREAT, 0666, BUFFER_SIZE);
    sem_full  = sem_open("/sem_full",  O_CREAT, 0666, 0);
    sem_mutex = sem_open("/sem_mutex", O_CREAT, 0666, 1);

    pthread_t producer;
    pthread_create(&producer, NULL, producer_thread, NULL);
    pthread_join(producer, NULL);

    return 0;
}
