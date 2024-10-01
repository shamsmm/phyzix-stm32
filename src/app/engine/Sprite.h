//
// Created by shams on 8/7/24.
//

#ifndef PHYZIX_SPRITE_H
#define PHYZIX_SPRITE_H


#include <cstdint>
#include "DynamicObject.h"
#include "Drawable.h"

class Sprite : public DynamicObject {
private:
    uint16_t x_size;
    uint16_t y_size;

};


#endif //PHYZIX_SPRITE_H
