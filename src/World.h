#ifndef WORLD_H
#define WORLD_H 1

#include "SDLL.h"
#include "Blob.h"
#include "Sprite.h"

class World {
public:
    World(
        double width, double height,
        unsigned blobsNumber, unsigned foodAmmount, 
        Size_t blobSizeByAge[NBLOBS],
        double deathChance[NBLOBS], double smellRadius[NBLOBS],
        double blobsMaximumSpeed,
        bool blobsMaximumSpeedRandom = false // When true, the maximum speed of each blob is a random number between 0.0 and blobsbMaximumSpeed
    );

    /*
     * DESTROY THE WHOLE WORLD MUAHAHAHAHAHA!
     * 
     */
    void destroy(void);

    /*
     * What are the odds? Will this blob die?
     * 
     * Kills the blob if it can't take it
     * 
     * Returns:
     *  True: The blob is now dead
     *  False: The blob lives another tick.
     */
    bool blobsDeath(Blob& blob);

    /*
     * Decide if any blob is near some food and head towards it.
     *
     * Also eats food when necessary
     * 
     * Return:
     *  True: At least one blob has changed its direction.
     *  False: No blob has changed direction..
     */
    bool checkFood(void);

    /*
     * Decide if there are blobs to be merged and merge them.
     * 
     * Return:
     *  True: At least one pair of blob has been merged.
     *  False: No blob mergin happend.
     */
    bool checkMerge(const double randomJiggleLimit);

    /*
     * Tell if there's at least one blob still alive.
     * 
     * Return:
     *  True: At least one blob is alive.
     *  False: All blobs are dead... this is such an empty world :(
     */
    bool status(void);

    
    /*
     * Get the next blob/food element in the list.
     * An argument of NULL returns the first one in the list.
     * NULL if there's no other element in the list.
     */
    Blob* getNextBlob(Blob* lastBlob = NULL);
    Food* getNextFood(Food* lastFood = NULL);

    /*
     * Returns false on error.
     */
    bool setDeathChance(const int age, const double newChance);
    bool setSmellRadius(const int age, const double newRadius);

private:
    SDLL* blobsList;
    SDLL* foodList;

    unsigned foodAvailable; // Ammount of food
    unsigned aliveBlobs;    // How many blobs are alive

    Size_t dimensions;           // World dimensions

    /*
     * All new blobs are created using this four parameters.
     */
    double blobsDeathChance[NBLOBS];
    double blobsSmellRadius[NBLOBS];
    double blobsMaxSpeed;
    bool blobsMaxSpeedIsRnd;
    Size_t blobsSize[NBLOBS];

    bool createBlob(void);
    void initializeBlob(Blob* blob); // Call this after creation
    bool createFood(void);
    void initializeFood(Food* food); // Call this after creation

    void updateFood(Food& food); // Make a piece of food change its coordinates


    SDLL_Node* findBlobNode(Blob* blob);

    /*
     * Perform merge between blob1 and blob2.
     * The first blob always survives with the merged parameters, 
     * the second blob does not (aka: it should be destroyed).
     *
     * Returns:
     *  True: if merge was successfull (caller should kill blob2).
     *  False: if merge didn't took place (no blob should be killed).
     */
    bool mergeBlobs(Blob& blob1, Blob& blob2, const double randomJiggleLimit);

    /*
     * When _blob_ is is on the same position as its food, eats it.
     *
     * Returns:
     *  True: When the blob has eaten enough to reproduce itself 
            (aka: a new blob has been appended at the list's tail).
     *  False: Food has been eated but no reproduction was performed.
     */
    bool eatAndReproduce(Blob& blob);

    /*
     * When _blob_ detects food in its smell radius, changes its direction.
     *
     * Returns:
     *  Pointer to nearest food. 
     *  NULL if no food is inside _blob_'s smell radius.
     */
    Food* smell(Blob& blob);


    // TODO: void updateBlobCommons(void);
};

#endif /* ! WORLD_H */