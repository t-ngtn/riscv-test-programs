#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 64
#define ITERATIONS 10

void matrix_multiply(int mat1[][MATRIX_SIZE], int mat2[][MATRIX_SIZE], int result[][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

int main() {
    printf("Matrix Multiplication Test (Short Version)\n");
    printf("Matrix size: %dx%d\n", MATRIX_SIZE, MATRIX_SIZE);
    printf("Iterations: %d\n\n", ITERATIONS);
    
    static int mat1[MATRIX_SIZE][MATRIX_SIZE];
    static int mat2[MATRIX_SIZE][MATRIX_SIZE];
    static int result[MATRIX_SIZE][MATRIX_SIZE];
    
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            mat1[i][j] = i + j;
            mat2[i][j] = i - j;
        }
    }
    
    for (int iter = 0; iter < ITERATIONS; iter++) {
        matrix_multiply(mat1, mat2, result);
        printf("Completed iteration %d\n", iter);
    }
    
    printf("\nMatrix multiplication completed %d times\n", ITERATIONS);
    printf("Sample results:\n");
    printf("  result[0][0]: %d\n", result[0][0]);
    printf("  result[31][31]: %d\n", result[31][31]);
    printf("  result[63][63]: %d\n", result[63][63]);
    
    return 0;
}