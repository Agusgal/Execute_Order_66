#ifndef BLOB_H
#define BLOB_H  1

#include "Coordinates.h"
#include "Sprite.h"

enum blobAge {
    BABYBLOB = 0,
    GROWNBLOB,
    GOODOLDBLOB,
    NBLOBS
};

enum blobBirdthFood {
    FOOD_GOODOLDBLOB = 3,
    FOOD_GROWNBLOB,
    FOOD_BABYBLOB,
};

class Blob {
public:
    /*Blob(const Sprite* sprites[NBLOBS],
        double maxSpeed, double smellRadius, 
        double deathChance[NBLOBS]);
     */
    Blob(Point_t& maxCoordinates, Sprite sprites[NBLOBS],
        double maxSpeed,
        double smellRadius[NBLOBS], double deathChance[NBLOBS]
    );

    /* This is the blob speed.
     * Modify it at will, it's not taken into account 
     */
    double speed;

    void die(void);
    /* Increment food counter and return if a new birdth should happen */
    bool eat(void);
    void grow(const double newAngle);
    void move(const double modulus);
    void sayHi(void);

    double getDeadthChance(void);
    double getSmellRadius(void);
    double getMaximumSpeed(void);
    
    const Sprite* getBlobSprite(void);
    void getCoordinates(double& x, double& y, double& angle);

private:
    unsigned age;
    double maximumSpeed;
    unsigned foodCount;

    double * deathChanceByAge;
    double * smellRadiusByAge;

    Point_t maximumPosition;
    Coordinates currentPosition;
    Sprite * sprites;
};

#endif /* ! BLOB_H */