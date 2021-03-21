#ifndef COORDINATES_H
#define COORDINATES_H  1

typedef struct Point {
    double x;
    double y;
} Point_t;

class Coordinates {
public:
    /* X, Y and angle are initialized to 0.0 */
    Coordinates();
    /* X, Y are set with a random value between 0.0 and maxX or maxY.
     * Angle is set with a random value in range [0.0 ; 360.0)
     */
    Coordinates(unsigned int maxX, unsigned int maxY);

    void rotate(double angle);
    void update(double modulus);

    void getPosition(double& x, double& y);
    const Point_t* getPosition(void);
    void getAngle(double& angle);
    double getAngle();

private:
    Point_t position;
    double angle;
};

#endif /* !COORDINATES_H */