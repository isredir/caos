#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    struct Node *prev;
    struct Node *next;
    int value;
} Node;

Node *push(Node *place, int value) {
    Node *new_node = calloc(1, sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->value = value;
    new_node->next = place;
    if (place == NULL) {
        return new_node;
    }
    if (place->prev != NULL) {
        new_node->prev = place->prev;
        place->prev->next = new_node;
    }
    place->prev = new_node;
    return new_node;
}

int pop(Node *node) {
    int value = node->value;
    if (node->prev && node->next) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    } else if (node->prev && !node->next) {
        node->prev->next = NULL;
    } else if (!node->prev && node->next) {
        node->next->prev = NULL;
    }
    free(node);
    return value;
}
