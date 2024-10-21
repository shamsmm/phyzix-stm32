//
// Created by shams on 8/8/24.
//

#include "LineSegmentBoundary.h"
#include "CircleBoundary.h"
#include "app/math/Math.h"
#include "BoundaryCalculations.h"


BoundaryIntersectionResult LineSegmentBoundary::intersects(Boundary *o)
{
    if (o->getBaseType() == RuntimeBaseType::LINE_SEGMENT_BOUNDARY)
    {
    }
    else if (o->getBaseType() == RuntimeBaseType::CIRCLE_BOUNDARY)
    {
        auto other = (CircleBoundary *)(o);
        return BoundaryCalculations::intersects(this, other);
    }

    return {false, Vector(0, 0)};
}

float LineSegmentBoundary::getLengthSquared()
{
    return (Math::pow(this->x2 - this->x1, 2) + Math::pow(this->y2 - this->y1, 2));
}
