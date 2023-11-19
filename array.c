#include <stdio.h>

int array[1000000];
int length = 0;

void printAll() {

    printf("[");
    for (int i = 0; i < length; i++) {
        printf(" %d ", array[i]);
    }
    printf("]\n");
}

void insertAtIndex(int dataToBeInsert, int index) {
    
    for (int i = length; i > index; i--) {
        array[i] = array[i-1];
    }
    array[index] = dataToBeInsert;
    length++;
}

void insertAtBegin(int dataToBeInsert) {

    insertAtIndex(dataToBeInsert, 0);
}

void insertAtEnd(int dataToBeInsert) {

    insertAtIndex(dataToBeInsert, length);
}

int deleteIndex(int index) {

    int r = array[index];
    for (int i = index; i < length-1; i++) {
        array[i] = array[i+1];
    }
    length--;
    return r;
}

int deleteAtBegin() {

    return deleteIndex(0);
}

int deleteEnd() {

    return deleteIndex(length-1);
}

int len() {

    return length;
}
