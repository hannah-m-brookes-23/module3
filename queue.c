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
static void removeQueue(internalQueue_t* queue) {
    free(queue);
}

static queueItem_t* makeQueueItem(void *itemPointer) {
    queueItem_t *ip = (queueItem_t*) malloc(sizeof(queueItem_t));
    ip->next = NULL;
    ip->item = itemPointer;
    return ip;
}

static void removeQueueItem(queueItem_t *p) {
    free(p);
}

// Creates an empty queue and gives pointer to user
queue_t* qopen(void) {
    internalQueue_t* queue = makeQueue();
    return (queue_t*) queue;
}

// Closes a queue that the user has opened
void qclose(queue_t *qp) {
    internalQueue_t* queue = (internalQueue_t*) qp;
    
    while (queue->front == NULL) {
        qget(qp);
    }
    
    removeQueue((internalQueue_t*) qp);
}

// Puts an item in the queue
int32_t qput(queue_t *qp, void *elementp) {

    // Convert user pointer to internal pointer
    internalQueue_t *queue = (internalQueue_t*) qp;
    
    // Create queueItem from item
    queueItem_t* item = makeQueueItem(elementp);

    // Queue is empty
    if (queue->front == NULL) {
        queue->front = item;
        queue->back = item;
        return 0;
    }

    // Queue is not empty
    else {
        queueItem_t* currentBack = queue->back;
        currentBack->next = item;
        queue->back = item;
        return 0;
    }
}

// Gets the first element in the queue and returns a pointer to it. Returns 
// NULL if queue is empty
void *qget(queue_t *qp) {
    // Convert user pointer to internal pointer
    internalQueue_t *queue = (internalQueue_t*) qp;
    
    // Queue is empty
    if (queue->front == NULL) 
        return NULL;

    // Get item at front of queue and make next item the front of the queue
    queueItem_t *front = queue->front;
    queue->front = front->next;

    // Queue is now empty, so fix the back
    if (queue->front == NULL)
        queue->back = NULL;

    // Extract item pointer from queueItem
    void *itemPointer = front->item;

    // Handle deallocation of memory
    removeQueueItem(front);

    return itemPointer;
}
