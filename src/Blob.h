#ifndef BLOB_H
#define BLOB_H  1

#include "Coordinates.h"

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
    void grow(void); // This happens on merge
    void move(const double modulus);
    void sayHi(void);

    int getAge(void);
    double getDeadthChance(void);
    double getSmellRadius(void);
    double getMaximumSpeed(void);
    const Size_t* getBlobSize(void);
    void getBlobSize(double& width, double& height);
    void getCoordinates(double& x, double& y, double& angle);
    void getPoint(double& x, double& y); // Same as getCoordinates without angle

    bool setDeathChance(double chance);
    bool setDimensions(Size_t& newDim);
    bool setDimensions(double newWidth, double newHeight);
    bool setPointingDirection(double newAngle);
    bool setPointingDirection(double x, double y); // Angle will be calculated to make blob point towards x and y
    bool setMaximumSpeed(double newMaxSpeed);
    bool setSmellRadius(double radius);
    void setAwayFromBlob(double x, double y);

private:
    unsigned age;
    double maximumSpeed;
    unsigned foodCount;

    double deathChance;
    double smellRadius;

    Size_t dimensions;
    Coordinates currentPosition;
};

#endif /* ! BLOB_H */