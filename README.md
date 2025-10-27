# KentCS-OperatingSystems-Assignment1

#Description

This project demonstrates synchronization between two independent processes (a producer and a consumer) using:

POSIX shared memory (shm_open)

POSIX semaphores (sem_open)

Threads for concurrency inside each program.

The producer generates items and stores them in a shared table. The consumer retrieves items. Synchronization ensures that:

The table never overflows (max 2 items).

The consumer never reads empty slots.

Both programs respect mutual exclusion when accessing shared memory.

#How to Build/Run

In a Unix/Linux based terminal, enter the following commands in the directory of the files.

gcc producer.c -pthread -lrt -o producer
gcc consumer.c -pthread -lrt -o consumer

After producing the executables, enter this command to run it

./producer & ./consumer &

