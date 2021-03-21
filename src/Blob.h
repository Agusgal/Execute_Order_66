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

class Blob {
public:
    Blob()
    Blob(const Point_t* maxCoords, const Sprite sprites[NBLOBS],
        double maxSpeed);

    double speed;
    double deathChance;
    double smellRadius;
    unsigned foodCount;
    unsigned age;
    Point_t currentPosition;

    void move(void);
    void eat(void);
    void die(void);
    void sayHi(void);
    void grow(void);

private:
    double maximumSpeed;
    Point_t maximumPosition;
    //Sprite sprites[NBLOBS];
};

#endif /* ! BLOB_H */