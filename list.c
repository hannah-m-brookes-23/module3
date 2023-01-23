/* list.c --- module list.c implements interface list.h
 * 
 * 
 * Author: Hannah M. Brookes
 * Created: Mon Jan 23 15:47:17 2023 (-0500)
 * Version: 
 * 
 * Description: 
 * 
 */

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define MAXREG 10

typedef struct car {
	struct car *next;
	char plate[MAXREG];
	double price;
	int year;
} car_t;


// global declaration, hides list of cars internally
static car_t *front=NULL;


int32_t lput(car_t *cp) {
	// if the list is currently empty, set new car to be the front and
	// do nothing else
	if (front == NULL) {
		printf("this option\n");
		front = cp;
	}
	// if the list is not empty, set the new car's next pointer to the
	// current front of the list then set the front pointer to the new
	// car
	else {
		printf("other option\n");
		cp -> next = front;
		front = cp;
	}
	return 0;
}


car_t *lget() {
	// if the list is empty, return NULL
	if (front == NULL) {
		printf("nothing in list\n");
		return NULL;
	}
	// if the list is NOT empty, return the car that is at the front of
	// the list and update the front of the list to the car that it
	// pointed to
	else {
		printf("there is a car\n");
		car_t *temp = front;
		front = temp -> next;
		return temp;
	}
}


void lapply(void (*fn)(car_t *cp)) {
	// if the list is empty, do nothing. otherwise, apply the function
	// to every car in the list
	if (front != NULL) {
		car_t *curr_car = front;
		while (curr_car != NULL) {
			fn(curr_car);
			curr_car = curr_car -> next;
		}
	}
}


car_t *lremove(char *platep) {
	// returns NULL if the list is empty
	if (front == NULL) {
		return NULL;
	}
	else {
		car_t *curr_car = front;
		while (curr_car != NULL) {
			if (strcmp(platep, curr_car -> plate) == 0)
				return curr_car;
			curr_car = curr_car -> next;
		}
		// if reached end of while loop, then no such car exists and
		// return NULL
		return NULL;
	}
}

