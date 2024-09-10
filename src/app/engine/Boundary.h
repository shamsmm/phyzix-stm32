//
// Created by shams on 8/7/24.
//

#ifndef PHYZIX_BOUNDARY_H
#define PHYZIX_BOUNDARY_H


#include <cstdint>
class Boundary;

struct Boundaries {
    Boundary ** list;
    uint16_t count;
};

struct BoundaryIntersectionResult {
    char intersects : 1;
    Boundary * it;
    Boundary * other;
};

class Boundary{
public:
    float e = 0.5;

    virtual bool intersects(Boundary * other) const = 0;

    static BoundaryIntersectionResult intersects(Boundaries b1, Boundaries b2) {
        for(int i = 0; i < b1.count; ++i) {
            for (int j = i; j < b2.count; ++j) {
                if (b1.list[i]->intersects(b2.list[j]))
                    return {true, b1.list[i], b2.list[j]};
            }
        }

        return {false};
    }
};

#endif //PHYZIX_BOUNDARY_H
