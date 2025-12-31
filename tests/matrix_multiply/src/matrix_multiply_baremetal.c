#define MATRIX_SIZE 64
#define ITERATIONS 100

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

void _start() {
    write_string("Matrix Multiplication Test\n");
    write_string("Matrix size: ");
    write_int(MATRIX_SIZE);
    write_string("x");
    write_int(MATRIX_SIZE);
    write_string("\nIterations: ");
    write_int(ITERATIONS);
    write_string("\n\n");
    
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
        if (iter % 10 == 0) {
            write_string("Completed iteration ");
            write_int(iter);
            write_string("\n");
        }
    }
    
    write_string("\nMatrix multiplication completed ");
    write_int(ITERATIONS);
    write_string(" times\n");
    write_string("Sample results:\n");
    write_string("  result[0][0]: ");
    write_int(result[0][0]);
    write_string("\n  result[31][31]: ");
    write_int(result[31][31]);
    write_string("\n  result[63][63]: ");
    write_int(result[63][63]);
    write_string("\n");
    
    asm volatile (
        "li a7, 93\n"
        "li a0, 0\n"
        "ecall\n"
    );
}