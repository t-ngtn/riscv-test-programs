#define ARRAY_SIZE (1024 * 1024)

static void write_string(const char* str) {
    const char* p = str;
    int len = 0;
    while (p[len]) len++;
    
    asm volatile (
        "li a7, 64\n"
        "li a0, 1\n"
        "mv a1, %0\n"
        "mv a2, %1\n"
        "ecall\n"
        :
        : "r"(str), "r"(len)
        : "a0", "a1", "a2", "a7"
    );
}

static void write_int(int num) {
    char buffer[32];
    int i = 0;
    
    if (num == 0) {
        buffer[i++] = '0';
    } else {
        if (num < 0) {
            buffer[i++] = '-';
            num = -num;
        }
        
        char temp[32];
        int j = 0;
        while (num > 0) {
            temp[j++] = '0' + (num % 10);
            num /= 10;
        }
        
        while (j > 0) {
            buffer[i++] = temp[--j];
        }
    }
    
    buffer[i] = '\0';
    write_string(buffer);
}

void cache_stress_test() {
    static int large_array[ARRAY_SIZE];
    
    write_string("Cache Stress Test\n");
    write_string("Array size: ");
    write_int(ARRAY_SIZE);
    write_string(" integers (");
    write_int((ARRAY_SIZE * sizeof(int)) / (1024 * 1024));
    write_string(" MB)\n");
    write_string("Testing different stride patterns...\n\n");
    
    for (int stride = 1; stride <= 64; stride *= 2) {
        int sum = 0;
        int accesses = 0;
        
        for (int i = 0; i < ARRAY_SIZE; i += stride) {
            large_array[i] = i;
            sum += large_array[i];
            accesses++;
        }
        
        write_string("  Stride ");
        if (stride < 10) write_string(" ");
        write_int(stride);
        write_string(": sum=");
        write_int(sum);
        write_string(", accesses=");
        write_int(accesses);
        write_string("\n");
    }
    
    write_string("Cache stress test completed\n");
    write_string("Testing sequential vs random access patterns...\n\n");
    
    write_string("Sequential access:\n");
    int seq_sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        large_array[i] = i;
        seq_sum += large_array[i];
    }
    write_string("  Sequential sum: ");
    write_int(seq_sum);
    write_string("\n");
    
    write_string("\nRandom-like access (prime stride):\n");
    int rand_sum = 0;
    int prime = 524287;
    for (int i = 0, idx = 0; i < ARRAY_SIZE; i++) {
        idx = (idx + prime) % ARRAY_SIZE;
        large_array[idx] = idx;
        rand_sum += large_array[idx];
    }
    write_string("  Random-like sum: ");
    write_int(rand_sum);
    write_string("\n");
    
    write_string("\nAll cache stress tests completed successfully!\n");
}

void _start() {
    cache_stress_test();
    
    asm volatile (
        "li a7, 93\n"
        "li a0, 0\n"
        "ecall\n"
    );
}