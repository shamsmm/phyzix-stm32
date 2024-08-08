//
// Created by shams on 8/8/24.
//

#include "LineSegmentBoundary.h"
#include "CircleBoundary.h"
#include "app/math/Math.h"

bool LineSegmentBoundary::intersects(Boundary *other) const {
    if (dynamic_cast<LineSegmentBoundary*>(other)) {
        auto it = dynamic_cast<LineSegmentBoundary*>(other);

        double A1 = y2 - y1;
        double B1 = x1 - x2;

        double A2 = it->y2 - it->y1;
        double B2 = it->x1 - it->x2;

        return A1 * B2 - A2 * B1 != 0;
    } else if ( dynamic_cast<CircleBoundary *>(other) ) {
        auto it = dynamic_cast<CircleBoundary *>(other);

        double A = this->y2 - this->y1;
        double B = this->x1 - this->x2;
        double C = this->x2 * this->y1 - this->x1 * this->y2;

        double distance = Math::fabs(A * it->x + B * it->y + C) / Math::sqrt(A * A + B * B);

        // Check if the distance is less than or equal to the radius
        return distance <= it->r;
    }

    return false;
}
