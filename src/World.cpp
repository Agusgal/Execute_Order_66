#include <iostream>
#include <cmath> /* isless/equal isgreater/equal */

#include "randomGenerators.h"
#include "World.h"

/******************** DEFINITIONS ********************/

/******************** MACROS ********************/

/******************** CONSTRUCTOR ********************/
World::World(
    double worldWidth, double worldHeight,
    unsigned blobsNumber, unsigned foodAmmount,
    Size_t blobSizeByAge[NBLOBS],
    double deathChance[NBLOBS], double smellRadius[NBLOBS],
    double blobsMaximumSpeed,
    bool blobsMaximumSpeedRandom
) {
    // Initialize everything 
    this->width = 0.0;
    this->height = 0.0;
    this->foodAvailable = 0;
    this->aliveBlobs = 0;
    for (int i = BABYBLOB; i < NBLOBS; i++) {
        this->blobsDeathChance[i] = 0;
        this->blobsSmellRadius[i] = 0;
        this->blobsSize[i] = { 0 };
    }

    // Data validation
    if (islessequal(worldWidth, 0.0) || islessequal(worldHeight, 0.0)) {
        std::cout
            << "World dimensions must be greater than zero."
            << std::endl;
        return;
    }
    else if (blobsNumber == 0) {
        std::cout
            << "Evolution cannot happen without any blobs!"
            << std::endl;
        return;
    }
    else if (foodAmmount == 0) {
        std::cout
            << "No food => No growing => No reproduction => No evolution"
            << std::endl;
        return;
    }
    else if (islessequal(blobsMaximumSpeed, 0.0)) {
        std::cout
            << "Blobs need a maximum speed greater than zero."
            << std::endl;
        return;
    }
    else {
        for (int i = BABYBLOB; i < NBLOBS; i++) {
            if (islessequal(blobSizeByAge[i].width, 0.0) 
                || islessequal(blobSizeByAge[i].height, 0.0)) {
                std::cout
                    << "Invalid blob size. Must have width and height greater than zero."
                    << std::endl;
                return;
            }
            else if (islessequal(deathChance[i], 0.0) || isgreaterequal(deathChance[i], 1.0)) {
                std::cout
                    << "A death chance smaller or equal than 0.0 or "
                    << "greater or equal than 1.0 cannot be set."
                    << std::endl;
                return;
            }
            else if (islessequal(smellRadius[i], 0.0)) {
                std::cout
                    << "Blobs only can smell if their smell radius is greater than zero!"
                    << std::endl;
            }
        }
    }

    this->width = worldWidth;
    this->height = worldHeight;

    for (int i = BABYBLOB; i < NBLOBS; i++) {
        this->blobsDeathChance[i] = deathChance[i];
        this->blobsSmellRadius[i] = smellRadius[i];
        this->blobsSize[i] = blobSizeByAge[i]; 
    }

    //TODO: createBlobs(blobsNumber);
    //TODO: createFood(foodAmmount);

    return;
}

/******************** PUBLIC METHODS ********************/
bool World::checkFood(void) {
    std::cout << "Not implemented." << std::endl;
    return false;
}

bool World::checkMerge(void) {
    std::cout << "Not implemented." << std::endl;
    return false;
}

bool World::status(void) {
    std::cout << "Not implemented." << std::endl;
    return false;
}

bool World::setDeathChance(const int age, const double newChance) {
    if (age < BABYBLOB || age > GOODOLDBLOB) {
        std::cout 
            << "Unable to set death chance of an invalid age."
            << std::endl;
        return false;
    }
    else if (islessequal(newChance, 0.0) || isgreaterequal(newChance, 1.0)) {
        std::cout
            << "Death chance must be in range (0.0 ; 1.0)."
            << std::endl;
        return false;
    }

    this->blobsDeathChance[age] = newChance;
    // TODO: Set death chance to all blobs this age
    // updateBlobCommons();

    return true;
}

bool World::setSmellRadius(const int age, const double newRadius) {
    if (age < BABYBLOB || age > GOODOLDBLOB) {
        std::cout 
            << "Unable to set smell radius of an invalid age."
            << std::endl;
        return false;
    }
    else if (islessequal(newRadius, 0.0)) {
        std::cout
            << "Smell radius cannot be less or equal than zero."
            << std::endl;
        return false;
    }

    this->blobsSmellRadius[age] = newRadius;
    // TODO: Set smell radius to all blobs this age
    // updateBlobCommons();

    return true;
}


/******************** PRIVATE METHODS ********************/
bool World::mergeBlobs(Blob& blob1, Blob& blob2) {
    std::cout << "Not implemented." << std::endl;
    return false;
}

bool World::eatAndReproduce(Blob& blob) {
    std::cout << "Not implemented." << std::endl;
    return false;
}

bool World::smell(Blob& blob) {
    std::cout << "Not implemented." << std::endl;
    return false;
}
