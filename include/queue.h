#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "item.h"

// Opaque type (strict encapsulation)
typedef struct queue QUEUE;

/* --- Creation and Destruction --- */
QUEUE *queue_create(void);
void queue_delete(QUEUE **queue_ptr);

/* --- Main Operations (FIFO) --- */
bool queue_enqueue(QUEUE *queue, ITEM *item);
ITEM *queue_dequeue(QUEUE *queue);
ITEM *queue_front(const QUEUE *queue);

/* --- Queries --- */
bool queue_is_empty(const QUEUE *queue);
int queue_size(const QUEUE *queue);

#endif
