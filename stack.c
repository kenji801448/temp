#define MAX_LENGTH 1000000
#include <stdlib.h>
#include "array.c"
int top = -1;

void printStack() {

    printAll();
}

void push(int dataToBeInsert) {
    
    if (top < MAX_LENGTH-1) {
        top++;
        insertAtIndex(dataToBeInsert, top);
    } else {
        printf("Stack overflow!\n");
        exit(-1);
    }
}

int pop() {
    
    if (top >= 0) {
        int r = deleteIndex(top);
        top--;
        return r;
    } else {
        printf("Stack underflow!\n");
        exit(-1);
    }
}
