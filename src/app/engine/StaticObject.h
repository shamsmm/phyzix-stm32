//
// Created by shams on 8/7/24.
//

#ifndef PHYZIX_STATICOBJECT_H
#define PHYZIX_STATICOBJECT_H

#include "Drawable.h"
#include "Boundary.h"

class StaticObject: public Drawable {
public:
    float zIndex = 0;
    Boundaries boundaries;

    RuntimeBaseType getBaseType() const override {
        return RuntimeBaseType::STATIC_OBJECT;
    }

    // Constructor takes a callable to implement the draw method
    StaticObject( void (*drawFunction)())
            : drawFunction(drawFunction) {}

    // Override the draw method from the base class
    void draw() const override {
        drawFunction();
    }

private:
    void (*drawFunction)();
};


#endif //PHYZIX_STATICOBJECT_H
