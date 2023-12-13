#include <stdio.h>
#define MAXLEN 3000000
#define DEBUG 0

int n, m;
int data[MAXLEN], left[MAXLEN], right[MAXLEN], parent[MAXLEN];
int goods[10000];

void printNode(int i) {

    printf("node %d:[data=%d, left=%d, right=%d, parent=%d]\n", i, data[i], left[i], right[i], parent[i]);
}

int main () {
    
    //initial start
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n*2; i++) {
        data[i] = left[i] = right[i] = parent[i] = 0;
    }
    for (int i = n; i < n*2; i++) {
        scanf("%d", &data[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &goods[i]);
    }
    for (int i = 1; i < n; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        parent[b] = a;
        parent[c] = a;
        left[a] = b;
        right[a] = c;
    }
    for (int i = 0; i < n*2; i++) {
        if (DEBUG) {
            printNode(i);
        }
    }
    for (int i = n; i < n*2; i++) {
        int child = i;
        int d = data[child];
        int p = parent[i];
        for (; p > 0; child = p, p = parent[p]) {
            data[p] += d;
        }
    }
    //initial end

    for (int i = 0; i < m; i++) {
        int current = 1;
        data[current] += goods[i];
        while (left[current] != 0 || right[current] != 0) {
            if (data[left[current]] <= data[right[current]]) {
                current = left[current];
            } else {
                current = right[current];
            }
            data[current] += goods[i];
        }
        printf("%d ", current);
    }

    if (DEBUG) {
        printf("\n");
    }
    for (int i = 0; i < n*2; i++) {
        if (DEBUG) {
            printNode(i);
        }
    }
}
