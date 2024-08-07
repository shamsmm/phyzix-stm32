//
// Created by shams on 8/7/24.
//

#ifndef PHYZIX_DYNAMICOBJECT_H
#define PHYZIX_DYNAMICOBJECT_H


#include <cstdint>
#include "Drawable.h"

class DynamicObject : public Drawable{
public:
    float x = 0;
    float y = 0;
    float z = 0;
    float v_x = 0;
    float v_y = 0;
    float a_x = 0;
    float a_y = 0;

    float (*axFunction)(float, float, float, float);
    float (*ayFunction)(float, float, float, float);

    // Constructor takes a callable to implement the draw method
    DynamicObject( void (*drawFunction)(uint16_t, uint16_t), uint16_t x, uint16_t y)
            : drawFunction(drawFunction), x(x), y(y) {}

    // Override the draw method from the base class
    void draw() const override {
        drawFunction((uint16_t ) x, (uint16_t ) y);
    }

    void setAccelerationFunctions(float (*axFunction)(float, float, float, float), float (*ayFunction)(float, float, float, float)) {
        this->axFunction = axFunction;
        this->ayFunction = ayFunction;
    }

private:
    void (*drawFunction)(uint16_t, uint16_t);
};


#endif //PHYZIX_DYNAMICOBJECT_H
