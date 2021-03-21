#include <iostream>

#include "randomGenerators.h"
#include "Food.h"

/******************** DEFINITIONS ********************/

/******************** MACROS ********************/

/******************** CONSTRUCTOR ********************/

/******************** PUBLIC METHODS ********************/
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
    this->current.x = generateRandomNumber((unsigned)this->maximum.x);
    this->current.y = generateRandomNumber((unsigned)this->maximum.y);
    return;
}
