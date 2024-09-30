//
// Created by shams on 8/8/24.
//

#include "CircleBoundary.h"
#include "app/math/Math.h"
#include "LineSegmentBoundary.h"
#include "BoundaryCalculations.h"

BoundaryIntersectionResult CircleBoundary::intersects(Boundary *o) {
    if (o->getId() == ClassId::CIRCLE_BOUNDARY) {
        auto * other = (CircleBoundary *) o;

        if(Math::pow(this->x - other->x, 2) + Math::pow(this->y - other->y, 2) < Math::pow(this->r + other->r, 2)) {
            // Intersects
            return {true, Vector(this->x - other->x, this->y - other->y).getNormal(), this, o };
        }
    } else if (o->getId() == ClassId::LINE_SEGMENT_BOUNDARY) {
        auto * other = (LineSegmentBoundary *)(o);
        return BoundaryCalculations::intersects(other, this, true);
    }

    return {};
}
