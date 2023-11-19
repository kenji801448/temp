//edit from https://www.tutorialspoint.com/data_structures_algorithms/linked_list_algorithms.htm
#include <stdio.h>
#include <stdlib.h>

struct node {

    int data;
    struct node* next;
};
struct node* head = NULL;
struct node* previous = NULL;
struct node* this = NULL;
struct node* newNode = NULL;

void printAll() {

    printf("[");
    for (this = head; this; this = this->next) {
        printf(" %d ", this->data);
    }
    printf("]\n");
}

void insertAtBegin(int dataToBeInsert) {

    newNode = (struct node*) malloc(sizeof(struct node));
    newNode->data = dataToBeInsert;
    newNode->next = head;
    head = newNode;
}

void moveToNext() {

    if (this == NULL) {
        printf("The length of the linked list is smaller than index, that's not how it works!\n");
        exit(-1);
    }
    previous = this;
    this = this->next;
}

void moveToIndex(int index) {

    previous = NULL;
    this = head;
    for (int i = 0; i < index; i++) {
        moveToNext();
    }
}

void insertAtIndex(int dataToBeInsert, int index) {
//the length of the list, must larger than index
    
    if (index == 0)
        insertAtBegin(dataToBeInsert);
    else {
        moveToIndex(index);
        newNode = (struct node*) malloc(sizeof(struct node));
        newNode->data = dataToBeInsert;
        newNode->next = this;
        previous->next = newNode;
    }
}

int len() {

    int count = 0;
    for (this = head ; this; this = this->next)
        count++;
    return count;
}

void insertAtEnd(int dataToBeInsert) {

    insertAtIndex(dataToBeInsert, len());
}

int deleteAtBegin() {

    int r;
    r = head->data;
    this = head;
    head = head->next;
    free(this);

    return r;
}

int deleteIndex(int index) {
    
    int r;
    if (index == 0) {
        return deleteAtBegin();
    }
    moveToIndex(index);
    r = this->data;
    previous->next = this->next;
    free(this);

    return r;
}

int deleteEnd() {
    
    return deleteIndex(len()-1);
}
