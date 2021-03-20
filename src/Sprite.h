#ifndef SPRITE_H
#define SPRITE_H

#include <string>

typedef struct Size
{
    double width;
    double height;
}Size_t;

class Sprite {
public:
    Sprite(const std::string path, const double width, const double height);

    std::string * getPath(void);
    void getSize(double& width, double& height);
    const Size_t * getSize(void);

private:
    std::string path;
    Size_t dimensions;
};

#endif /* ! SPRITE_H */