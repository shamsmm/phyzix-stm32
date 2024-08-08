//
// Created by shams on 8/8/24.
//

#include "CircleBoundary.h"
#include "app/math/Math.h"
#include "LineSegmentBoundary.h"

bool CircleBoundary::intersects(Boundary *other) const {
    if (dynamic_cast<CircleBoundary*>(other)) {
        auto * it = dynamic_cast<CircleBoundary*>(other);

        return Math::pow(x - it->x, 2) + Math::pow(y - it->y, 2) < Math::pow(r + it->r, 2);
    } else if (dynamic_cast<LineSegmentBoundary *>(other)) {
        auto * it = dynamic_cast<LineSegmentBoundary *>(other);

        double A = it->y2 - it->y1;
        double B = it->x1 - it->x2;
        double C = it->x2 * it->y1 - it->x1 * it->y2;

        double distance = Math::fabs(A * this->x + B * this->y + C) / Math::sqrt(A * A + B * B);

        // Check if the distance is less than or equal to the radius
        return distance <= this->r;
    }

    return false;
}
