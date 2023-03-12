#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList {
    int num;
    struct LinkedList *next;
} LinkedList;

int main() {
    LinkedList *node = calloc(1, sizeof(*node));
    int num;
    while (scanf("%d", &num) == 1) {
        LinkedList *prev_node = calloc(1, sizeof(*node->next));
        node->num = num;
        prev_node->next = node;
        node = prev_node;
        // printf("%d\n", node->next->num);
    }
    while (node->next != NULL) {
        printf("%d\n", node->next->num);
        LinkedList *prev_node = node;
        node = node->next;
        free(prev_node);
    }
    free(node);
}