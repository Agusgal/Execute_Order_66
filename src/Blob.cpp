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
}

Blob::Blob(Point_t& maxCoordinates) 
    : currentPosition(maxCoordinates.x, maxCoordinates.y) {
    // Initialize everything
    this->speed = 0;
    this->age = BABYBLOB;
    this->maximumSpeed = 0;
    this->foodCount = 0;
    this->deathChance = 0;
    this->smellRadius = 0;
    this->dimensions = { 0 };

#ifdef DEBUG
    const Point_t* cPos = this->currentPosition.getPosition();
    double ang = this->currentPosition.getAngle();
    std::cout << "Blob in: (" << cPos->x << ", " << cPos->y << ") a = " << ang << std::endl;
#endif

    return;
}
/******************** PUBLIC METHODS ********************/

int Blob::getAge(void) {
    return this->age;
}

void Blob::die(void) {
    this->speed = 0;
    this->age = BABYBLOB;
    this->maximumSpeed = 0;
    this->foodCount = 0;
    this->deathChance = 0;
    this->smellRadius = 0;
    this->dimensions.height = 0;
    this->dimensions.width = 0;

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

void Blob::grow(void) {
    if (this->age == GOODOLDBLOB) {
        return;
    }

    this->age++;
    this->foodCount = 0;
    return;
}

void Blob::move(const double modulus) {
    currentPosition.update(modulus);
    return;
}
void Blob::sayHi(void) {
    /*switch (this->age)
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
    */
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

void Blob::getPoint(double& x, double& y) {
    this->currentPosition.getPosition(x, y);
    return;
}

bool Blob::setDeathChance(double chance) {
    if (islessequal(chance, 0.0) || isgreaterequal(chance, 1.0)) {
        std::cout
            << "Death chance must be a value in range (0.0 ; 1.0)."
            << std::endl;
        return false;
    }
    
    this->deathChance = chance;
    return true;
}

bool Blob::setDimensions(Size_t& newDim) {
    return this->setDimensions(newDim.width, newDim.height);
}

bool Blob::setDimensions(double newWidth, double newHeight) {
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

bool Blob::setPointingDirection(double newAngle) {
    this->currentPosition.rotate(newAngle);
    return true;
}

bool Blob::setPointingDirection(double x, double y) {
    double blobX = 0, blobY = 0;
    double newAngle = 0;

    this->currentPosition.getPosition(blobX, blobY);
    
    newAngle = atan2(y - blobY, x - blobX);

    this->currentPosition.rotateRadians(newAngle);
    return true;
}

bool Blob::setMaximumSpeed(double newMaxSpeed) {
    if (islessequal(newMaxSpeed, 0.0)) {
        std::cout
            << "A blob's maximum speed must be greater than zero."
            << std::endl;
        return false;
    }

    this->maximumSpeed = newMaxSpeed;
    return true;
}

bool Blob::setSmellRadius(double radius) {
    if (islessequal(radius, 0.0)) {
        std::cout
            << "Smell radius must be greater than zero."
            << std::endl;
        return false;
    }
    
    this->smellRadius = radius;
    return true;
}

void Blob::setAwayFromBlob(double x, double y) {
    this->currentPosition.displace(x, y);
}

/******************** PRIVATE METHODS ********************/
