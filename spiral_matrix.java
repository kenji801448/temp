import java.util.Scanner;
import java.util.Arrays;

public class SpiralMatrix {
    //matrix size
    private int n, m;
    //matrix elements
    private int[][] a;
    //boundary
    private int u, d, l, r;

    private static final Scanner scanner = new Scanner(System.in);

    //movement
    private static int move = 0;

    //right, down, left, up
    private static final int[] x = {0, 1, 0, -1};
    private static final int[] y = {1, 0, -1, 0};
    
    private void fetchInput() {

        n = scanner.nextInt();
        m = scanner.nextInt();
        a = new int[n][m];
        u = l = 0;
        d = n-1;
        r = m-1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                a[i][j] = scanner.nextInt();
            }
        }
    }

    public SpiralMatrix() {

        fetchInput();
        int row = 0, col = 0;
        while (u <= d && l <= r) {
            //echo
            System.out.format("%d ", a[row][col]);

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

    //main function
    public static void main(String[] arg) {

        new SpiralMatrix();
    }
}
