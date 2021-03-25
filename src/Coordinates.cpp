#define _USE_MATH_DEFINES   /* For M_PI */

#include <iostream>
#include <cmath> /* M_PI, sin(), cos(), isgreater, isless */

#include "randomGenerators.h"
#include "Coordinates.h"

/******************** DEFINITIONS ********************/

/******************** MACROS ********************/
// Convert degrees in radians
#define DEG2RAD(d)      ((d)*M_PI/180.0)
// Convert radians in degrees
#define RAD2DEG(r)      ((r)*180.0/M_PI)

/******************** CONSTRUCTOR ********************/
Coordinates::Coordinates() {
//#ifdef DEBUG
//    std::cout << std::endl << "---DEBUG---" << std::endl;
//    std::cout << "Coordinates() called" << std::endl;
//    std::cout << "***DEBUG***" << std::endl;
//#endif

    this->maximumCoordinates = { 0 };
    this->position = { 0 };
    angle = 0.0;
 }

Coordinates::Coordinates(double maxX, double maxY) {
//#ifdef DEBUG
//    std::cout << std::endl << "---DEBUG---" << std::endl;
//    std::cout 
//        << "Coordinates(maxX = " 
//        << maxX
//        << ", maxY = "
//        << maxY
//        << ")"
//        << std::endl;
//    std::cout << "***DEBUG***" << std::endl;
//#endif

    this->maximumCoordinates = { 0 };
    this->position = { 0 };
    this->angle = 0;

    if (islessequal(maxX, 0.0) || islessequal(maxY, 0.0)) {
        std::cout << "Both maxX and maxY must be greater than 0.0" << std::endl;
        return;
    }
    
    this->maximumCoordinates.x = maxX;
    this->maximumCoordinates.y = maxY;

    // TODO: Handle floating point in random number generation
    this->position.x = generateRandomNumber(this->maximumCoordinates.x);
    this->position.y = generateRandomNumber(this->maximumCoordinates.y);
    angle = generateRandomAngle();
    
    return;
}

/******************** PUBLIC METHODS ********************/
void Coordinates::rotateRadians(const double angleInRadians) {
    /*if (isgreater(newAngle, 1.0)) {
        newAngle = this->angle + (this->angle - newAngle);
    }
    else if (isless(newAngle, 1.0)) {
        newAngle = this->angle - (this->angle - newAngle);
    }*/

    //double tmp = RAD2DEG(angleInRadians);
    //if (isgreaterequal(tmp, 0.0) && isless(tmp, 90.0) 
    //    || isgreaterequal(tmp, 180.0) && isless(tmp, 270.0))


    this->angle = RAD2DEG(angleInRadians);
    //this->rotate(RAD2DEG(angleInRadians));
    /*
#ifdef DEBUG
    std::cout
        << ""
        << std::endl;
#endif*/
    return;
}
void Coordinates::rotate(const double rotationAngle) {
//#ifdef DEBUG
//    std::cout << std::endl << "---DEBUG---" << std::endl;
//    std::cout << "Rotate: " << rotationAngle << std::endl;
//    std::cout << "***DEBUG***" << std::endl;
//#endif

    // Angles that fall out of range (-360.0 ; 360.0) are taken back to this range
    if (isgreaterequal(fabs(rotationAngle), 360.0)) {
        this->angle += fmod(rotationAngle, 360.0);
    }
    else {
        this->angle += rotationAngle;
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

void Coordinates::update(const double modulus) {
//#ifdef DEBUG
//    std::cout << std::endl << "---DEBUG---" << std::endl;
//    std::cout << "Update (" << modulus << ")" << std::endl;
//    std::cout << "***DEBUG***" << std::endl;
//#endif

    if (islessequal(modulus, 0.0)) {
        return;
    }

    // Fix bad angles
    /*if (isless(this->angle, 0.0) || isgreaterequal(this->angle, 360.0)) {
        std::cout << "An invalid angle has been set. Fixing..." << std::endl;
        rotate(0.0);
    }*/

    /*
     * Taking into account that 0° is pointing to the North, that x increases
     * to the east and y to the south, a graphic to understand which signs to apply
     * on the arithmetics could be this one:
     *
     * Let 'a' be an angle between the direction vector and the North (0°).
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
    /*if (isless(this->angle, 90.0)) {
        this->position.x += modulus * sin(DEG2RAD(this->angle));
        this->position.y -= modulus * cos(DEG2RAD(this->angle));
    }
    // 90 <= angle < 180
    else if (isless(this->angle, 180.0)) {
        this->position.x += modulus * sin(DEG2RAD(this->angle - 90));
        this->position.y += modulus * cos(DEG2RAD(this->angle - 90));
    }
    // 180 <= angle < 270
    else if (isless(this->angle, 270.0)) {
        this->position.x -= modulus * sin(DEG2RAD(this->angle - 180));
        this->position.y += modulus * cos(DEG2RAD(this->angle - 180));
    }
    // 270 <= angle < 360
    else if (isless(this->angle, 360.0)) {
        this->position.x -= modulus * sin(DEG2RAD(this->angle - 270));
        this->position.y -= modulus * cos(DEG2RAD(this->angle - 270));
    }*/

    this->position.x += modulus * cos(DEG2RAD(this->angle));
    this->position.y += modulus * sin(DEG2RAD(this->angle));

    // Stay inside bounds
    if (isgreaterequal(this->position.x, this->maximumCoordinates.x)) {
        this->position.x -= this->maximumCoordinates.x;
    }

    if (isgreaterequal(this->position.y, this->maximumCoordinates.y)) {
        this->position.y -= this->maximumCoordinates.y;
    }

    if (isless(this->position.x, 0.0)) {
        this->position.x += this->maximumCoordinates.x;
    }

    if (isless(this->position.y, 0.0)) {
        this->position.y += this->maximumCoordinates.y;
    }


    return;
 }

void Coordinates::getPosition(double& x, double& y) {
//#ifdef DEBUG
//    std::cout << std::endl << "---DEBUG---" << std::endl;
//    std::cout
//        << "X: " << this->position.x
//        << "Y: " << this->position.y
//        << std::endl;
//    std::cout << "***DEBUG***" << std::endl;
//#endif
    x = this->position.x;
    y = this->position.y;
    return;
}

const Point_t* Coordinates::getPosition(void) {
    return &(this->position);
}

void Coordinates::getAngle(double& ang) {
    ang = this->angle;
    return;
}

double Coordinates::getAngle(void) {
    return this->angle;
}

void Coordinates::displace(double x, double y) {
    this->position.x += x;
    this->position.y += y;
    this->update(1.0);
}

/******************** PRIVATE METHODS ********************/
