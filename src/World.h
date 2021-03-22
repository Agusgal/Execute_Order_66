#ifndef WORLD_H
#define WORLD_H 1

#include "Sprite.h"
#include "Blob.h"

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
     * Decide if any blob is near some food and head towards it.
     * 
     * Return:
     *  True: At least one blob has changed its direction.
     *  False: No blob has changed directionDecide if any blob is near some food and head towards it.
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
    bool checkMerge(void);

    /*
     * DESTROY THE WHOLE WORLD MUAHAHAHAHAHA!
     * 
     */
    void destroy(void);

    /*
     * Tell if there's at least one blob still alive.
     * 
     * Return:
     *  True: At least one blob is alive.
     *  False: All blobs are dead... this is such an empty world :(
     */
    bool status(void);

    bool setDeathChance(const int age, const double newChance);
    bool setSmellRadius(const int age, const double newRadius);

private:
    //Sprite* worldSprite;
    //Blobs* allBlobs;
    //Food* allFood;

    unsigned foodAvailable; // Ammount of food
    unsigned aliveBlobs;    // How many blobs are alive

    double width;           // World dimensions
    double height;

    /*
     * All new blobs are created using this three parameters.
     */
    double blobsDeathChance[NBLOBS];
    double blobsSmellRadius[NBLOBS];
    Size_t blobsSize[NBLOBS];

    /*
     * Perform merge between blob1 and blob2.
     * The first blob always survives with the merged parameters, 
     * the second blob does not (aka: it should be destroyed).
     *
     * Returns:
     *  True: if merge was successfull.
     *  False: if merge failed.
     */
    bool mergeBlobs(Blob& blob1, Blob& blob2);

    /*
     * When _blob_ is is on the same position as its food, eats it.
     *
     * Returns:
     *  True: When the blob has eaten enough to reproduce itself 
            (aka: generate a new baby blob).
     *  False: Food has been eated but no reproduction is to be performed.
     */
    bool eatAndReproduce(Blob& blob);

    /*
     * When _blob_ detects food in its smell radius, changes its direction.
     *
     * Returns:
     *  True: Food has been detected near the blob and it has changed its direction.
     *  False: No food detected.
     */
    bool smell(Blob& blob);


    // TODO: void updateBlobCommons(void);
};

#endif /* ! WORLD_H */