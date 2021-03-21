#include <iostream>
#include <cmath>

#include "Blob.h"


/******************** DEFINITIONS ********************/

/******************** MACROS ********************/
/******************** CONSTRUCTOR ********************/
Blob::Blob(Point_t& maxCoordinates, Sprite spritesArray[NBLOBS],
    double maxSpeed, 
    double smellRadius[NBLOBS],
    double deathChance[NBLOBS]) 
    : currentPosition(maxCoordinates.x, maxCoordinates.y) {

#ifdef DEBUG
    std::cout << "Blob constructor called." << std::endl;
    std::cout 
        << "Blob(" 
            << "maxCoordinates.x = " << maxCoordinates.x << "maxCoordinates.y = " << maxCoordinates.y
            << maxSpeed  << ", "
            << "[" << smellRadius[BABYBLOB] << " .. ]"
            << "[" << deathChance[BABYBLOB] << ", " << deathChance[GROWNBLOB] << ", " << deathChance[GOODOLDBLOB] << "]" << ", "
        <<  ")" 
        << std::endl;
#endif

    // Initialize everything
    this->speed = 0;
    this->age = BABYBLOB;
    this->maximumSpeed = 0;
    this->foodCount = 0;
    this->deathChanceByAge = NULL;
    this->smellRadiusByAge = NULL;
    this->maximumPosition = { 0 };
    this->sprites = NULL;

    // Valid arguments
    if (islessequal(maxSpeed, 0.0)) {
        std::cout << "Maximum speed must be greater than 0." << std::endl;
    }
    else if (spritesArray == NULL) {
        std::cout << "Recieved NULL pointer for sprites." << std::endl;
        return;
    }

    for (int i = BABYBLOB; i < NBLOBS; i++) {
        if (islessequal(deathChance[i], 0.0)) {
            std::cout 
                << "Death chance must be greater than 0 for all ages." 
                << std::endl;
            return;
        }
        else if (islessequal(smellRadius[i], 0.0)) {
            std::cout 
                << "Smell radius must be greater than 0 for all ages."
                << std::endl;
            return;
        }
    }

    this->age = BABYBLOB;
    this->foodCount = 0;

    this->deathChanceByAge = deathChance;
    this->smellRadiusByAge = smellRadius;

    this->maximumSpeed = maxSpeed;
    this->maximumPosition = maxCoordinates;

    this->sprites = spritesArray;
}
/******************** PUBLIC METHODS ********************/

void Blob::die(void) {
    this->speed = 0;
    this->age = BABYBLOB;
    this->maximumSpeed = 0;
    this->foodCount = 0;
    this->deathChanceByAge = NULL;
    this->smellRadiusByAge = NULL;
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

double Blob::getDeadthChance(void) {
    return this->deathChanceByAge[this->age];
}

double Blob::getSmellRadius(void) {
    return this->smellRadiusByAge[this->age];
}

double Blob::getMaximumSpeed(void) {
    return this->maximumSpeed;
}

const Sprite* Blob::getBlobSprite(void) {
    return &(this->sprites[this->age]);
}

void Blob::getCoordinates(double& x, double& y, double& angle) {
    this->currentPosition.getPosition(x, y);
    this->currentPosition.getAngle(angle);
    return;
}

/******************** PRIVATE METHODS ********************/
