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

    double speed;

    /*
    void move(void);
    void eat(void);
    void die(void);
    void sayHi(void);
    */
    double getDeadthChance(void);
    double getSmellRadius(void);
    
    /*
    const Sprite* getBlobSprite(void);
    void getCoordinates(double& x, double& y, double& angle);
    */

    void printDeathChance(void);
    void printCoordinates(void);

private:
    unsigned age;
    double maximumSpeed;
    unsigned foodCount;


    double * deathChanceByAge;
    double * smellRadiusByAge;

    Point_t maximumPosition;
    Coordinates currentPosition;
    Sprite * sprites;


    //void blobBirthday(void);
};

#endif /* ! BLOB_H */