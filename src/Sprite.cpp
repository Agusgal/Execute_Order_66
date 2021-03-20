#include <iostream>
#include <cmath>
#include <string>

#include "Sprite.h"

/******************** DEFINITIONS ********************/

/******************** MACROS ********************/
/******************** CONSTRUCTOR ********************/
Sprite::Sprite(const std::string path, const double width, const double height) {
    // Initialize everything
    this->path = "";
    this->dimensions = { 0.0 };

#ifdef DEBUG
    std::cout << "Constructor called with: " << std::endl;
    std::cout << "\tpath: " << path << std::endl;
    std::cout << "\twidth: " << width << std::endl;
    std::cout << "\theight: " << height << std::endl;
#endif

    if ( !path.compare("") ) {
        std::cout << "Path cannot be an empty string." << std::endl;
        return;
    }
    else if (islessequal(width, 0.0)) {
        std::cout << "Height must be greater than 0.0. "
                  << "Got: " << width
                  << std::endl;
        return;
    }
    else if (islessequal(height, 0.0)) {
        std::cout << "Height must be greater than 0.0. "
                  << "Got: " << height 
                  << std::endl;
        return;
    }
    
    this->path = path;
    this->dimensions.width = width;
    this->dimensions.height = height;
}

/******************** PUBLIC METHODS ********************/
std::string* Sprite::getPath(void) {
#ifdef DEBUG
    std::cout << "getPath(void) called" << std::endl;
#endif
    return &(this->path);
}

void Sprite::getSize(double& width, double& height) {
#ifdef DEBUG
    std::cout << "getSize(width: " << width 
        << ", height: " << height << ") called." << std::endl;
#endif

    width = this->dimensions.width;
    height = this->dimensions.height;
    return;
}

const Size_t* Sprite::getSize(void) {
#ifdef DEBUG
    std::cout << "getSize(void) called." << std::endl;
#endif

    return &(this->dimensions);
}

/******************** PRIVATE METHODS ********************/
