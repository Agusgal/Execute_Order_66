#include <iostream>
#include <cmath> /* isless/equal isgreater/equal */

#include "randomGenerators.h"
#include "World.h"

/******************** DEFINITIONS ********************/
#define EATING_DISTANCE     (1.0)

/******************** MACROS ********************/


long double distance(Point_t& firstPoint, Point_t& secondPoint);

/******************** CONSTRUCTOR ********************/
World::World(
    int worldMode,
    double worldWidth, double worldHeight,
    int blobsNumber, int foodAmmount,
    Size_t blobSizeByAge[NBLOBS],
    float deathChance[NBLOBS], float smellRadius[NBLOBS],
    float blobsMaximumSpeed) {
    // Initialize everything 
    this->mode = MODE_INVALID;
    this->blobsList = NULL;
    this->foodList = NULL;
    this->dimensions = { 0 };
    this->foodAvailable = 0;
    this->aliveBlobs = 0;
    this->blobsMaxSpeed = 0;
    this->blobsMaxSpeedIsRnd = false;
    this->blobsRelativeSpeed = 0;

    for (int i = BABYBLOB; i < NBLOBS; i++) {
        this->blobsDeathChance[i] = 0;
        this->blobsSmellRadius[i] = 0;
        this->blobsSize[i] = { 0 };
    }

    // Data validation
    if (worldMode != MODE_ONE && worldMode != MODE_TWO) {
        std::cout
            << "Invalid world mode. Aborting."
            << std::endl;
        return;
    }
    else if (islessequal(worldWidth, 0.0) || islessequal(worldHeight, 0.0)) {
        std::cout
            << "World dimensions must be greater than zero."
            << std::endl;
        return;
    }
    else if (blobsNumber <= 0) {
        std::cout
            << "Evolution cannot happen without any blobs!"
            << std::endl;
        return;
    }
    else if (foodAmmount <= 0) {
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

    this->mode = worldMode;
    this->dimensions.width = worldWidth;
    this->dimensions.height = worldHeight;

    for (int i = BABYBLOB; i < NBLOBS; i++) {
        this->blobsDeathChance[i] = deathChance[i];
        this->blobsSize[i] = blobSizeByAge[i]; 
        this->blobsSmellRadius[i] = smellRadius[i] + this->blobsSize[i].width; // user's smell radius + blob's size :)
    }

    this->blobsMaxSpeed = blobsMaximumSpeed;
    switch (this->mode) {
        case MODE_ONE:
            this->blobsMaxSpeedIsRnd = false;
            break;
        case MODE_TWO:
            this->blobsMaxSpeedIsRnd = true;
            break;
        default:
            break;
    }

    // Allocate Blob and Food list
    Point_t worldMax = {0};
    worldMax.x = this->dimensions.width;
    worldMax.y = this->dimensions.height;

    this->blobsList = new SDLL(SDLL_DT_BLOB, worldMax);
    if (this->blobsList == NULL) {
        std::cout 
            << "Unable to create blobs list. Aborting."
            << std::endl;
        return;
    }
    // Creating a new blob list generates an uninitialized blob
    this->initializeBlob(this->blobsList->getTail()->getData()->blob);

    this->foodList = new SDLL(SDLL_DT_FOOD, worldMax);
    if (this->foodList == NULL) {
        std::cout 
            << "Unable to create food list. Aborting."
            << std::endl;
        return;
    }
    // Creating a new food list generates an uninitialized piece of food
    this->initializeFood(this->foodList->getTail()->getData()->food);

    // Generate the desired blobs and food
    for (int i = this->aliveBlobs; i < blobsNumber; i++) {
        if (this->createBlob() == false) {
            std::cout
                << "Unable to create a new blob. Aborting."
                << std::endl;
            return;
        }
    }

    for (int i = this->foodAvailable; i < foodAmmount; i++) {
        if (this->createFood() == false) {
            std::cout
                << "Unable to create new food. Aborting."
                << std::endl;
            return;
        }
    }


    return;
}

/******************** PUBLIC METHODS ********************/
void World::destroy(void) {
    if (this->blobsList != NULL)    { blobsList->destroy(); }
    if (this->foodList != NULL)     { foodList->destroy();  }
    this->foodAvailable = 0;
    this->aliveBlobs = 0;
    this->dimensions.width = 0;
    this->dimensions.height = 0;
    this->blobsMaxSpeed = 0;
    this->blobsMaxSpeedIsRnd = false;
    for (int i = BABYBLOB; i < NBLOBS; i++) {
        this->blobsDeathChance[i] = 0;
        this->blobsSmellRadius[i] = 0;
        this->blobsSize[i].width = 0;
        this->blobsSize[i].height = 0;
    }

    return;
}

bool World::worldTick(const float randomJiggleLimit) {
    double tickSpeed = 0;

    Blob* john = NULL;

    this->checkMerge(randomJiggleLimit);
    this->checkFood();

    SDLL_Node* current = NULL;
    SDLL_Node* next = NULL;

    for (current = this->blobsList->getHead(); current != NULL; current = next) {
        if (current == NULL) break;

        next = current->getNextNode(); // This will avoid derreferencing an invalid address if this blob dies
        john = current->getData()->blob;

        if (!blobsDeath(*john)) {

            tickSpeed = this->blobsRelativeSpeed * john->getMaximumSpeed();
            john->move(tickSpeed);
        }
    }

    return this->status();
}

bool World::checkFood(void) {
    bool someFood = false;
    Point_t blobPosition = { 0 };
    double blobAngle = 0;
    Point_t nearestFoodPosition = { 0 };

    for (SDLL_Node* currentNode = blobsList->getHead(); 
            currentNode != NULL; 
            currentNode = currentNode->getNextNode()) {
        
        Blob* currentBlob = currentNode->getData()->blob;
        Food* nearestFood = smell(*currentBlob);

        // Food is inside smellRadius. 
        // Let's see if in the same position as the blob (and eat it if so!)
        if (nearestFood != NULL) {
            currentBlob->getCoordinates(blobPosition.x, blobPosition.y, blobAngle);
            nearestFood->getPosition(nearestFoodPosition.x, nearestFoodPosition.y);
            const Size_t* blobSize = currentBlob->getBlobSize();

            if (islessequal(distance(blobPosition, nearestFoodPosition), blobSize->width)) {
                eatAndReproduce(*currentBlob);
                nearestFood->updatePosition();
            }
            someFood = true;
        }
    }

    return someFood;
}

bool World::blobsDeath(Blob& blob) {
    bool aBlobHasDied = false;

    SDLL_Node* node = this->findBlobNode(&blob);
    if (node == NULL) {
        return false;
    }

    static unsigned int flagXD = 0;
    if (flagXD % 97 == 0) {
        if (isless(generateRandomNumber(1.0, 2), blob.getDeadthChance())) {
            this->blobsList->remove(node);
            aBlobHasDied = true;
        }
        flagXD = 0;
    }
    flagXD++;

    return aBlobHasDied;
}

bool World::checkMerge(const float randomJiggleLimit) {
    bool atLeastOneMerge = false;

    // Store the current tail's address so newly born blobs (appended to the list)
    // are not taken into account.
    SDLL_Node* listTail = this->blobsList->getTail(); 

    bool thisPairMerged = false;

    for (SDLL_Node * mainNode = this->blobsList->getHead();
        mainNode != NULL && mainNode != listTail;
        mainNode = mainNode->getNextNode()) {

        Blob* mainBlob = mainNode->getData()->blob;
        if (mainBlob == NULL) {
            std::cout << "List looping error." << std::endl;
            break;
        }

        SDLL_Node* secondaryNodeNext = NULL;
        for (SDLL_Node * secondaryNode = mainNode->getNextNode();
            secondaryNode != NULL;
            secondaryNode = secondaryNodeNext) {

            secondaryNodeNext = secondaryNode->getNextNode();

            Blob* secondaryBlob = secondaryNode->getData()->blob;
            if (secondaryBlob == NULL) {
                std::cout << "List looping error." << std::endl;
                break;
            }

            thisPairMerged = this->mergeBlobs(*mainBlob, *secondaryBlob, randomJiggleLimit);
            if (thisPairMerged == true) {
                atLeastOneMerge = true; 
                mainBlob->grow();
                this->blobsList->remove(secondaryNode);
            }
        }
    }

    return atLeastOneMerge;
}

bool World::status(void) {
    if (this->aliveBlobs > 0) return true;
    return false;
}

Blob* World::getNextBlob(Blob* lastBlob) {
    if (lastBlob == NULL) {
        return this->blobsList->getHead()->getData()->blob;
    }

    SDLL_Node* blobNode = this->findBlobNode(lastBlob);

    if (blobNode == NULL) {
        return NULL;
    }

    // We have _lastBlob_ (if blobNode != NULL), let's get the next blob
    blobNode = blobNode->getNextNode();
    if (blobNode == NULL) {
        return NULL;
    }

    return blobNode->getData()->blob;
}

SDLL_Node* World::findBlobNode(Blob* blob) {
    if (this->blobsList == NULL) {
        return NULL;
    }

    // Find out to which node this blob belogs
    // _blobNode_ will end up being the node with _blob_
    SDLL_Node* blobNode = this->blobsList->getHead();

    while (blobNode->getData()->blob != blob) {
        blobNode = blobNode->getNextNode();
        
        if (blobNode == NULL) {
            // _blob_ was not found in the list.
            //std::cout << "Unable to find the given blob." << std::endl;
            return NULL;
        }
    }

    return blobNode;
}

Food* World::getNextFood(Food* lastFood) {
    if (this->foodList == NULL) {
        return NULL;
    }

    if (lastFood == NULL) {
        return this->foodList->getHead()->getData()->food;
    }

    // Find out to which node this food belogs
    // _blobNode_ will end up being the node with _lastFood_
    SDLL_Node* foodNode = this->foodList->getHead();

    while (foodNode->getData()->food != lastFood) {
        foodNode = foodNode->getNextNode();
        if (foodNode == NULL) {
            break;
        }
    }
    // We have _lastFood_ (if foodNode != NULL), let's get the next food
    if (foodNode != NULL) foodNode = foodNode->getNextNode();

    // The next food doesn't exist or _lastFood_ was not found in the list.
    if (foodNode == NULL) {
        //std::cout << "Unable to find the given food." << std::endl;
        return NULL;
    }
    
    return foodNode->getData()->food;
}


bool World::setDeathChance(const int age, const float newChance) {
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
    // Set death chance to all blobs this age
    updateBlobCommons();

    return true;
}

bool World::setSmellRadius(const int age, const float newRadius) {
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

    this->blobsSmellRadius[age] = newRadius + this->blobsSize[age].width;
    // Set smell radius to all blobs this age
    updateBlobCommons();

    return true;
}

void World::setMaxSpeed(float speed) {
    if (isless(speed, 0.0)) {
        std::cout << "Maximum speed must be greater than 0" << std::endl;
        return;
    }
    this->blobsMaxSpeed = speed;
    for (SDLL_Node* current = this->blobsList->getHead();
        current != NULL; current = current->getNextNode()) {
        
        if (this->blobsMaxSpeedIsRnd) {
            current->getData()->blob->setMaximumSpeed(generateRandomNumber(this->blobsMaxSpeed));
        }
        else {
            current->getData()->blob->setMaximumSpeed(this->blobsMaxSpeed);
        }
    }
}

void World::setRelativeSpeed(float speed) {
    if (isless(speed, 0.0)) {
        std::cout << "Relative speed must be greater than 0" << std::endl;
        return;
    }
    this->blobsRelativeSpeed = speed;
}

void World::setFoodCount(int food) {
    if (food <= 0) {
        std::cout << "Food must be greater than 0" << std::endl;
        return;
    }

    while (food != (int)this->foodAvailable) {
        if (food < (int)this->foodAvailable) {
            this->foodList->pop();
            this->foodAvailable--;
        }
        else if (food > (int)this->foodAvailable) {
            this->foodList->append();
            this->foodAvailable++;
        }
    }

    return;
}


/******************** PRIVATE METHODS ********************/
bool World::createBlob(void) {
    if (blobsList == NULL) {
std::cout
<< "blobsList is NULL !!!"
<< std::endl;
return false;
    }


    if (this->blobsList->append() == NULL) {
        return false;
    }

    this->initializeBlob(this->blobsList->getTail()->getData()->blob);

    return true;
}

void World::initializeBlob(Blob* blob) {
    if (blob == NULL) { return; }

    // Initialize blob
    blob->setDimensions(this->blobsSize[BABYBLOB]);
    blob->setDeathChance(this->blobsDeathChance[BABYBLOB]);
    blob->setSmellRadius(this->blobsSmellRadius[BABYBLOB]);
    if (this->blobsMaxSpeedIsRnd == true) {
        blob->setMaximumSpeed(generateRandomNumber(this->blobsMaxSpeed));
    }
    else {
        blob->setMaximumSpeed(this->blobsMaxSpeed);
    }

    this->aliveBlobs++;

    return;
}

bool World::createFood(void) {
    if (foodList == NULL) {
        std::cout
            << "foodList is NULL !!!"
            << std::endl;
        return false;
    }

    if (this->foodList->append() == NULL) {
        return false;
    }

    this->initializeFood(this->foodList->getTail()->getData()->food);
    return true;
}

/* For consistency with initializeBlob */
void World::initializeFood(Food* food) {
    if (food == NULL) { return; }

    this->foodAvailable++;

    return;
}

void World::updateFood(Food& food) {
    food.updatePosition();
    return;
}

bool World::mergeBlobs(Blob& blob1, Blob& blob2, const double randomJiggleLimmit) {
    Point_t fbP = { 0 };    // First Blob's Position
    double fbA = 0;         // First Blob's Angle
    Point_t fbS = { 0 };     // First Blob's Size stored as Point_t for distance()

    Point_t sbP = { 0 };    // Second Blob's Position
    double sbA = 0;         // Second Blob's Angle
    Point_t sbS = { 0 };     // First Blob's Size stored as Point_t for distance()

    if (blob1.getAge() != blob2.getAge()) {
        blob1.sayHi();
        blob2.sayHi();
        return false;
    }

    blob1.getCoordinates(fbP.x, fbP.y, fbA);
    blob2.getCoordinates(sbP.x, sbP.y, sbA);

    blob1.getBlobSize(fbS.x, fbS.y);
    blob1.getBlobSize(sbS.x, sbS.y);



    // Blobs are one above the other or not.
    if (isgreater(fbP.x + fbS.x, sbP.x) && isless(fbP.x, sbP.x + sbS.x) 
        && isgreater(fbP.y + fbS.y, sbP.y)  && isless(fbP.y, sbP.y + sbS.y) ) {
        blob1.setPointingDirection( ( fbA 
                                 + sbA 
                                 + generateRandomNumber(fabs(randomJiggleLimmit))
                                ) / 3);
        return true;
    }

    return false;
}

bool World::eatAndReproduce(Blob& blob) {
    bool newBirdth = blob.eat();
    
    // Change the food's position, let the blob eat it and verify if a new
    // blob must be born.
    if (newBirdth == true) {
        this->createBlob();
        
        double x = 0, y = 0, angle = 0;
        blob.getCoordinates(x, y, angle);
        this->blobsList->getTail()->getData()->blob->setAwayFromBlob(x, y);
    }
    return newBirdth;
}

Food* World::smell(Blob& blob) {
    Point_t blobPosition = { 0 };
    double blobAngle = 0;
    blob.getCoordinates(blobPosition.x, blobPosition.y, blobAngle);

    Point_t foodPosition = { 0 };
    // This value makes no sense, so it will be ommited when less than one 
    // pieces of food are in conflict.
    long double nearestFoodDistance = 2 * blob.getSmellRadius(); 
    Point_t nearestFoodPosition = { 0 };
    Food* nearestFood = NULL;

    Food* food = NULL;
    SDLL_Node * foodNode = this->foodList->getHead();

    while (foodNode != NULL) {
        food = foodNode->getData()->food;
        if (food == NULL) { return NULL; }

        food->getPosition(foodPosition.x, foodPosition.y);

        // Blob is near enough of its food
        long double foodDistance = distance(blobPosition, foodPosition);

        if (islessequal(foodDistance, blob.getSmellRadius()) 
            && isless(foodDistance, nearestFoodDistance)) {
            
            nearestFoodDistance = foodDistance;
            nearestFoodPosition.x = foodPosition.x;
            nearestFoodPosition.y = foodPosition.y;
            nearestFood = food;
        }

        foodNode = foodNode->getNextNode();
    }

    if (nearestFood != NULL) {
        blob.setPointingDirection(nearestFoodPosition.x, nearestFoodPosition.y);
    }
    
    return nearestFood;
}


void World::updateBlobCommons(void) {
    for (SDLL_Node* curr = blobsList->getHead();
        curr != NULL; curr = curr->getNextNode()) {
        Blob* john = curr->getData()->blob;
        john->setDeathChance(blobsDeathChance[john->getAge()]);
        john->setSmellRadius(blobsSmellRadius[john->getAge()]);
    }

    return;
}


/*== STATIC FUNCTIONS ==*/
long double distance(Point_t& firstPoint, Point_t& secondPoint) {
    return  (sqrtl(
                powl(firstPoint.x - secondPoint.x, 2.0)
                +
                powl(firstPoint.y - secondPoint.y, 2.0))
            );
}
