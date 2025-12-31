#define LIST_SIZE 1000

typedef struct Node {
    int data;
    struct Node* next;
} Node;

static char heap[64*1024] __attribute__((aligned(16)));
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

void _start() {
    write_string("Linked List Test\n");
    write_string("List size: ");
    write_int(LIST_SIZE);
    write_string(" nodes\n\n");
    
    Node* head = 0;
    Node* current = 0;
    
    write_string("Creating linked list...\n");
    for (int i = 0; i < LIST_SIZE; i++) {
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
        
        if (i % 100 == 0) {
            write_string("Created ");
            write_int(i);
            write_string(" nodes\n");
        }
    }
    
    write_string("\nTraversing linked list...\n");
    int sum = 0;
    int count = 0;
    current = head;
    while (current != 0) {
        sum += current->data;
        count++;
        current = current->next;
    }
    
    write_string("Traversal complete\n");
    write_string("Node count: ");
    write_int(count);
    write_string("\nSum of all values: ");
    write_int(sum);
    write_string("\nExpected sum: ");
    write_int((LIST_SIZE * (LIST_SIZE - 1)) / 2);
    write_string("\n");
    
    if (sum == (LIST_SIZE * (LIST_SIZE - 1)) / 2) {
        write_string("Verification: PASSED\n");
    } else {
        write_string("Verification: FAILED\n");
    }
    
    write_string("\nLinked list test completed\n");
    
    asm volatile (
        "li a7, 93\n"
        "li a0, 0\n"
        "ecall\n"
    );
}