#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <string.h>

bool compareInts(void *a, const void *b);
void doubleInt(void* n);

int main(void) {

    queue_t* queue = qopen();

    // Putting items into queue
    int x = 100;
    int y = 6;
    int result1 = qput(queue, &x);
    int result2 = qput(queue, &y);
    if (result1 != 0 || result2 != 0) {
        printf("Failed putting items into the queue\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed putting items into the queue\n");
    
    // Putting null item into queue
    int nullResult = qput(queue, NULL);
    if (nullResult == 0) {
        printf("Failed putting null item into queue (able to be added)\n");
        exit(EXIT_FAILURE);
    }

    // Getting items from queue
    int *x_queue = (int*) qget(queue);
    if (*x_queue != x) {
        printf("Failed getting items from the queue\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed getting items from the queue\n");

    // Fully empty out queue
    qget(queue);

    // Getting from empty queue (should return NULL)
    int *null_queue = (int*) qget(queue);
    if (null_queue != NULL) {
        printf("Failed getting from empty queue\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed getting from empty queue (NULL returned)\n");

    // Searching for existing item in queue
    int z = 100;
    qput(queue, &z);
    int *w = qsearch(queue, compareInts, &z);
    if (*w != z) {
        printf("Failed searching for existing item from queue\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed searching for existing item from queue\n");
   
    // Searching for nonexisting item in queue
    int t = 5;
    w = qsearch(queue, compareInts, &t);
    if (w != NULL) {
        printf("Failed searching for nonexistent item in queue\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed searching for nonexistent item in queue\n");

    // Searching empty queue
    qget(queue);
    w = &z; // Give a new value to make sure null is not from past step
    w = qsearch(queue, compareInts, &t);
    if (w != NULL) {
        printf("Failed searching empty queue\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed searching empty queue\n");

    // Populate queues with new values
    queue_t *queue2 = qopen();
    queue_t *queue3 = qopen();

    int len = 10;
    int a[len];
    int b[len];
    for (int i = 0; i < len; i++) {
        a[i] = 2 * i + 1;
        b[i] = 2 * i + 1;
        int resulta = qput(queue2, &a[i]);
        int resultb = qput(queue3, &b[i]);
        if (resulta != 0 || resultb != 0) {
            exit(EXIT_FAILURE);
        }
    }
    
    // Double all values in queue3
    qapply(queue3, doubleInt);
    
    // Check qapply
    int *n2 = qget(queue2);
    int *n3 = qget(queue3);

    while (n2 != NULL && n3 != NULL) {
        if (*n2 * 2 != *n3) {
            printf("Failed applying a function to a queue\n");
            exit(EXIT_FAILURE);
        }
        n2 = qget(queue2);
        n3 = qget(queue3);
    }
    printf("Passed applying a function to a queue\n");
<<<<<<< HEAD
    
=======
        
>>>>>>> b2fc8903e22f5cb999caeeede7d60b37801914d7
    // Create and populate queue for qremove testing
    queue_t *queue4 = qopen();
    int num1 = 1;
    int num2 = 2;
    int num3 = 4;
    qput(queue4, &num1);
    qput(queue4, &num2);
    qput(queue4, &num3);

    // Remove item from queue and make sure it is removed
    int num2r = num2;
    int *queueNum2 = (int*) qremove(queue4, compareInts, &num2r);

    if (*queueNum2 != num2r) {
        printf("Failed removing item from queue (incorrect value)\n");
        exit(EXIT_FAILURE);
    }
    int *num2InQueue = (int*) qsearch(queue4, compareInts, &num2r);
    if (num2InQueue != NULL) {
        printf("Failed removing item from queue (still in queue)\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed removing element from queue\n");

    // Remove nonexistent item from queue
    int num4 = 200;
    int *notInQueue = (int*) qremove(queue4, compareInts, &num4);
    if (notInQueue != NULL) {
        printf("Failed removing nonexistent item from queue\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed removing nonexistent item from queue\n");

    // Clear out queue
    while (qget(queue4) != NULL) {} 
    
    // Remove item from empty queue
    int *emptyRemove = (int*) qremove(queue4, compareInts, &num1);
    if (emptyRemove != NULL) {
        printf("Failed removing from empty queue\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed removing from empty queue\n");

<<<<<<< HEAD
=======
    qclose(queue4);

		
>>>>>>> b2fc8903e22f5cb999caeeede7d60b37801914d7
    // Allocation for qconcat testing
    queue_t *queue5 = qopen();
    queue_t *queue6 = qopen();
		
    qput(queue5, &num1);
    qput(queue5, &num2);
    qput(queue6, &num3);

    qconcat(queue5, queue6);

    int *x1 = (int*) qget(queue5);
    int *x2 = (int*) qget(queue5);
    int *x3 = (int*) qget(queue5);

    if (*x1 != num1 || *x2 != num2 || *x3 != num3) {
        printf("Failed concatenation of queues\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed concatenation of queues\n");
		
    // Empty queue concatenation (second queue empty)
    qput(queue5, &num1);
    qput(queue5, &num2);
    queue_t* queue7 = qopen();
    qconcat(queue5, queue7);

    int *num = (int*) qget(queue5);
    int counter = 0;
    while (num != NULL) {
        num = (int*) qget(queue5);
        counter++;
    }

    if (counter != 2) {
        printf("Failed empty concatenation - second queue empty\n");
        exit(EXIT_FAILURE);
    }
<<<<<<< HEAD
    printf("Passed empty concatenation");
     
=======
    printf("Passed empty concatenation - second queue empty\n");


		// Empty queue concatenation (first queue empty)
    qput(queue5, &num1);
    qput(queue5, &num2);
    queue_t* queue8 = qopen();
    qconcat(queue8, queue5);

    num = (int*) qget(queue8);
    counter = 0;
    while (num != NULL) {
        num = (int*) qget(queue8);
        counter++;
    }
    if (counter != 2) {
        printf("Failed empty concatenation - first queue empty\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed empty concatenation - first queue empty\n");
    
>>>>>>> b2fc8903e22f5cb999caeeede7d60b37801914d7
    // Closing of all queues
    qclose(queue); 
    qclose(queue2);
    qclose(queue8);
		
    // Closing non empty queue, check valgrind for memory leaks
    qput(queue3, n3);
    qclose(queue3);
<<<<<<< HEAD
    
    qclose(queue4);
    qclose(queue5);
    qclose(queue6);
    qclose(queue7);

=======

		// Make sure qclose works if pass in NULL pointer
		queue_t* queue9 = NULL;
		qclose(queue9);

		
>>>>>>> b2fc8903e22f5cb999caeeede7d60b37801914d7
    // All tests passed
    printf("\nAll tests passed!\n");
    exit(EXIT_SUCCESS);
}

bool compareInts(void *a, const void *b) {
    int *aInt = (int*) a;
    int *bInt = (int*) b;
    bool result = *aInt == *bInt;
    return result;
}

void doubleInt(void *n) {
    int *x = (int*)n;
    *x *= 2;
}
