/* test1.c --- test file for linked-list data structure
 * 
 * 
 * Author: Raif T. Olson
 * Created: Tue Jan 24 09:07:01 2023 (-0500)
 * Version: 1.0
 * 
 * Description: tests the get() and put() functions from list 
 * 
 */

#include "list.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>


void test_apply_fn(car_t *cp) {
	cp -> year = 10*(cp -> year);
}

void print_list(car_t *curr_car) {
	// prints whole list if curr_car is the first car in list
	while (curr_car != NULL) {
		char *plates = curr_car -> plate;
		printf("%s\n", plates);
		curr_car = curr_car -> next;
	}
}

int main(void) {
	int32_t res = 0;
	car_t car1 = { .next = NULL, .plate = "car1", .price = 2000.99, .year = 1998 };
	car_t car2 = { .next = NULL, .plate = "car2", .price = 1111100.25, .year = 2045 };
	car_t car3 = { .next = NULL, .plate = "car3", .price = 123.10, .year = 1901 };
	car_t car4 = { .next = NULL, .plate = "car4", .price = 12345.22, .year = 2000 };
	car_t *car_return;

	// test put car in empty list
	res = lput(&car1);
	if (res != 0) {
		printf("test FAILED: put car in empty list\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("test passed: put car in empty list\n");

	// test put car in non-empty list
	res = lput(&car2);
	if (res != 0) {
		printf("test FAILED: put car in non-empty list\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("test passed: put car in non-empty list\n");
	
	// test remove car from non-empty list
	car_return = lget();
	if (car_return != &car2) {
		printf("test FAILED: remove car from non-empty list\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("test passed: remove car from non-empty list\n");
	printf("car2 plate: %s\n", car_return -> plate);
	car_return = lget();
	if (car_return != &car1) {
		printf("test FAILED: remove car from non-empty list\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("test passed: remove car from non-empty list\n");
	printf("car1 plate: %s\n", car_return -> plate);

	// test remove car from empty list
	car_return = lget();
	if (car_return != NULL) {
		printf("test FAILED: remove car from empty list\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("test passed: remove car from empty list\n");

	// test apply function to every car in list
	lput(&car1);
	lput(&car2);
	lput(&car3);
	lapply(test_apply_fn);
	int year1 = car1.year;
	int year2 = car2.year;
	int year3 = car3.year;
	if ((year1 != 19980) || (year2 != 20450) || (year3 != 19010)) {
		printf("test FAILED: apply function to all cars\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("test passed: apply function to all cars\n");

	// test remove from beginning of list
	lput(&car4);
	car_return = lremove("car4");
	if (car_return != &car4) {
		printf("test FAILED: remove car from beginning of list\n");
		exit(EXIT_FAILURE);
	}
	else {
		printf("test passed: remove car from beginning of list\n");
		print_list(&car3); // should print 3, 2, 1
	}
	
	// test remove from end of list
	lput(&car4);
	car_return = lremove("car1");
	if (car_return != &car1) {
		printf("test FAILED: remove car from end of list\n");
		exit(EXIT_FAILURE);
	}
	else {
		printf("test passed: remove car from end of list\n");
		print_list(&car4); // should print 4, 3, 2
	}

	// test remove from middle of list
	lput(&car1);
	car_return = lremove("car3");
	if (car_return != &car3) {
		printf("test FAILED: remove car from middle of list\n");
		exit(EXIT_FAILURE);
	}
	else {
		printf("test passed: remove car from middle of list\n");
		print_list(&car1); // should print 1, 4, 2
	}

	// test remove car that doesn't exist
	car_return = lremove("car20");
	if (car_return != NULL) {
		printf("test FAILED: remove car not exist\n");
		exit(EXIT_FAILURE);
	}
	else 
		printf("test passed: remove car not exist\n");

	
	exit(EXIT_SUCCESS);
}

