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

int main(void) {
	int32_t res = 0;
	car_t car1 = { .*next = NULL, .plate = "12345", .price = 2000.99, .year = 1998 };
	car_t car2 = { .*next = NULL, .plate = "gtses", .price = 1111100.25, .year = 2045 };
	car_t car_return;
	res = lput(&car1);
	if (res != 0)
		exit(EXIT_FAILURE);

	res = lput(&car2);
	if (res != 0)
		exit(EXIT_FAILURE);

	car_return = lget();
	if (car_res != &car2)
		exit(EXIT_FAILURE);
	printf("car2 plate: %s", *car_return -> plate);

	car_return = lget();
	if (car_res != &car1)
		exit(EXIT_FAILURE);
	car_return = lget();
	if (car_return != NULL)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
