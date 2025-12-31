#define ARRAY_SIZE 1024
#define MATRIX_SIZE 64
#define ITERATIONS 100

static char heap[8*1024*1024] __attribute__((aligned(16)));
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

static unsigned int simple_rand_seed = 12345;
static int simple_rand() {
    simple_rand_seed = simple_rand_seed * 1103515245 + 12345;
    return (simple_rand_seed / 65536) % 32768;
}

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
        int j = simple_rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void memory_copy_test(void *dest, const void *src, int n) {
    memcpy_custom(dest, src, n);
}

void linked_list_test() {
    typedef struct Node {
        int data;
        struct Node* next;
    } Node;
    
    Node* head = 0;
    Node* current = 0;
    
    for (int i = 0; i < 1000; i++) {
        Node* new_node = (Node*)simple_malloc(sizeof(Node));
        new_node->data = i;
        new_node->next = 0;
        
        if (head == 0) {
            head = new_node;
            current = head;
        } else {
            current->next = new_node;
            current = new_node;
        }
    }
    
    int sum = 0;
    current = head;
    while (current != 0) {
        sum += current->data;
        current = current->next;
    }
    
    write_string("Linked list sum: ");
    write_int(sum);
    write_string("\n");
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
            write_string("Stride ");
            write_int(stride);
            write_string(" sum: ");
            write_int(sum);
            write_string("\n");
        }
    }
}

void _start() {
    write_string("Starting memory intensive tests...\n\n");
    
    write_string("Test 1: Matrix Multiplication\n");
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
    write_string("Matrix multiplication completed ");
    write_int(ITERATIONS);
    write_string(" times\n");
    write_string("Sample result[0][0]: ");
    write_int(result[0][0]);
    write_string("\n\n");
    
    write_string("Test 2: Array Shuffling\n");
    int* shuffle_array = (int*)simple_malloc(ARRAY_SIZE * sizeof(int));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        shuffle_array[i] = i;
    }
    
    for (int iter = 0; iter < ITERATIONS; iter++) {
        array_shuffle(shuffle_array, ARRAY_SIZE);
    }
    write_string("Array shuffled ");
    write_int(ITERATIONS);
    write_string(" times\n");
    write_string("First 5 elements: ");
    write_int(shuffle_array[0]);
    write_string(" ");
    write_int(shuffle_array[1]);
    write_string(" ");
    write_int(shuffle_array[2]);
    write_string(" ");
    write_int(shuffle_array[3]);
    write_string(" ");
    write_int(shuffle_array[4]);
    write_string("\n\n");
    
    write_string("Test 3: Memory Copy Operations\n");
    void* src_buffer = simple_malloc(1024 * 1024);
    void* dest_buffer = simple_malloc(1024 * 1024);
    
    memset_custom(src_buffer, 0xAA, 1024 * 1024);
    
    for (int iter = 0; iter < 100; iter++) {
        memory_copy_test(dest_buffer, src_buffer, 1024 * 1024);
    }
    write_string("Memory copy completed (100MB total)\n\n");
    
    write_string("Test 4: Linked List Operations\n");
    linked_list_test();
    write_string("\n");
    
    write_string("Test 5: Cache Stress Test\n");
    cache_stress_test();
    
    write_string("\nAll memory intensive tests completed successfully!\n");
    
    asm volatile (
        "li a7, 93\n"
        "li a0, 0\n"
        "ecall\n"
    );
}