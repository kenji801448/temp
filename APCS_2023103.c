//edit from https://www.programiz.com/dsa/graph-adjacency-list
//reference https://web.ntnu.edu.tw/~algo/Graph.html
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 500
#define MAX_LENGTH MAX_SIZE*MAX_SIZE
#define DEBUG 0

int array[MAX_LENGTH];
int length = 0;

//starting of implement stack by array
void push(int dataToBeInsert) {
    
    if (length < MAX_LENGTH) {
        array[length] = dataToBeInsert;
        length++;
    } else {
        printf("Stack overflow!\n");
        exit(-1);
    }
}

int pop() {
    
    if (length > 0) {
        length--;
        int r = array[length];
        return r;
    } else {
        printf("Stack underflow!\n");
        exit(-1);
    }
}
//ending of implement stack by array

struct node {
    int vertex;
    struct node* next;
};

struct node* newNode = NULL;
struct node* this = NULL;

struct graph {
    int numberOfVertex;
    struct node** adjacencyLists;
};

struct graph* createAGraph(int numberOfVertex) {
    
    struct graph* graph = malloc(sizeof(struct graph));
    graph->numberOfVertex = numberOfVertex;
    graph->adjacencyLists = malloc(numberOfVertex * sizeof(struct node*));
    for (int i = 0; i < numberOfVertex; i++)
        graph->adjacencyLists[i] = NULL;
    return graph;
}

struct node* createNode(int vertex) {
    
    newNode = malloc(sizeof(struct node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct graph* graph, int s, int d) {

    newNode = createNode(d);
    newNode->next = graph->adjacencyLists[s];
    graph->adjacencyLists[s] = newNode;

    newNode = createNode(s);
    newNode->next = graph->adjacencyLists[d];
    graph->adjacencyLists[d] = newNode;
}

int n, m;

int id(int i, int j) {
    
    return i*m+j;
}

char c[MAX_SIZE][MAX_SIZE];
int u[MAX_SIZE][MAX_SIZE] = {0};
int d[MAX_SIZE][MAX_SIZE] = {0};
int l[MAX_SIZE][MAX_SIZE] = {0};
int r[MAX_SIZE][MAX_SIZE] = {0};
int visit[MAX_SIZE*MAX_SIZE] = {0};

void printVisit() {

    printf("Visit:");
    for (int i = 0; i < n*m; i++) {
        if (i % m == 0) {
            printf("\n");
        }
        printf("%d ", visit[i]);
    }
    printf("\n");
}

int count;

int main() {

    //initial start
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            while((c[i][j] = getchar()) == '\n') {
            }
            switch (c[i][j]) {
                case 'F':
                    r[i][j] = 1;
                    d[i][j] = 1;
                    break;
                case 'H':
                    l[i][j] = 1;
                    r[i][j] = 1;
                    break;
                case '7':
                    l[i][j] = 1;
                    d[i][j] = 1;
                    break;
                case 'I':
                    u[i][j] = 1;
                    d[i][j] = 1;
                    break;
                case 'X':
                    u[i][j] = 1;
                    d[i][j] = 1;
                    l[i][j] = 1;
                    r[i][j] = 1;
                    break;
                case 'L':
                    r[i][j] = 1;
                    u[i][j] = 1;
                    break;
                case 'J':
                    l[i][j] = 1;
                    u[i][j] = 1;
                    break;
            }
        }
    }
    //initial end
    
    struct graph* graph = createAGraph(n*m);

    //connect horizontal edges
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j < m-1 && r[i][j] && l[i][j+1]) {
                addEdge(graph, id(i, j), id(i, j+1));
            }
        }
    }

    //connect vertical edges
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            if (i < n-1 && d[i][j] && u[i+1][j]) {
                addEdge(graph, id(i, j), id(i+1, j));
            }
        }
    }

    if (DEBUG) {
        for (int i = 0; i < graph->numberOfVertex; i++) {
            printf("node %d", i);
            for (this = graph->adjacencyLists[i]; this; this = this->next) {
                printf(" -> %d", this->vertex);
            }
            printf("\n");
        }
    }

    //dfs traversal using stack
    int max = 0;
    for (int i = 0; i < n*m; i++) {
        if (!visit[i]) {
            push(i);
            visit[i] = 1;

            for (count = 0; length > 0; count++) { //stack is not empty
                int r = pop();
                //traversal all adjacency nodes of node r
                for (this = graph->adjacencyLists[r]; this; this = this->next) {
                    if (!visit[this->vertex]) { //has not been visited yet
                        push(this->vertex);
                        visit[this->vertex] = 1;
                    }
                }
            }
            //new max is the bigger one between count and old max
            max = max < count ? count : max;
        }
    }

    if (DEBUG) {
        printVisit();
    }

    printf("%d\n", max);
}
