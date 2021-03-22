#include <iostream>
#include <cmath>

#include "Blob.h"


/******************** DEFINITIONS ********************/

/******************** MACROS ********************/
/******************** CONSTRUCTOR ********************/
Blob::Blob(
    Point_t& maxCoordinates, Size_t& dimensions,
    double maxSpeed, 
    double deathChance,
    double smellRadius
    ) : currentPosition(maxCoordinates.x, maxCoordinates.y) {

#ifdef DEBUG
    std::cout << "Blob constructor called." << std::endl;
    std::cout 
        << "Blob(" 
            << "maxCoordinates.x = " << maxCoordinates.x << "maxCoordinates.y = " << maxCoordinates.y
            << maxSpeed  << ", "
        <<  ")" 
        << std::endl;
#endif

    // Initialize everything
    this->speed = 0;
    this->age = BABYBLOB;
    this->maximumSpeed = 0;
    this->foodCount = 0;
    this->deathChance = 0;
    this->smellRadius = 0;
    this->dimensions = { 0 };
    this->maximumPosition = { 0 };

    // Valid arguments
    if (islessequal(maxSpeed, 0.0)) {
        std::cout << "Maximum speed must be greater than 0." << std::endl;
        return;
    }
    else if (islessequal(dimensions.width, 0.0)
        || islessequal(dimensions.height, 0.0)) {
        std::cout
            << "Invalid dimensions for blob."
            << std::endl;
        return;
    }

    if (this->setDeathChance(deathChance) == false) { return; }
    if (this->setSmellRadius(smellRadius) == false) { return; }
    if (this->setDimensions(dimensions) == false) { return;  }

    this->age = BABYBLOB;
    this->foodCount = 0;

    this->maximumSpeed = maxSpeed;
    this->maximumPosition = maxCoordinates;
}
/******************** PUBLIC METHODS ********************/

void Blob::die(void) {
    this->speed = 0;
    this->age = BABYBLOB;
    this->maximumSpeed = 0;
    this->foodCount = 0;
    this->deathChance = 0;
    this->smellRadius = 0;
    this->dimensions.height = 0;
    this->dimensions.width = 0;
    this->maximumPosition.x = 0;
    this->maximumPosition.y = 0;

    return;
}

bool Blob::eat(void) {
    bool newBirdth = false;

    this->foodCount++;
    switch (this->age) {
        case BABYBLOB:
            if (this->foodCount == FOOD_BABYBLOB) {
                newBirdth = true;
                foodCount = 0;
            }
            break;

        case GROWNBLOB:
            if (this->foodCount == FOOD_GROWNBLOB) {
                newBirdth = true;
                foodCount = 0;
            }
            break;

        case GOODOLDBLOB:
            if (this->foodCount == FOOD_GOODOLDBLOB) {
                newBirdth = true;
                foodCount = 0;
            }
            break;

        default:
            newBirdth = false;
            break;
    }

    return newBirdth;
}

void Blob::grow(const double newAngle) {
    if (isless(newAngle, 0.0) || isgreaterequal(newAngle, 360.0)) {
        std::cout << "The Blob's new angle must be in range [0 ; 360.0)." 
            << "\nRecieved: " << newAngle 
            << std::endl;
            return;
    }
    else if (this->age == GOODOLDBLOB) {
        this->sayHi();
        return;
    }

    double currentAngle = this->currentPosition.getAngle();
    this->currentPosition.rotate(-currentAngle); // Set angle to 0°
    this->currentPosition.rotate(newAngle); // Set new angle

    this->age++;
    this->foodCount = 0;
    return;
}

void Blob::move(const double modulus) {
    currentPosition.update(modulus);
    return;
}
void Blob::sayHi(void) {
    switch (this->age)
    {
        case BABYBLOB:
            std::cout << "Baby blob: ";
            break;
        case GROWNBLOB:
            std::cout << "Grown blob: ";
            break;
        case GOODOLDBLOB:
            std::cout << "Good Old blob: ";
            break;
        default:
            break;
    }
    std::cout << "Hi!" << std::endl;

    return;
}

const Size_t* Blob::getBlobSize(void) {
    return &(this->dimensions);
}

void Blob::getBlobSize(double& width, double& height) {
    width = this->dimensions.width;
    height = this->dimensions.height;
    
    return;
}

double Blob::getDeadthChance(void) {
    return this->deathChance;
}

double Blob::getMaximumSpeed(void) {
    return this->maximumSpeed;
}

double Blob::getSmellRadius(void) {
    return this->smellRadius;
}

void Blob::getCoordinates(double& x, double& y, double& angle) {
    this->currentPosition.getPosition(x, y);
    this->currentPosition.getAngle(angle);
    return;
}

bool Blob::setDeathChance(double& chance) {
    if (islessequal(chance, 0.0) || isgreaterequal(chance, 1.0)) {
        std::cout
            << "Death chance must be a value in range (0.0 ; 1.0)."
            << std::endl;
        return false;
    }
    
    this->deathChance = chance;
    return true;
}


bool Blob::setSmellRadius(double& radius) {
    if (islessequal(radius, 0.0)) {
        std::cout
            << "Smell radius must be greater than zero."
            << std::endl;
        return false;
    }
    
    this->smellRadius = radius;
    return true;
}

bool Blob::setDimensions(Size_t& newDim) {
    return this->setDimensions(newDim.width, newDim.height);
}

bool Blob::setDimensions(double& newWidth, double& newHeight) {
    if (islessequal(newWidth, 0.0) || islessequal(newHeight, 0.0)) {
        std::cout
            << "Blob's width and height must be greater than zero."
            << std::endl;
        return false;
    }

    dimensions.width = newWidth;
    dimensions.height = newHeight;
    return true;
}

/******************** PRIVATE METHODS ********************/
