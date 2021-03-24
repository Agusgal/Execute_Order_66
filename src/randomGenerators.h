#ifndef RANDOM_GENERATORS_H
#define RANDOM_GENERATORS_H  1

/******************** DEFINITIONS ********************/
// Default decimal precision taken into account when generating float and double
#define MINIMUM_PRECISION	    (5)

/******************** MACROS ********************/

/******************** PROTOTYPES ********************/
/*
 * Initialize random seed.
 * 
 * Wrapper around srand(time(NULL))
 * 
 * Parameters:
 *  None
 * Returns:
 *  Nothing
 */
void initRandom(void);

/*
 * Generate a random number in range [0;maximum).
 * 
 * Assumes srand() has already been initialized with a seed.
 * 
 * Parameters:
 *  maximum: Number upper limit. Must be greater than 0.
 *  precision: Maximum number of many decimals to generate for the number.
 * 
 * Returns:
 *  Number between 0 and maximum with _precision_ decimals.
 * 
 * Returns:
 *  Number between 0 and maximum with _precision_ decimals:a
 */
double generateRandomNumber(double maximum, unsigned int precision = MINIMUM_PRECISION);

/*
 * Generate a random angle in range 0.0 <= angle < 360.0.
 *
 * Assumes that srand() has been already initialized with a seed.
 *
 * Parameters:
 *  precision: Maximum number of many decimals to generate for the angle.
 *
 * Returns:
 *  Number in range [0.0;360.0) with at most _precision_ decimals.
 */
double generateRandomAngle(unsigned int precision = MINIMUM_PRECISION);

#endif /*! RANDOM_GENERATORS_H*/