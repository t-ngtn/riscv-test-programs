#include <stdio.h>
#include <stdlib.h>

#define LIST_SIZE 1000

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int main() {
    printf("Linked List Test\n");
    printf("List size: %d nodes\n\n", LIST_SIZE);
    
    Node* head = NULL;
    Node* current = NULL;
    
    printf("Creating linked list...\n");
    for (int i = 0; i < LIST_SIZE; i++) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        if (!new_node) {
            printf("Failed to allocate memory for node %d\n", i);
            return 1;
        }
        
        new_node->data = i;
        new_node->next = NULL;
        
        if (head == NULL) {
            head = new_node;
            current = head;
        } else {
            current->next = new_node;
            current = new_node;
        }
        
        if (i % 100 == 0) {
            printf("Created %d nodes\n", i);
        }
    }
    
    printf("\nTraversing linked list...\n");
    int sum = 0;
    int count = 0;
    current = head;
    while (current != NULL) {
        sum += current->data;
        count++;
        current = current->next;
    }
    
    printf("Traversal complete\n");
    printf("Node count: %d\n", count);
    printf("Sum of all values: %d\n", sum);
    printf("Expected sum: %d\n", (LIST_SIZE * (LIST_SIZE - 1)) / 2);
    
    if (sum == (LIST_SIZE * (LIST_SIZE - 1)) / 2) {
        printf("Verification: PASSED\n");
    } else {
        printf("Verification: FAILED\n");
    }
    
    printf("\nFreeing linked list...\n");
    current = head;
    int freed = 0;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
        freed++;
    }
    printf("Freed %d nodes\n", freed);
    
    return 0;
}