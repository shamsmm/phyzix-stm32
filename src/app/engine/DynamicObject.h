//
// Created by shams on 8/7/24.
//

#ifndef PHYZIX_DYNAMICOBJECT_H
#define PHYZIX_DYNAMICOBJECT_H


#include <cstdint>
#include "Drawable.h"
#include "Boundary.h"
#include "Vector.h"

class DynamicObject : public Drawable{
public:
    float prev_x = 0;
    float prev_y = 0;

    Vector s;
    Vector v = Vector(0, 0);
    Vector a = Vector(0, 0);
    float m = 1;

    Vector (*forceFunction)(float, float, float, float, float){};

    float zIndex = 0;

    // Constructor takes a callable to implement the draw method
    DynamicObject(
            void (*drawFunction)(float , float),
            void (*blackOutFunction)(float , float),
            void (*boundaryUpdateFunction)(Boundaries&, Vector&),
            float x,
            float y
    )
    : drawFunction(drawFunction), blackOutFunction(blackOutFunction), updateBoundaryFunction(boundaryUpdateFunction), s(Vector(x, y)) {
        this->updateBoundaryFunction(boundaries, s);
    }

    // Override the draw method from the base class
    void draw() const override {
        drawFunction(s.x, s.y);
    }

    void blackOut() const {
        blackOutFunction(prev_x, prev_y);
    }

public:
    void (*drawFunction)(float , float );
    void (*blackOutFunction)(float , float );
    void (*updateBoundaryFunction)(Boundaries&, Vector&);
    Boundaries boundaries;
};


#endif //PHYZIX_DYNAMICOBJECT_H
