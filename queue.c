#define MAX_LENGTH 1000000
#include <stdlib.h>
#include "linkedlist.c"

void printQueue() {

    printAll();
}

void enqueue(int dataToBeInsert) {
    
    if (len() < MAX_LENGTH) {
        insertAtEnd(dataToBeInsert);
    } else {
        printf("Queue overflow!\n");
        exit(-1);
    }
}

int dequeue() {
    
    if (len() > 0) {
        int r = deleteAtBegin();
        return r;
    } else {
        printf("Queue underflow!\n");
        exit(-1);
    }
}

int main() {

    dequeue();
    printQueue();
    enqueue(3);
    enqueue(5);
    enqueue(9);
    enqueue(-1);
    printQueue();
    int r = dequeue();
    printQueue();

    printf("r=%d\n", r);
}
