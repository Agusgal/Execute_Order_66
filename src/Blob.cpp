#include <iostream>
#include <cmath>

#include "Blob.h"


/******************** DEFINITIONS ********************/

/******************** MACROS ********************/
/******************** CONSTRUCTOR ********************/
Blob::Blob(Point_t& maxCoordinates, Sprite sprites[NBLOBS],
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
}
/******************** PUBLIC METHODS ********************/
double Blob::getDeadthChance(void) {
    return this->deathChanceByAge[this->age];
}

double Blob::getSmellRadius(void) {
    return this->smellRadiusByAge[this->age];
}

void Blob::printDeathChance(void) {
    std::cout << "Pointer: " << deathChanceByAge << std::endl;
    std::cout << "[";
    for (int i = BABYBLOB; i < NBLOBS; i++) {
        std::cout << this->deathChanceByAge[i] << ", ";
    }
    std::cout << "]" << std::endl;

}

void Blob::printCoordinates(void) {
    double x = 0, y = 0, currangle = 0;
    this->currentPosition.getPosition(&x, &y);
    this->currentPosition.getAngle(currangle);

    std::cout << "Position: (" << x << ", " << y << ")" << std::endl;
    std::cout << "Angle: "<< currangle<< std::endl;
}

/*
bool Blob::birdth(void) {
    bool newBirdth = false;
    switch (this->age) {
        case BABYBLOB:
            if (this->foodCount == FOOD_BABYBLOB) {
                newBirdth = true;
            }
            break;
        case GROWNBLOB:
            if (this->foodCount == FOOD_GROWNBLOB) {
                newBirdth = true;
            }

            break;
        case GOODOLDBLOB:
            if (this->foodCount == FOOD_GOODOLDBLOB) {
                newBirdth = true;
            }
            break;
        default:
            newBirdth = false;
            break;
    }
    return newBirdth;
}

void Blob::grow(void) {
    if (this->age == GOODOLDBLOB) return;

    this->blobBirthday();
}
*/
/******************** PRIVATE METHODS ********************/

/*
void Blob::blobBirthday(void) {
    if (this->age == GOODOLDBLOB) return;

    this->age++;
    this->foodCount = 0;
    this->deathChance = this->deathChanceByAge[this->age];
}
*/
