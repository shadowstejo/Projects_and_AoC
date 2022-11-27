/*
 *  Stephan Jokiel
 *  Maxine Rahlfes
*/

#include "base.h"
#include <math.h>

//template code

char *brands[] = {"VW", "BMW", "Mercedes", "Fiat", "Ford", "Dacia", "Audi", "Citroen"};
int brand_count = sizeof(brands) / sizeof(char *);
int min_year = 1950;
int max_year = 2017;
int max_km = 250000;


struct Car {
    char *brand;
    int year;
    int km;
    double price;
};

typedef struct Car Car;

//print car information
void print_car(Car *car) {
    printf("Caryear: %4d\tbrand: %8s\tKM: %6dkm\tPrice: %8.2lfEuro\n", car->year, car->brand, car->km, car->price);
}

//print carArray
void print_car_array(Car *car_park, int car_count) {
    for (int i = 0; i < car_count; i++) {
        print_car(car_park + i);
    }
}


// Creates an array with random cars. Returns a pointer to the array.
Car *create_car_park(int car_count) {
    //next statement is part of the following lectures. Don't worry.
    Car *car = (Car *) xmalloc(sizeof(Car) * car_count);

    //fill the array with random cars
    for (int i = 0; i < car_count; i++) {
        int random_brand_index = i_rnd(brand_count); // car brand index in interval: [0,7]

        car[i].brand = brands[random_brand_index];
        int random_year = i_rnd(max_year - min_year) + min_year; //years between min and max year
        car[i].year = random_year;

        int random_km = 0;
        // On MinGW: max random number is 32767. To overcome this two 16 bit random numbers are glued together.
        if (RAND_MAX == 32767) {
            random_km = (i_rnd(max_km >> 16) << 16) | i_rnd(max_km); //dirty hack
        } else {
            random_km = i_rnd(max_km);
        }
        car[i].km = random_km; //max 250.000km

        car[i].price = 30000.00 * pow(0.85, (random_year - min_year)) +
                       20000.00 * pow(0.75, random_km / 10000.0); // car price max 50.000 Euro
    }
    return car;
}

// Deletes a car array. Call the function, when you don't need the array anymore.
void delete_car_park(Car *cars) {
    free(cars);
}


//end of template code
//now it is your turn ...

// (a)

int compare(Car car1, Car car2) {
    int rv;
    if (car1.year == car2.year) {
        rv = strcmp(car1.brand, car2.brand);

    } else if (car1.year > car2.year) {
        rv = 1;
    } else {
        rv = -1;
    }
    return rv;
}

// (b)

Car make_car(char *brand, int year, int km, double price) {
    Car c = {brand, year, km, price};
    return c;
}

void compare_test(void) {

    test_equal_i(compare
                         (make_car("VW", 1982, 17000, 200050),
                          make_car("BMW", 1982, 17000, 200050)),
                 1);
    test_equal_i(compare
                         (make_car("VW", 1981, 17000, 200050),
                          make_car("VW", 1982, 17000, 200050)),
                 -1);
    test_equal_i(compare
                         (make_car("VW", 1982, 17000, 200050),
                          make_car("BMW", 1982, 17000, 200050)),
                 1);
    test_equal_i(compare
                         (make_car("VW", 1982, 17000, 200050),
                          make_car("VW", 1982, 17000, 200050)),
                 0);
    test_equal_i(compare
                         (make_car("BMWW", 1982, 17000, 200050),
                          make_car("VW", 1982, 17000, 200050)),
                 -1);
}

// (c)

bool sorted(Car *a, int length) {
    bool rv = true;
    for (int i = 0; i < length - 1; i++) {
        if (compare(a[i], a[i + 1]) > 0) {
            rv = false;
            break;
        }
    }
    return rv;
}

// (d,e)

int random_sort(Car *a, int length) {
    int swaps = 0;
    while (true) {
        swaps++;
        int i = i_rnd(length);
        int j = i_rnd(length);

        if ((i < j && compare(a[i], a[j]) > 0) || (j < i && compare(a[j], a[i]) > 0)) {
            Car c = a[i];
            a[i] = a[j];
            a[j] = c;
        }
        if (sorted(a,
                   length)) {          //die compere-funktion wird ungefähr "swaps * (length / 2)" -Mal aufgerufen.
            break;
        }
    }
    return swaps;
}

// (b)
int main(void) {

    compare_test();
    int number_of_random_cars = 10;
    Car *car_park = create_car_park(number_of_random_cars);
    print_car_array(car_park, number_of_random_cars);

    printf("Sorting...\n");

    // (c)
    int swaps = random_sort(car_park, number_of_random_cars);
    printf("times of swaps: %d\n", swaps);

    print_car_array(car_park, number_of_random_cars);

    delete_car_park(car_park);
    println();

    // (f)
    for (int i = 0; i < 5; i++) {
        int n = 3 + i_rnd(8);
        printf("Arraysize: %d\n", n);
        int test_swaps = 0;
        for (int t = 0; t < 100; t++) {
            int n = 3;
            Car *new_cars = create_car_park(n);
            int x = random_sort(new_cars, n);
            test_swaps += x;
        }
        int median_swaps = test_swaps / 100;
        printf("Median Swaps: %d for array-size n: %d\n", median_swaps, n);
    }

    return 0;
}
