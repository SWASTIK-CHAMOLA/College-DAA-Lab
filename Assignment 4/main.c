#include <stdio.h>
#include <limits.h>

// Function to print the optimal parenthesis placement
void printParenthesis(int i, int j, int n, int bracket[n][n], char *name) {
    if (i == j) {
        printf("%c", (*name)++);
        return;
    }
    printf("(");
    printParenthesis(i, bracket[i][j], n, bracket, name);
    printParenthesis(bracket[i][j] + 1, j, n, bracket, name);
    printf(")");
}

// Matrix Chain Multiplication using Dynamic Programming
void matrixChainOrder(int p[], int n) {
    int m[n][n];       // m[i][j] = minimum number of multiplications needed
    int bracket[n][n]; // To store the position of split

    // Cost is 0 when multiplying one matrix
    for (int i = 1; i < n; i++)
        m[i][i] = 0;

    // L is the chain length
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    bracket[i][j] = k;
                }
            }
        }
    }

    printf("Minimum number of multiplications is: %d\n", m[1][n - 1]);
    printf("Optimal Parenthesization is: ");
    char name = 'A';
    printParenthesis(1, n - 1, n, bracket, &name);
    printf("\n");
}

int main() {
    // Example: 4 matrices with dimensions
    // A1 = 10x20, A2 = 20x30, A3 = 30x40, A4 = 40x30
    int arr[] = {10, 20, 30, 40, 30};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Matrix dimensions: ");
    for (int i = 0; i < n - 1; i++)
        printf("A%d(%dx%d) ", i + 1, arr[i], arr[i + 1]);
    printf("\n\n");

    matrixChainOrder(arr, n);

    return 0;
}
