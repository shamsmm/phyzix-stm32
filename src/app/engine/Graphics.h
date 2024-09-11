//
// Created by shams on 8/7/24.
//

#ifndef PHYZIX_GRAPHICSOBJECT_H
#define PHYZIX_GRAPHICSOBJECT_H


#include <functional>
#include "Drawable.h"

class Graphics: public Drawable {
public:
    // Constructor takes a callable to implement the draw method
    Graphics( void (*drawFunction)())
            : drawFunction(drawFunction) {}

    // Override the draw method from the base class
    void draw() const override {
        drawFunction();
    }

private:
    void (*drawFunction)();
};


#endif //PHYZIX_GRAPHICSOBJECT_H
