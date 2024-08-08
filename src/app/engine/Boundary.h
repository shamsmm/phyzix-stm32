//
// Created by shams on 8/7/24.
//

#ifndef PHYZIX_BOUNDARY_H
#define PHYZIX_BOUNDARY_H


class Boundary{
public:

    virtual bool intersects(Boundary * other) const = 0;
};


#endif //PHYZIX_BOUNDARY_H
