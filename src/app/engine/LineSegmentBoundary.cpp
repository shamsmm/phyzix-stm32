//
// Created by shams on 8/8/24.
//

#include "LineSegmentBoundary.h"
#include "CircleBoundary.h"
#include "app/math/Math.h"

BoundaryIntersectionResult LineSegmentBoundary::intersects(Boundary *other) {
    if (dynamic_cast<LineSegmentBoundary*>(other)) {
        auto it = dynamic_cast<LineSegmentBoundary*>(other);

        double A1 = y2 - y1;
        double B1 = x1 - x2;

        double A2 = it->y2 - it->y1;
        double B2 = it->x1 - it->x2;

        if (A1 * B2 - A2 * B1 != 0) {

        }
    } else if ( dynamic_cast<CircleBoundary *>(other) ) {
        auto it = dynamic_cast<CircleBoundary *>(other);

        double A = this->y2 - this->y1;
        double B = this->x1 - this->x2;
        double C = this->x2 * this->y1 - this->x1 * this->y2;

        float D = C/B + it->y;
        float a = 1 + A * A / (B * B);
        float b = -2 * it->x - 2 * (A * D) / B;
        float c = it->x * it->x + D * D - it->r * it->r;

        float discriminant = b * b - 4 * a * c;
        if (discriminant >= 0) {
            float sqrtDiscriminant = Math::sqrt(discriminant);
            float x1 = (-b + sqrtDiscriminant) / (2 * a);
            float x2 = (-b - sqrtDiscriminant) / (2 * a);
            float y1 = -A/B * x1 - C/B;
            float y2 = -A/B * x2 - C/B;


            return {true, Vector(it->x - (x1 + x2) / 2, it->y - (y1 + y2) / 2).getNormal(), this, other};
        }
    }

    return {};
}
