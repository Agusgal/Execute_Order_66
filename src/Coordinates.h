#ifndef COORDINATES_H
#define COORDINATES_H  1

class Coordinates {
public:
    double x;
    double y;
    double angle;

    Coordinates();
    Coordinates(unsigned int maxX, unsigned int maxY);

    void rotate(double angle);
    void update(double modulus);
};

#endif /* !COORDINATES_H */
