//
// Created by shams on 8/8/24.
//

#include <cstdio>
#include "CircleBoundary.h"
#include "app/math/Math.h"
#include "LineSegmentBoundary.h"

BoundaryIntersectionResult CircleBoundary::intersects(Boundary *o) {
    if (dynamic_cast<CircleBoundary*>(o)) {
        auto * other = dynamic_cast<CircleBoundary*>(o);

        if(Math::pow(this->x - other->x, 2) + Math::pow(this->y - other->y, 2) < Math::pow(this->r + other->r, 2)) {
            // Intersects
            return {true, Vector(this->x - other->x, this->y - other->y).getNormal(), this, o };
        }
    } else if (dynamic_cast<LineSegmentBoundary *>(o)) {
        auto * it = dynamic_cast<LineSegmentBoundary *>(o);

        double A = it->y2 - it->y1;
        double B = it->x1 - it->x2;
        double C = it->x2 * it->y1 - it->x1 * it->y2;

        //double distance = Math::fabs(A * this->x + B * this->y + C) / Math::sqrt(A * A + B * B);

        // Check if the distance is less than or equal to the radius
//        if (distance <= this->r) {
        float D = C / B - this->y;
        float a = 1 + A*A / (B * B);
        float b = -2 * this->x + 2 * A * D / B;
        float c = this->x * this->x + D * D - this->r * this->r;

        float discriminant = b * b - 4 * a * c;
        if (discriminant >= 0) {
            float sqrtDiscriminant = Math::sqrt(discriminant);
            float x1 = (-b + sqrtDiscriminant) / (2 * a);
            float x2 = (-b - sqrtDiscriminant) / (2 * a);
            float y1 = -A/B * x1 - C/B;
            float y2 = -A/B * x2 - C/B;

            return {true, Vector(this->x - (x1 + x2) / 2, this->y - (y1 + y2) / 2).getNormal(), this, o};
        }
    }

    return {false, Vector(0,0)};
}
