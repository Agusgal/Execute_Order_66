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
    Blob(Point_t& maxCoordinates, Size_t& dimensions,
        double maxSpeed,
        double deathChance, double smellRadius
    );

    Blob(Point_t& maxCoordinates);

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
    const Size_t* getBlobSize(void);
    void getBlobSize(double& width, double& height);
    void getCoordinates(double& x, double& y, double& angle);

    bool setDeathChance(double chance);
    bool setDimensions(Size_t& newDim);
    bool setDimensions(double newWidth, double newHeight);
    bool setMaximumSpeed(double speed);
    bool setSmellRadius(double radius);

private:
    unsigned age;
    double maximumSpeed;
    unsigned foodCount;

    double deathChance;
    double smellRadius;

    Size_t dimensions;
    Point_t maximumPosition;
    Coordinates currentPosition;
};

#endif /* ! BLOB_H */