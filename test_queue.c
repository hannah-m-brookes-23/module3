#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <string.h>

int main() {

    queue_t* queue = qopen();

    int x = 100;
    int y = 6;

    int result1 = qput(queue, &x);
    int result2 = qput(queue, &y);

    int *x_queue = (int*) qget(queue);
    int *y_queue = (int*) qget(queue);

    printf("results: %d, %d, x: %d, y: %d\n", result1, result2, *x_queue, *y_queue);
    for (int i = 0; i < 100; i++) {
        int result = qput(queue, &i);
        if (result != 0) {
            exit(EXIT_FAILURE);
        }
    }
    
    int *word = qget(queue);
    while (word != NULL) {
        printf("%d\n", *word);
        word = qget(queue);
    }

    qclose(queue);

    exit(EXIT_SUCCESS);
}
