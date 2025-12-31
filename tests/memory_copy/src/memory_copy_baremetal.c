#define BUFFER_SIZE (1024 * 1024)
#define ITERATIONS 100

static char heap[2*1024*1024 + 32] __attribute__((aligned(16)));
static char* heap_ptr = heap;

static void* simple_malloc(int size) {
    size = (size + 15) & ~15;
    char* ptr = heap_ptr;
    heap_ptr += size;
    return ptr;
}

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

static void memcpy_custom(void* dest, const void* src, int n) {
    char* d = (char*)dest;
    const char* s = (const char*)src;
    for (int i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

static void memset_custom(void* dest, int val, int n) {
    char* d = (char*)dest;
    for (int i = 0; i < n; i++) {
        d[i] = val;
    }
}

void memory_copy_test(void *dest, const void *src, int n) {
    memcpy_custom(dest, src, n);
}

void _start() {
    write_string("Memory Copy Test\n");
    write_string("Buffer size: ");
    write_int(BUFFER_SIZE);
    write_string(" bytes (1MB)\n");
    write_string("Iterations: ");
    write_int(ITERATIONS);
    write_string("\n\n");
    
    void* src_buffer = simple_malloc(BUFFER_SIZE);
    void* dest_buffer = simple_malloc(BUFFER_SIZE);
    
    write_string("Initializing source buffer...\n");
    memset_custom(src_buffer, 0xAA, BUFFER_SIZE);
    
    write_string("Starting memory copy operations...\n");
    for (int iter = 0; iter < ITERATIONS; iter++) {
        memory_copy_test(dest_buffer, src_buffer, BUFFER_SIZE);
        if (iter % 10 == 0) {
            write_string("Completed iteration ");
            write_int(iter);
            write_string("\n");
        }
    }
    
    write_string("\nMemory copy completed\n");
    write_string("Total data copied: ");
    write_int(ITERATIONS);
    write_string(" MB\n");
    
    unsigned char* src = (unsigned char*)src_buffer;
    unsigned char* dest = (unsigned char*)dest_buffer;
    int errors = 0;
    for (int i = 0; i < BUFFER_SIZE; i += 4096) {
        if (dest[i] != src[i]) {
            errors++;
        }
    }
    
    if (errors == 0) {
        write_string("Verification: PASSED\n");
    } else {
        write_string("Verification: FAILED (");
        write_int(errors);
        write_string(" errors)\n");
    }
    
    asm volatile (
        "li a7, 93\n"
        "li a0, 0\n"
        "ecall\n"
    );
}