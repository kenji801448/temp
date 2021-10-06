#include <stdio.h>
#define MAXIMUM_SIZE 5000

int main(void) {
    
    int n, m;
    int a[MAXIMUM_SIZE];

    //fetch input
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i*m+j]);
        }
    }

    //movement
    int move = 0;
    //right, down, left, up
    int x[4] = {0, 1, 0, -1}; 
    int y[4] = {1, 0, -1, 0}; 
    
    //u upward boundary
    //d downward boundary
    //l leftward boundary
    //r rightward boundary
    int u = 0, d = n-1, l = 0, r = m-1; 

    int row = 0, col = 0;

    while (u <= d && l <= r) {
        //echo
        printf("%d ", a[row*m+col]);

        //move forward
        row += x[move];
        col += y[move];
        
        //check if out of boundary
        if (col > r || row > d || col < l || row < u) {
            //shrink boundary
            if (col > r)
                u++;
            else if (row > d)
                r--;
            else if (col < l)
                d--;
            else
                l++;

            //undo
            row -= x[move];
            col -= y[move];

            //turn
            move = (move + 1) % 4;

            //move forward again
            row += x[move];
            col += y[move];
        }
    }
}
