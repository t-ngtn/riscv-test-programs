#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ARRAY_SIZE 1024
#define MATRIX_SIZE 64
#define ITERATIONS 100

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

void array_shuffle(int *arr, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void memory_copy_test(void *dest, const void *src, size_t n) {
    memcpy(dest, src, n);
}

void linked_list_test() {
    typedef struct Node {
        int data;
        struct Node* next;
    } Node;
    
    Node* head = NULL;
    Node* current = NULL;
    
    for (int i = 0; i < 1000; i++) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = i;
        new_node->next = NULL;
        
        if (head == NULL) {
            head = new_node;
            current = head;
        } else {
            current->next = new_node;
            current = new_node;
        }
    }
    
    int sum = 0;
    current = head;
    while (current != NULL) {
        sum += current->data;
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    
    printf("Linked list sum: %d\n", sum);
}

void cache_stress_test() {
    static int large_array[1024 * 1024];
    
    for (int iter = 0; iter < 10; iter++) {
        for (int stride = 1; stride <= 64; stride *= 2) {
            int sum = 0;
            for (int i = 0; i < 1024 * 1024; i += stride) {
                large_array[i] = i;
                sum += large_array[i];
            }
            printf("Stride %d sum: %d\n", stride, sum);
        }
    }
}

int main() {
    printf("Starting memory intensive tests...\n\n");
    
    printf("Test 1: Matrix Multiplication\n");
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
    }
    printf("Matrix multiplication completed %d times\n", ITERATIONS);
    printf("Sample result[0][0]: %d\n\n", result[0][0]);
    
    printf("Test 2: Array Shuffling\n");
    int* shuffle_array = (int*)malloc(ARRAY_SIZE * sizeof(int));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        shuffle_array[i] = i;
    }
    
    for (int iter = 0; iter < ITERATIONS; iter++) {
        array_shuffle(shuffle_array, ARRAY_SIZE);
    }
    printf("Array shuffled %d times\n", ITERATIONS);
    printf("First 5 elements: %d %d %d %d %d\n\n", 
           shuffle_array[0], shuffle_array[1], shuffle_array[2], 
           shuffle_array[3], shuffle_array[4]);
    
    printf("Test 3: Memory Copy Operations\n");
    void* src_buffer = malloc(1024 * 1024);
    void* dest_buffer = malloc(1024 * 1024);
    
    memset(src_buffer, 0xAA, 1024 * 1024);
    
    for (int iter = 0; iter < 100; iter++) {
        memory_copy_test(dest_buffer, src_buffer, 1024 * 1024);
    }
    printf("Memory copy completed (100MB total)\n\n");
    
    free(src_buffer);
    free(dest_buffer);
    
    printf("Test 4: Linked List Operations\n");
    linked_list_test();
    printf("\n");
    
    printf("Test 5: Cache Stress Test\n");
    cache_stress_test();
    
    free(shuffle_array);
    
    printf("\nAll memory intensive tests completed successfully!\n");
    
    return 0;
}