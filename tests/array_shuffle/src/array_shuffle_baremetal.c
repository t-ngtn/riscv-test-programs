#define ARRAY_SIZE 1024
#define ITERATIONS 100

static char heap[16*1024] __attribute__((aligned(16)));
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

static unsigned int simple_rand_seed = 12345;
static int simple_rand() {
    simple_rand_seed = simple_rand_seed * 1103515245 + 12345;
    return (simple_rand_seed / 65536) % 32768;
}

void array_shuffle(int *arr, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = simple_rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void _start() {
    write_string("Array Shuffle Test\n");
    write_string("Array size: ");
    write_int(ARRAY_SIZE);
    write_string("\nIterations: ");
    write_int(ITERATIONS);
    write_string("\n\n");
    
    int* shuffle_array = (int*)simple_malloc(ARRAY_SIZE * sizeof(int));
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        shuffle_array[i] = i;
    }
    
    write_string("Initial array (first 10): ");
    for (int i = 0; i < 10; i++) {
        write_int(shuffle_array[i]);
        write_string(" ");
    }
    write_string("\n\n");
    
    for (int iter = 0; iter < ITERATIONS; iter++) {
        array_shuffle(shuffle_array, ARRAY_SIZE);
        if (iter % 20 == 0) {
            write_string("Completed iteration ");
            write_int(iter);
            write_string("\n");
        }
    }
    
    write_string("\nArray shuffled ");
    write_int(ITERATIONS);
    write_string(" times\n");
    write_string("Final array (first 10): ");
    for (int i = 0; i < 10; i++) {
        write_int(shuffle_array[i]);
        write_string(" ");
    }
    write_string("\n");
    
    int checksum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        checksum += shuffle_array[i];
    }
    write_string("Checksum (should be ");
    write_int((ARRAY_SIZE * (ARRAY_SIZE - 1)) / 2);
    write_string("): ");
    write_int(checksum);
    write_string("\n");
    
    asm volatile (
        "li a7, 93\n"
        "li a0, 0\n"
        "ecall\n"
    );
}