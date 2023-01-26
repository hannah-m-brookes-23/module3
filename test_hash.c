/* test_hash.c --- test file for hashtable
 * 
 * 
 * Author: Raif T. Olson
 * Created: Thu Jan 26 11:49:37 2023 (-0500)
 * Version: 1.0
 * 
 * Description: 
 * 
 */

#include <stdint.h>

#define MAXREG 10

int main(void) {

	typedef struct car {
		char plate[MAXREG];
		double price;
		int year;
	} car_t;
	
	hashtable_t* hashtable = hopen();

	car_t car1 = { .plate = "car1", .price = 2000.99, .year = 1998 };
	
	car_t car2 = { .plate = "car2", .price = 1111100.25, .year = 2045 };

	hput(hashtable, car1, &car1, &(car1 -> plate), sizeof(car -> plate);
}
