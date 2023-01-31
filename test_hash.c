/* test_hash.c --- test file for hashtable
 * 
 * 
 * Author: Raif T. Olson, Cameron Wolfe, and Hannah Brookes
 * Created: Thu Jan 26 11:49:37 2023 (-0500)
 * Version: 1.0
 * 
 * Description: 
 * 
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#define MAXREG 10

typedef struct car {
	char plate[MAXREG];
	double price;
	int year;
} car_t;

void doublePrice(void* ep);
bool plateMatch(void* elementp, const void* keyp);

int main(void) {

    // Open hashtable
	hashtable_t* hashtable = hopen(MAXREG);
    hashtable_t* hashtable2 = hopen(MAXREG); // Leave empty for valgrind check

    // Create cars
	car_t car1 = { .plate = "car1", .price = 2000.99, .year = 1998 };
	car_t car2 = { .plate = "car2", .price = 1111100.25, .year = 2045 };
	car_t car3 = { .plate = "FXO-249", .price = 18000, .year = 2017 };
    
	car_t car1copy = { .plate = "car1", .price = 2000.99, .year = 1998 };
	car_t car2copy = { .plate = "car2", .price = 1111100.25, .year = 2045 };
	car_t car3copy = { .plate = "FXO-249", .price = 18000, .year = 2017 };

    // Add elements to table
	int32_t result1 = hput(hashtable, &car1, car1.plate, sizeof(car1.plate));
    if (result1 != 0) {
			printf("Failed adding element to table. Err: %d\n", result1);
			exit(EXIT_FAILURE);
    }
    printf("Passed adding element to table\n");

	int32_t result2 = hput(hashtable, &car2, car2.plate, sizeof(car2.plate));
    if (result2 != 0) {
        printf("Failed adding second element to table\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed adding second element to table\n");

	int32_t result3 = hput(hashtable, &car3, car3.plate, sizeof(car3.plate));
    if (result3 != 0) {
        printf("Failed adding third element to table\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed adding third element to table\n");
    
    // Apply function to populated table
    happly(hashtable, doublePrice);
    if (car1.price != car1copy.price * 2 ||car2.price != car2copy.price * 2 || car3.price != car3copy.price * 2) {
        printf("Failed applying function to populated table\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed applying function to populated table\n");

    // Apply function to empty table, should do nothing, so unless it crashes 
    // we shouldn't have a problem
    happly(hashtable2, doublePrice);
    printf("Passed applying function to empty table (did not crash)\n");

    // Search for existing item in table
    car_t* search = (car_t*) hsearch(hashtable, plateMatch, car1.plate, sizeof(car1.plate));
    if (search != &car1) {
        printf("Failed searching for existing item in table\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed searching for existing item in table\n");

    // Search for nonexistent item in table
    car_t* badSearch = (car_t*) hsearch(hashtable, plateMatch, "Boop", sizeof("Boop"));
    if (badSearch != NULL) {
        printf("Failed searching for nonexistent item in table\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed searching for nonexistent item in table\n");

    // Search empty table
    car_t* emptySearch = (car_t*) hsearch(hashtable2, plateMatch, car1.plate, sizeof(car1.plate));
    if (emptySearch != NULL) {
        printf("Failed searching empty table\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed searching empty table\n");

    // Remove existing item in table
    car_t* remove = (car_t*) hremove(hashtable, plateMatch, car1.plate, sizeof(car1.plate));
    car_t* removeSearch = (car_t*) hsearch(hashtable, plateMatch, car1.plate, sizeof(car1.plate));
    if (remove != &car1 || removeSearch != NULL) {
        printf("Failed removing existing item in table\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed removing existing item in table\n");

    // Remove nonexistent item in table
    car_t* badRemove = (car_t*) hremove(hashtable, plateMatch, "Boop", sizeof("Boop"));
    if (badRemove != NULL) {
        printf("Failed removing nonexistent item in table\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed removing nonexistent item in table\n");

    // Remove from empty table
    car_t* emptyRemove = (car_t*) hremove(hashtable2, plateMatch, car1.plate, sizeof(car1.plate));
    if (emptyRemove != NULL) {
        printf("Failed removing from empty table\n");
        exit(EXIT_FAILURE);
    }
    printf("Passed removing from empty table\n");

    // Close out hashtables
    hclose(hashtable);
    hclose(hashtable2);

    printf("\nAll tests passed!\n");
		exit(EXIT_SUCCESS);
}

// Double the price of the car, for qapply testing
void doublePrice(void* ep) {
    car_t* itemPointer = (car_t*) ep;
    itemPointer->price *= 2;
}

// Check to see if a plate is the same as a given string
bool plateMatch(void* elementp, const void* keyp) {
    car_t* car = (car_t*) elementp;
    const char* key = (char*) keyp;
    
    int i = 0;
    while (car->plate[i] == key[i] && !(car->plate[i] == '\0' || key[i] == '\0'))
        i++;

    return car->plate[i] == key[i];
}
    
