#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 4  // must be power of 2 for Strassen

// Traditional Matrix Multiplication
void traditionalMultiply(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

// Strassen’s Algorithm Helper
void add(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Strassen’s Matrix Multiplication (recursive for N=2^k)
void strassen(int A[N][N], int B[N][N], int C[N][N], int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size/2;
    int a11[newSize][newSize], a12[newSize][newSize], a21[newSize][newSize], a22[newSize][newSize];
    int b11[newSize][newSize], b12[newSize][newSize], b21[newSize][newSize], b22[newSize][newSize];
    int c11[newSize][newSize], c12[newSize][newSize], c21[newSize][newSize], c22[newSize][newSize];
    int M1[newSize][newSize], M2[newSize][newSize], M3[newSize][newSize], M4[newSize][newSize], M5[newSize][newSize], M6[newSize][newSize], M7[newSize][newSize];
    int temp1[newSize][newSize], temp2[newSize][newSize];

    // Divide matrices
    for (int i=0; i<newSize; i++) {
        for (int j=0; j<newSize; j++) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j+newSize];
            a21[i][j] = A[i+newSize][j];
            a22[i][j] = A[i+newSize][j+newSize];

            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j+newSize];
            b21[i][j] = B[i+newSize][j];
            b22[i][j] = B[i+newSize][j+newSize];
        }
    }

    // M1 = (a11+a22)(b11+b22)
    add(a11, a22, temp1);
    add(b11, b22, temp2);
    strassen(temp1, temp2, M1, newSize);

    // M2 = (a21+a22)b11
    add(a21, a22, temp1);
    strassen(temp1, b11, M2, newSize);

    // M3 = a11(b12-b22)
    subtract(b12, b22, temp2);
    strassen(a11, temp2, M3, newSize);

    // M4 = a22(b21-b11)
    subtract(b21, b11, temp2);
    strassen(a22, temp2, M4, newSize);

    // M5 = (a11+a12)b22
    add(a11, a12, temp1);
    strassen(temp1, b22, M5, newSize);

    // M6 = (a21-a11)(b11+b12)
    subtract(a21, a11, temp1);
    add(b11, b12, temp2);
    strassen(temp1, temp2, M6, newSize);

    // M7 = (a12-a22)(b21+b22)
    subtract(a12, a22, temp1);
    add(b21, b22, temp2);
    strassen(temp1, temp2, M7, newSize);

    // c11 = M1+M4-M5+M7
    for (int i=0; i<newSize; i++)
        for (int j=0; j<newSize; j++)
            c11[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];

    // c12 = M3+M5
    for (int i=0; i<newSize; i++)
        for (int j=0; j<newSize; j++)
            c12[i][j] = M3[i][j] + M5[i][j];

    // c21 = M2+M4
    for (int i=0; i<newSize; i++)
        for (int j=0; j<newSize; j++)
            c21[i][j] = M2[i][j] + M4[i][j];

    // c22 = M1-M2+M3+M6
    for (int i=0; i<newSize; i++)
        for (int j=0; j<newSize; j++)
            c22[i][j] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];

    // Combine results
    for (int i=0; i<newSize; i++) {
        for (int j=0; j<newSize; j++) {
            C[i][j] = c11[i][j];
            C[i][j+newSize] = c12[i][j];
            C[i+newSize][j] = c21[i][j];
            C[i+newSize][j+newSize] = c22[i][j];
        }
    }
}

// Print Matrix
void printMatrix(int M[N][N]) {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++)
            printf("%d ", M[i][j]);
        printf("\n");
    }
}

int main() {
    int A[N][N] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    int B[N][N] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    int C1[N][N], C2[N][N];

    clock_t start, end;
    double timeTraditional, timeStrassen;

    // Traditional
    start = clock();
    traditionalMultiply(A, B, C1);
    end = clock();
    timeTraditional = (double)(end-start)/CLOCKS_PER_SEC;

    // Strassen
    start = clock();
    strassen(A, B, C2, N);
    end = clock();
    timeStrassen = (double)(end-start)/CLOCKS_PER_SEC;

    printf("Result using Traditional Multiplication:\n");
    printMatrix(C1);

    printf("\nResult using Strassen’s Multiplication:\n");
    printMatrix(C2);

    printf("\nPerformance:\n");
    printf("Traditional Time: %f sec\n", timeTraditional);
    printf("Strassen Time:   %f sec\n", timeStrassen);

    return 0;
}
