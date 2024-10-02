//
// Created by shams on 8/8/24.
//

#include "LineSegmentBoundary.h"
#include "CircleBoundary.h"
#include "app/math/Math.h"
#include "BoundaryCalculations.h"

BoundaryIntersectionResult LineSegmentBoundary::intersects(Boundary *o) {
    if (o->getBaseType() == RuntimeBaseType::LINE_SEGMENT_BOUNDARY) {
        auto other = (LineSegmentBoundary*)(o);

        double A1 = y2 - y1;
        double B1 = x1 - x2;

        double A2 = other->y2 - other->y1;
        double B2 = other->x1 - other->x2;

        if (A1 * B2 - A2 * B1 != 0) {
            // TODO: implement the intersection of two line segments
        }
    } else if (o->getBaseType() == RuntimeBaseType::CIRCLE_BOUNDARY) {
        auto other = (CircleBoundary *)(o);
        return BoundaryCalculations::intersects(this, other);
    }

    return {false, Vector(0,0)};
}
