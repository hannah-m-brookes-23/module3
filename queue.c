/*
 * queue.c -- implementation of queue.h interface
 *
 * Authors: Cameron Wolfe, Hannah Brookes, and Raif Olsen
 * Date: 
 * Version: 1.0
 *
 * Description: 
 */

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

// queueItem_t has a pointer to the next queueItem_t and to the actual data
typedef struct queueItem {
    struct queueItem *next;
    void *item;
} queueItem_t;

// internalQueue has a queueItem_t pointer to the front and the back
typedef struct internalQueue {
    queueItem_t *front;
    queueItem_t *back;
} internalQueue_t;

// Handles the memory allocation of creating an internalQueue_t and returns a pointer
static internalQueue_t* makeQueue(void) {
    internalQueue_t* queue = (internalQueue_t*) malloc(sizeof(internalQueue_t));
    queue->front = NULL;
    queue->back = NULL;
    return queue;
}

// Frees memory for internalQueue_t
static uint32_t removeQueue(internalQueue_t* queue) {
    free(queue);
    return 1;
}

// Creates an empty queue and gives pointer to user
queue_t* qopen(void) {
    internalQueue_t* queue = makeQueue();
    return (queue_t*) queue;
}

// Closes a queue that the user has
void qclose(queue_t *qp) {
    removeQueue((internalQueue_t*) qp);
}
