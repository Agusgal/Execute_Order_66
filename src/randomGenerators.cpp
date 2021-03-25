#include <iostream>
#include <cstdlib> /* srand(), rand() */
#include <ctime> /* time() */
#include <cmath>
#include "randomGenerators.h"

/******************** DEFINITIONS ********************/

/******************** MACROS ********************/

/******************** PROTOTYPES ********************/
static long int ipow(unsigned int base, unsigned int exponent);
static double generateRandomDouble(unsigned long int max, unsigned int precision = MINIMUM_PRECISION);

/******************** PUBLIC FUNCTIONS ********************/
void
initRandom(void) {
    srand(((unsigned int) time(NULL)) * ((unsigned int) clock()));
    return;
}

double
generateRandomNumber(double maximum, unsigned int originalPrecision) {
    /*if (islessequal(maximum, 0.0)) {
        std::cout << "randomGenerators -> generateRandomNumber: Invalid maximum value." << std::endl;
        return 0.0;
    }*/
    if (islessequal(maximum, 0.0)) {
        if (isless(maximum, 0.0)) {
            maximum = fabs(maximum);
        }
        else {
            return 0.0;
        }
    }

    double intPart = 0, decPart = 0, intPartMax = 0, decPartMax = 0; //Integer part (variable), decimal part (variable), integer part of maximum number, decimal part of maximum number
    unsigned long int aux1 = (unsigned long int) (maximum * ipow(10, originalPrecision)); //Convert maximum to unsigned long int without decimal separator
    aux1 -= (aux1 % ipow(10, originalPrecision)); //Substract to leave only the integer part of the maximum number
    aux1 = aux1 / ipow(10, originalPrecision); //Divide by (10 times the number of decimal digits) to get the integer part of the maximum number
    intPartMax = (double)aux1; //Convert to double to get intPartMax value
    decPartMax = maximum - intPartMax; //Substract to get decPartMax value. This will result in the random number not having decimal part if _maximum_ is an integer
    intPart = generateRandomDouble((unsigned long) intPartMax, 0); //Generate a random integer part for the random number
    if ((maximum - intPart) >= 1) //If _maximum_ is an integer or (maximum - intPart) is greater than one, this allows to get a decimal value from 0 to 1. Because of this, the returned
                                    //number is able to be equal to _maximum_
        decPart = generateRandomDouble(ipow(10, originalPrecision), 0);
    else    //If (minimum - intPart) is less than 1, restrict the decimal part to the original value. This allows non-integers to have decimal part
        decPart = generateRandomDouble(((unsigned long)decPartMax) * ipow(10, originalPrecision), 0);
    decPart /= ipow(10, originalPrecision); //Divide to convert to decimal
    return (intPart + decPart); //Then the random number is the sum of the integer part and the decimal part
}

double
generateRandomAngle(unsigned int precision) {
    return generateRandomDouble(360, precision);
}

/******************** STATIC FUNCTIONS ********************/
static double
generateRandomDouble(unsigned long int max, unsigned int precision) {
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
