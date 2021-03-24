#ifndef COORDINATES_H
#define COORDINATES_H  1

typedef struct Point {
    double x;
    double y;
} Point_t;

typedef struct Size
{
    double width;
    double height;
} Size_t;

class Coordinates {
public:
    /* X, Y and angle are initialized to 0.0 */
    Coordinates();
    /* X, Y are set with a random value between 0.0 and maxX or maxY.
     * Angle is set with a random value in range [0.0 ; 360.0)
     */
    Coordinates(double maxX, double maxY);

    void rotate(const double angle);
    void rotateRadians(const double angleInRadians);
    void update(const double modulus);

    void getPosition(double& x, double& y);
    const Point_t* getPosition(void);
    void getAngle(double&);
    double getAngle();
    void displace(double x, double y);

private:
    Point_t position;
    Point_t maximumCoordinates;
    double angle;
};

#endif /* !COORDINATES_H */
