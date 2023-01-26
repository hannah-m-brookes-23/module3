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

    if (qp == NULL) 
        return;

    internalQueue_t* queue = (internalQueue_t*) qp;
    
    while (queue->front != NULL) {
        qget(qp);
    }
    
    removeQueue((internalQueue_t*) qp);
}

// Puts an item in the queue
int32_t qput(queue_t *qp, void *elementp) {
    
    // Null Checks
    if (qp == NULL || elementp == NULL) {
        return 1;
    }

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

    // Null check
    if (qp == NULL) 
        return NULL;

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

// Applies a function to every element in the queue
void qapply(queue_t *qp, void (*fn)(void* elementp)) {
    
    // Null check
    if (qp == NULL || fn == NULL)
        return;
    
    // Queue conversion
    internalQueue_t *queue = (internalQueue_t*) qp;

    queueItem_t *current = queue -> front;

    // Go through all queue elements and apply function
    while (current != NULL) {
        fn(current->item);
        current = current->next;
    }
}

// searches the queue using boolean function, returns pointer to an
// element if its found otherwise returns NULL
void* qsearch(queue_t *qp,
							bool (*searchfn)(void* elementp, const void* keyp),
							const void* skeyp) {
    // Null check
    if (qp == NULL || searchfn == NULL || skeyp == NULL)
        return NULL;
		
    // external to internal conversion
    internalQueue_t *queue = (internalQueue_t*) qp;
    queueItem_t *current = queue -> front;

		// iterates through the queue searching for item using given
		// search function
    while (current != NULL) {
    	void *itemp = current -> item;
    	bool matches = searchfn(itemp, skeyp);
    	if (matches)
    		return itemp;
    	current = current -> next;
    }
    return NULL;
	
}

// searches a queue using the given boolean function; removes the
// element from the queue and returns a pointer to it if element is
// found; otherwise, return NULL
void* qremove(queue_t *qp,
							bool (*searchfn)(void* elementp, const void* keyp),\
							const void* skeyp) {
	  // Null check
    if (qp == NULL || searchfn == NULL || skeyp == NULL)
        return NULL;

		// external to internal conversion
    internalQueue_t *queue = (internalQueue_t*) qp;
    queueItem_t *current = queue -> front;
		queueItem_t *prev_item = NULL;
		
		// iterates through the queue searching for item using given
		// search function; if item found, remove it from queue and return
		// pointer to it
    while (current != NULL) {
    	void *itemp = current -> item;
    	bool matches = searchfn(itemp, skeyp);

			if (matches) {
				// matching item to be removed is the first in the queue:
				// update the front pointer to the item next in the queue
				if (prev_item == NULL) 
					queue -> front = current -> next;
				// matching item to be removed is the last item in the queue:
				// update the previous item's next pointer to be null
				else if (current -> next == NULL) 
					prev_item -> next = NULL;
				// item to be removed is in the middle of the queue: update
				// the previous item's pointer to the removed item's next
				// pointer
				else
					prev_item -> next = current -> next;
				// free memory for the item
				removeQueueItem(current);
				// return pointer to the item
				return itemp;
			}
			
			prev_item = current;
    	current = current -> next;
    }
		// if no matching item, return NULL
    return NULL;
}

// Concatenates two queues, putting the second at the end of the first
void qconcat(queue_t *q1p, queue_t *q2p) {

    // Null check
    if (q1p == NULL || q2p == NULL) 
        return;

    // Converts user queue to internalQueue
    internalQueue_t *q2 = (internalQueue_t*) q2p;
    
    // Get every item in second queue and put it at the end of second queue 
    while (q2->front != NULL) {
        void *item = qget(q2p);
        qput(q1p, item);
    }
    
    // Deallocate memory of second queue
    qclose(q2p);
}
