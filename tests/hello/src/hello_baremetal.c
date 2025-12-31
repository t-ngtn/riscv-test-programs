static void write_string(const char* str) {
    const char* p = str;
    int len = 0;
    while (p[len]) len++;
    
    asm volatile (
        "li a7, 64\n"       // syscall number for write
        "li a0, 1\n"        // fd = 1 (stdout)
        "mv a1, %0\n"       // buffer
        "mv a2, %1\n"       // length
        "ecall\n"
        :
        : "r"(str), "r"(len)
        : "a0", "a1", "a2", "a7"
    );
}

void _start() {
    write_string("Hello, RISC-V world!\n");
    
    asm volatile (
        "li a7, 93\n"       // syscall number for exit
        "li a0, 0\n"        // exit code
        "ecall\n"
    );
}