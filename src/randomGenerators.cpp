#include <iostream>
#include <cstdlib> /* srand(), rand() */
#include <ctime> /* time() */
#include "randomGenerators.h"

/******************** DEFINITIONS ********************/

/******************** MACROS ********************/

/******************** PROTOTYPES ********************/
static long int ipow(unsigned int base, unsigned int exponent);
static double generateRandomDouble(int max, unsigned int precision = MINIMUM_PRECISION);

/******************** PUBLIC FUNCTIONS ********************/
void
initRandom(void) {
    srand((unsigned int) time(NULL));
    return;
}

double
generateRandomNumber(unsigned int maximum, unsigned int precision) {
    if (maximum == 0) {
        std::cout << "Invalid maximum value: 0" << std::endl;
        return 0.0;
    }

    return generateRandomDouble(maximum, precision);
}

double
generateRandomAngle(unsigned int precision) {
    return generateRandomDouble(360, precision);
}

/******************** STATIC FUNCTIONS ********************/
static double
generateRandomDouble(int max, unsigned int precision) {
    // Generate two random numbers:
    // .- Integer part ( 0 <= integer < max)
    // .- Decimal part ( 0 <= decimal < 10^(precision) )
    // This will let us create the double with _precision_ decimal digits.
    if (max == 0) {
        std::cout << "Invalid maximum value." << std::endl;
        return 0.0;
    }

    int integer = rand() % max;

    // Uses custom pow function which only works with integers.
    // (math lib's pow() uses doubles... seems overkill)
    // Just in case, we take the absolute value of _precision_.
    int decimal = rand() % ipow(10, precision);

    // Integer part + decimal part 
    return (double)(integer + (((double)decimal) / ipow(10, precision)));
}

/*
 * Raise base to exponent using only integers.
 *
 * As math library does not provide a pow() function to work with pure
 * integers, I've made a simple one based on _Exponentiation by squaring_
 * method (also known as _binary exponentiation_).
 * See more at: https://en.wikipedia.org/wiki/Exponentiation_by_squaring
 *
 * Arguments:
 *  base: Power base.
 *  exponent: Power exponent.
 *
 * Returns:
 *  Success: base^exponent
 *  Failure: -1 (i.e. when trying to perform 0^0)
 */
static long int
ipow(unsigned int base, unsigned int exponent) {
    if (base == 0 && exponent == 0) {
        return -1;
    }

    if (base == 1) {
        return 1;
    }
    else if (base == 0) {
        return 0;
    }
    else if (exponent == 0) {
        return 1;
    }

    int result = 1;
    while (1) {
        // Is exponent odd?
        if (exponent & 1) {
            result *= base;
        }

        // Shift exponent to the left (same as divide by 2)
        exponent >>= 1;
        if (!exponent) {
            break;
        }

        base *= base;
    }

    return result;
}
