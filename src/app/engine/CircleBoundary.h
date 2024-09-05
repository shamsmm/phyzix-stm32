//
// Created by shams on 8/8/24.
//

#ifndef PHYZIX_CIRCLEBOUNDARY_H
#define PHYZIX_CIRCLEBOUNDARY_H



#include "Boundary.h"

class CircleBoundary: public Boundary{
public:
    float x;
    float y;
    float r;

    CircleBoundary(float x, float y, float r): x(x), y(y), r(r) {}

    bool intersects(Boundary * other) const override;
};


#endif //PHYZIX_CIRCLEBOUNDARY_H