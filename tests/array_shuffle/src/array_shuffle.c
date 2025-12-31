#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1024
#define ITERATIONS 100

void array_shuffle(int *arr, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int main() {
    printf("Array Shuffle Test\n");
    printf("Array size: %d\n", ARRAY_SIZE);
    printf("Iterations: %d\n\n", ITERATIONS);
    
    int* shuffle_array = (int*)malloc(ARRAY_SIZE * sizeof(int));
    if (!shuffle_array) {
        printf("Failed to allocate memory\n");
        return 1;
    }
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        shuffle_array[i] = i;
    }
    
    printf("Initial array (first 10): ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", shuffle_array[i]);
    }
    printf("\n\n");
    
    for (int iter = 0; iter < ITERATIONS; iter++) {
        array_shuffle(shuffle_array, ARRAY_SIZE);
        if (iter % 20 == 0) {
            printf("Completed iteration %d\n", iter);
        }
    }
    
    printf("\nArray shuffled %d times\n", ITERATIONS);
    printf("Final array (first 10): ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", shuffle_array[i]);
    }
    printf("\n");
    
    int checksum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        checksum += shuffle_array[i];
    }
    printf("Checksum (should be %d): %d\n", (ARRAY_SIZE * (ARRAY_SIZE - 1)) / 2, checksum);
    
    free(shuffle_array);
    return 0;
}