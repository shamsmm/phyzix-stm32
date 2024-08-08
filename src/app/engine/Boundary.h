//
// Created by shams on 8/7/24.
//

#ifndef PHYZIX_BOUNDARY_H
#define PHYZIX_BOUNDARY_H


#include <cstdio>

class Boundary{
public:

    virtual bool intersects(Boundary * other) const = 0;

    static bool intersects(Boundary ** b1, size_t b1Count, Boundary ** b2, size_t b2Count) {
        for(int i = 0; i < b1Count; ++i) {
            for (int j = i; j < b2Count; ++j) {
                if (b1[i]->intersects(b2[j]))
                    return true;
            }
        }

        return false;
    }
};


#endif //PHYZIX_BOUNDARY_H
