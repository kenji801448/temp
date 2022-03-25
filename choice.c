#include <stdio.h>
#define NUMBER_OF_CATEGORY 7
#define ROW NUMBER_OF_CATEGORY
#define COLUMN 3

int count = 0;
int choice[ROW][COLUMN] = {
    {0, 1, 2},
    {0, 1, -1},
    {0, 1, 2},
    {0, 1, -1},
    {0, 2, -1},
    {0, 1, -1},
    {0, 1, -1}
};

void printMatrix() {

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if (choice[i][j] >= 0) {
                printf("%d ", choice[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {

    printMatrix();
    int target_sum = 8;
    int a[ROW];
    for (a[0] = 0; a[0] < COLUMN; a[0]++) {
        for (a[1] = 0; a[1] < COLUMN; a[1]++) {
            for (a[2] = 0; a[2] < COLUMN; a[2]++) {
                for (a[3] = 0; a[3] < COLUMN; a[3]++) {
                    for (a[4] = 0; a[4] < COLUMN; a[4]++) {
                        for (a[5] = 0; a[5] < COLUMN; a[5]++) {
                            for (a[6] = 0; a[6] < COLUMN; a[6]++) {
                                int sum = 0;
                                int ignore = 0;
                                for (int i = 0; i < ROW; i++) {
                                    if (choice[i][a[i]] < 0) {
                                        ignore = 1;
                                        break;
                                    }
                                    sum += choice[i][a[i]];
                                }
                                if (!ignore) {
                                    if (sum == target_sum) {
                                        count++;
                                        for (int i = 0; i < ROW; i++) {
                                            printf("%d", choice[i][a[i]]);
                                        }
                                        printf("\n");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    printf("\n");
    printf("count=%d\n", count);
}
