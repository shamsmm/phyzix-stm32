//
// Created by shams on 8/7/24.
//

#ifndef PHYZIX_CAMERA_H
#define PHYZIX_CAMERA_H


#include <cstdint>
#include "DynamicObject.h"

class Camera/* : public DynamicObject*/ {
private:
    uint16_t x_size;
    uint16_t y_size;

public:
    Camera(uint16_t x_size, uint16_t y_size) {
        this->x_size = x_size;
        this->y_size = y_size;
    };
};


#endif //PHYZIX_CAMERA_H
