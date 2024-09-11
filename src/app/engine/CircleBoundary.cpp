//
// Created by shams on 8/8/24.
//

#include <cstdio>
#include "CircleBoundary.h"
#include "app/math/Math.h"
#include "LineSegmentBoundary.h"
#include "BoundaryCalculations.h"

BoundaryIntersectionResult CircleBoundary::intersects(Boundary *o) {
    if (dynamic_cast<CircleBoundary*>(o)) {
        auto * other = dynamic_cast<CircleBoundary*>(o);

        if(Math::pow(this->x - other->x, 2) + Math::pow(this->y - other->y, 2) < Math::pow(this->r + other->r, 2)) {
            // Intersects
            return {true, Vector(this->x - other->x, this->y - other->y).getNormal(), this, o };
        }
    } else if (dynamic_cast<LineSegmentBoundary *>(o)) {
        auto * other = dynamic_cast<LineSegmentBoundary *>(o);
        return BoundaryCalculations::intersects(other, this, true);
    }

    return {};
}
