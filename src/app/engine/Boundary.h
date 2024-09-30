//
// Created by shams on 8/7/24.
//

#ifndef PHYZIX_BOUNDARY_H
#define PHYZIX_BOUNDARY_H


#include <cstdint>
#include "Vector.h"
#include "app/lib/class_id.h"

class Boundary;

struct Boundaries {
    Boundary ** list;
    uint16_t count;
};

struct BoundaryIntersectionResult {
    bool intersected = false;
    Vector normal{0, 0};
    Boundary * it;
    Boundary * other;
};

class Boundary: public ClassIdentifiable {
public:
    float e = 0.8;

    ClassId getId() const override {
        return ClassId::BOUNDARY;
    }

    virtual BoundaryIntersectionResult intersects(Boundary * other) = 0;

    static BoundaryIntersectionResult intersects(Boundaries b1, Boundaries b2) {
        for(int i = 0; i < b1.count; ++i) {
            for (int j = i; j < b2.count; ++j) {
                auto intersection = b1.list[i]->intersects(b2.list[j]);
                if (intersection.intersected)
                    return intersection;
            }
        }

        return {false, Vector(0,0)};
    }
};

#endif //PHYZIX_BOUNDARY_H
