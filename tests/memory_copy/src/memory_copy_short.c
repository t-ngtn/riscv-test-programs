#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE (1024 * 1024)
#define ITERATIONS 3

void memory_copy_test(void *dest, const void *src, size_t n) {
    memcpy(dest, src, n);
}

int main() {
    printf("Memory Copy Test (Short Version)\n");
    printf("Buffer size: %d bytes (1MB)\n", BUFFER_SIZE);
    printf("Iterations: %d\n\n", ITERATIONS);
    
    void* src_buffer = malloc(BUFFER_SIZE);
    void* dest_buffer = malloc(BUFFER_SIZE);
    
    if (!src_buffer || !dest_buffer) {
        printf("Failed to allocate memory\n");
        return 1;
    }
    
    printf("Initializing source buffer...\n");
    memset(src_buffer, 0xAA, BUFFER_SIZE);
    
    printf("Starting memory copy operations...\n");
    for (int iter = 0; iter < ITERATIONS; iter++) {
        memory_copy_test(dest_buffer, src_buffer, BUFFER_SIZE);
        printf("Completed iteration %d\n", iter);
    }
    
    printf("\nMemory copy completed\n");
    printf("Total data copied: %d MB\n", ITERATIONS);
    
    unsigned char* src = (unsigned char*)src_buffer;
    unsigned char* dest = (unsigned char*)dest_buffer;
    int errors = 0;
    for (int i = 0; i < BUFFER_SIZE; i += 4096) {
        if (dest[i] != src[i]) {
            errors++;
        }
    }
    
    if (errors == 0) {
        printf("Verification: PASSED\n");
    } else {
        printf("Verification: FAILED (%d errors)\n", errors);
    }
    
    free(src_buffer);
    free(dest_buffer);
    
    return 0;
}