#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main() {

    queue_t* queue = qopen();

    int x = 69;
    int y = 666;

    int result1 = qput(queue, &x);
    int result2 = qput(queue, &y);

    int *x_queue = (int*) qget(queue);
    int *y_queue = (int*) qget(queue);

    printf("results: %d, %d, x: %d, y: %d\n", result1, result2, *x_queue, *y_queue);

    exit(EXIT_SUCCESS);
}
