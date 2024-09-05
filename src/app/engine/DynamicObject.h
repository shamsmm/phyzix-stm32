//
// Created by shams on 8/7/24.
//

#ifndef PHYZIX_DYNAMICOBJECT_H
#define PHYZIX_DYNAMICOBJECT_H


#include <cstdint>
#include "Drawable.h"
#include "Boundary.h"

class DynamicObject : public Drawable{
public:
    float prev_x = 0;
    float prev_y = 0;
    float x = 0;
    float y = 0;
    float z = 0;
    float v_x = 0;
    float v_y = 0;
    float a_x = 0;
    float a_y = 0;
    float (*axFunction)(float, float, float, float);
    float (*ayFunction)(float, float, float, float);
    bool isStatic = false;

    // Constructor takes a callable to implement the draw method
    DynamicObject(
            void (*drawFunction)(uint16_t, uint16_t),
            void (*blackOutFunction)(uint16_t, uint16_t),
            void (*boundaryUpdateFunction)(Boundary ** boundaries, uint16_t boundaryCount, uint16_t, uint16_t),
            uint16_t x, uint16_t y
            )
            : drawFunction(drawFunction),blackOutFunction(blackOutFunction), boundaryUpdateFunction(boundaryUpdateFunction), x(x), y(y) {}

    // Override the draw method from the base class
    void draw() const override {
        drawFunction((uint16_t ) x, (uint16_t ) y);
    }

    void blackOut() const {
        blackOutFunction((uint16_t ) prev_x, (uint16_t ) prev_y);
    }

    void setAccelerationFunctions(float (*axFunction)(float, float, float, float), float (*ayFunction)(float, float, float, float)) {
        this->axFunction = axFunction;
        this->ayFunction = ayFunction;
    }

public:
    void (*drawFunction)(uint16_t, uint16_t);
    void (*boundaryUpdateFunction)(Boundary ** boundaries, uint16_t boundaryCount, uint16_t, uint16_t);
    void (*blackOutFunction)(uint16_t, uint16_t);

public:
    Boundary ** boundaries;
    uint16_t boundaryCount;
};


#endif //PHYZIX_DYNAMICOBJECT_H
