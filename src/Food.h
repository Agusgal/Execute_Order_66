#ifndef FOOD_H
#define FOOD_H

#include "Coordinates.h"
class Food {
public:
    Food(Point_t& maxCoordinates);
    Food(unsigned int maxX, unsigned int maxY);

    void destroy(void);

    void getPosition(double& x, double& y);
    const Point_t* getPosition(void);

    void updatePosition(void);
    void updateAndGetPosition(double& newX, double& newY);
    const Point_t* updateAndGetPosition(void);

private:
    Point_t current;
    Point_t maximum;

    void generatePosition(void);
};

#endif /* ! FOOD_H */