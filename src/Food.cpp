#include <iostream>

#include "randomGenerators.h"
#include "Food.h"

/******************** DEFINITIONS ********************/

/******************** MACROS ********************/

/******************** CONSTRUCTOR ********************/

Food::Food(unsigned int maxX, unsigned int maxY) {
    this->current = { 0 };
    this->maximum = { 0 };
    
    if (maxX == 0 || maxY == 0) {
        std::cout 
            << "Please provide a value greater than 0 for both maxX and maxY." 
            << std::endl;
        return;
    }

    this->maximum.x = maxX;
    this->maximum.y = maxY;
    this->generatePosition();
}

Food::Food(Point_t& maxCoordinates) {
    this->current = { 0 };
    this->maximum = { 0 };
    
    if (maxCoordinates.x == 0 || maxCoordinates.y == 0) {
        std::cout 
            << "Please provide a value greater than 0 for both X and Y." 
            << std::endl;
        return;
    }

    this->maximum.x = maxCoordinates.x;
    this->maximum.y = maxCoordinates.y;
    this->generatePosition();
}

/******************** PUBLIC METHODS ********************/
void Food::destroy(void) {
    this->current.x = 0;
    this->current.y = 0;
    this->maximum.x = 0;
    this->maximum.y = 0;
    return;
}

void Food::getPosition(double& x, double& y) {
    x = this->current.x;
    y = this->current.y;
    return;
}

const Point_t* Food::getPosition(void) {
    return &(this->current);
}

void Food::updatePosition(void) {
    this->generatePosition();
    return;
}

void Food::updateAndGetPosition(double& newX, double& newY) {
    this->generatePosition();
    newX = this->current.x;
    newY = this->current.y;
    return;
}

const Point_t* Food::updateAndGetPosition(void) {
    this->generatePosition();
    return &(this->current);
}

/******************** PRIVATE METHODS ********************/
void Food::generatePosition(void) {
    // TODO: Handle floating point
    this->current.x = generateRandomNumber(this->maximum.x);
    this->current.y = generateRandomNumber(this->maximum.y);

#ifdef DEBUG
    std::cout << "Food in: (" << this->current.x << ", " << this->current.y << ")" << std::endl;
#endif
    return;
}
