#define _USE_MATH_DEFINES   /* For M_PI */

#include <iostream>
#include <cmath> /* M_PI, sin(), cos(), isgreater, isless */

#include "randomGenerators.h"
#include "Coordinates.h"

/******************** DEFINITIONS ********************/

/******************** MACROS ********************/
// Convert degree in radians
#define DEG2RAD(d)      ((d)*(M_PI/180))


/******************** NAMESPACES ********************/
using namespace std;

/******************** CONSTRUCTOR ********************/
Coordinates::Coordinates() {
    cout << "Coordinates() called" << endl;
    x = 0.0;
    y = 0.0;
    angle = 0.0;
 }

Coordinates::Coordinates(int maxX, int maxY) {
    cout << "Coordinates(int, int) called" << endl;
    
    x = generateRandomNumber(maxX);
    y = generateRandomNumber(maxY);
    angle = generateRandomAngle();
}

/******************** PUBLIC METHODS ********************/
void Coordinates::rotate(const double angle) {
    cout << "Rotate: " << angle << endl;

    // Angles that fall out of range (-360.0 ; 360.0) are taken back to this range
    if (isgreaterequal(fabs(angle), 360.0)) {
        this->angle += fmod(angle, 360.0);
    }
    else {
        this->angle += angle;
    }

    // Verify that the new angle does not fall out of range.
    /*
     * As the desired angle has been taken back to range in the previos step,
     * this time it will always be in range (-360.0 ; 360.0).
     * Then, if it's negative, we just take its absolute value.
     */
    if (isless(this->angle, 0.0)) {
        //                    |--- This is between [0; 360.0)
        //                    |--- But the original intention was to rotate on the other direction...
        //                    |--- So we substract it from 360.0.
        this->angle = 360.0 - fmod(fabs(this->angle), 360.0);
    }
    else if (isgreaterequal(this->angle, 360.0)) {
        this->angle = fmod(this->angle, 360.0);
    }

    return;
 }

void Coordinates::update(double modulus) {
    cout << "Update (" << modulus << ")" << endl;


    if (islessequal(modulus, 0.0)) {
        cout << "Modulus must be greater than 0.0" << endl;
        return;
    }

    // Fix bad angles
    if (isless(this->angle, 0.0) || isgreaterequal(this->angle, 360.0)) {
        cout << "An invalid angle has been set. Fixing..." << endl;
        rotate(0.0);
    }

    /*
     * Taking into account that 0� is pointing to the North, that x increases
     * to the east and y to the south, a graphic to understand which signs to apply
     * on the arithmetics could be this one:
     *
     * Let 'a' be an angle between the direction vector and the North (0�).
     * Let 'H' be the modulus of the direction vector.
     * Let 'R' be a robor in some coordinatas (x,y) of the board.
     *
     *  -----------------------------------------> x
     *  |                         /\
     *  |                    ^    /
     *  |                    |_a_/    X increases:   H*sin(a) (X is positive to the east)
     *  |                    |  /     Y increases: - H*cos(a) (Y is negative to the north)
     *  |             <----- R ----->
     *  |                    |
     *  |                    |
     *  |                   \ /
     * \ /
     *  y
     *
     * The same idea can be extrapolated to the other quadrants.
     *
     */
     // 0 <= angle < 90
    if (isless(this->angle, 90.0)) {
        this->x += modulus * sin(DEG2RAD(this->angle));
        this->y -= modulus * cos(DEG2RAD(this->angle));
    }
    // 90 <= angle < 180
    else if (isless(this->angle, 180.0)) {
        this->x += modulus * sin(DEG2RAD(this->angle - 90));
        this->y += modulus * cos(DEG2RAD(this->angle - 90));
    }
    // 180 <= angle < 270
    else if (isless(this->angle, 270.0)) {
        this->x -= modulus * sin(DEG2RAD(this->angle - 180));
        this->y += modulus * cos(DEG2RAD(this->angle - 180));
    }
    // 270 <= angle < 360
    else if (isless(this->angle, 360.0)) {
        this->x -= modulus * sin(DEG2RAD(this->angle - 270));
        this->y -= modulus * cos(DEG2RAD(this->angle - 270));
    }

    return;
 }
