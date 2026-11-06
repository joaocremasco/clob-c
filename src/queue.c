#include <stdlib.h>
#include "queue.h"

// Internal linked-list node (hidden in the .c file)
typedef struct node {
    ITEM *item;
    struct node *next;
} NODE;

// Main Queue structure
struct queue {
    NODE *front;
    NODE *rear;
    int size;
};

QUEUE *queue_create(void) {
    QUEUE *queue = malloc(sizeof(QUEUE));

    if (queue != NULL) {
        queue->front = NULL;
        queue->rear = NULL;
        queue->size = 0;
    }

    return queue;
}

void queue_delete(QUEUE **queue_ptr) {
    if (queue_ptr == NULL || *queue_ptr == NULL)
        return;

    NODE *current = (*queue_ptr)->front;

    while (current != NULL) {
        NODE *aux = current;
        current = current->next;

        // Free the queue node (ITEM memory is managed externally)
        free(aux);
    }

    free(*queue_ptr);
    *queue_ptr = NULL;
}

bool queue_enqueue(QUEUE *queue, ITEM *item) {
    if (queue == NULL || item == NULL)
        return false;

    NODE *new_node = malloc(sizeof(NODE));

    if (new_node == NULL)
        return false;

    new_node->item = item;
    new_node->next = NULL;

    if (queue->front == NULL) {
        queue->front = new_node;
    } else {
        queue->rear->next = new_node;
    }

    queue->rear = new_node;
    queue->size++;

    return true;
}

ITEM *queue_dequeue(QUEUE *queue) {
    if (queue == NULL || queue->front == NULL)
        return NULL;

    NODE *removed_node = queue->front;
    ITEM *item = removed_node->item;

    queue->front = removed_node->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(removed_node);
    queue->size--;

    return item;
}

ITEM *queue_front(const QUEUE *queue) {
    if (queue == NULL || queue->front == NULL)
        return NULL;

    return queue->front->item;
}

bool queue_is_empty(const QUEUE *queue) {
    return (queue == NULL || queue->size == 0) ? true : false;
}

int queue_size(const QUEUE *queue) {
    return (queue == NULL) ? 0 : queue->size;
}
