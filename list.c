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
#include "list.h"

// global declaration, hides list of cars internally
static car_t *front=NULL;


/* 
 * put(): places a car at the beginning of the list; returns 0
 * indicating success
 */
int32_t lput(car_t *cp) {
	// if the list is currently empty, set new car to be the front and
	// do nothing else
	if (front == NULL)
		front = cp;
	// if the list is not empty, set the new car's next pointer to the
	// current front of the list then set the front pointer to the new
	// car
	else {
		cp -> next = front;
		front = cp;
	}
	return 0;
}


/*
 * get(): remove and return the first car in the list (returns NULL if
 * the list is empty)
 */
car_t *lget() {
	// if the list is empty, return NULL
	if (front == NULL)
		return NULL;
	// if the list is NOT empty, return the car that is at the front of
	// the list and update the front of the list to the car that it
	// pointed to
	else {
		car_t *temp = front;
		front = temp -> next;
		return temp;
	}
}


/*
 * apply(): applies an arbitrary function to every car in the list
 */
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


/*
 * remove(): find, rmeove, and return any car with the designated
 * plate (returns NULL ifa matching car is not present)
 */
car_t *lremove(char *platep) {
	// returns NULL if the list is empty
	if (front == NULL) {
		return NULL;
	}
	else {
		car_t *prev_car = NULL;
		car_t *curr_car = front;
		while (curr_car != NULL) {
			// identifies a car to remove (and thus return)
			if (strcmp(platep, curr_car -> plate) == 0) {
				// car to be removed is the first in the list: update the
				// front pointer to be the car next in line to the car to be
				// removed
				if (prev_car == NULL) 
					front = curr_car -> next;
				// car to be removed is the last car in the list: update the
				// previous car's next pointer to be null
				else if (curr_car -> next == NULL) 
					prev_car -> next = NULL;
				// car to be removed is neither the first nor the last car in
				// the list (in the middle of the list): update the previous
				// car's next pointer to be the removed car's next pointer
				else 
					prev_car -> next = curr_car -> next;
		    // return the current car
				return curr_car;
			}
			prev_car = curr_car;
			curr_car = curr_car -> next;
		}
		// if reached end of while loop, then no such car exists and
		// return NULL
		return NULL;
	}
}

