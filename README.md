# KentCS-OperatingSystems-Assignment1

# Description

This program simulates two processes; a producer and a consumer, that share a small table where data items are stored.
A shared memory buffer is first made that both proccesses can access, The producer then puts items on the table inside that buffer, and the consumer takes them off. The table can only hold two items at a time, so both programs must take turns safely.

# How to Build/Run

In a Unix/Linux based terminal, enter the following commands making sure you are in the corerct directory

**gcc producer.c -pthread -lrt -o producer**
**gcc consumer.c -pthread -lrt -o consumer**

After producing the executables, enter this command to run them together

./producer & ./consumer &

