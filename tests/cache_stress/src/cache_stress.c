#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE (1024 * 1024)

void cache_stress_test() {
    static int large_array[ARRAY_SIZE];
    
    printf("Cache Stress Test\n");
    printf("Array size: %d integers (%ld MB)\n", ARRAY_SIZE, (ARRAY_SIZE * sizeof(int)) / (1024 * 1024));
    printf("Testing different stride patterns...\n\n");
    
    for (int stride = 1; stride <= 64; stride *= 2) {
        int sum = 0;
        int accesses = 0;
        
        for (int i = 0; i < ARRAY_SIZE; i += stride) {
            large_array[i] = i;
            sum += large_array[i];
            accesses++;
        }
        
        printf("  Stride %2d: sum=%d, accesses=%d\n", stride, sum, accesses);
    }
    
    printf("Cache stress test completed\n");
    printf("Testing sequential vs random access patterns...\n\n");
    
    printf("Sequential access:\n");
    int seq_sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        large_array[i] = i;
        seq_sum += large_array[i];
    }
    printf("  Sequential sum: %d\n", seq_sum);
    
    printf("\nRandom-like access (prime stride):\n");
    int rand_sum = 0;
    int prime = 524287;
    for (int i = 0, idx = 0; i < ARRAY_SIZE; i++) {
        idx = (idx + prime) % ARRAY_SIZE;
        large_array[idx] = idx;
        rand_sum += large_array[idx];
    }
    printf("  Random-like sum: %d\n", rand_sum);
    
    printf("\nAll cache stress tests completed successfully!\n");
}

int main() {
    cache_stress_test();
    return 0;
}