//
// Created by shams on 8/8/24.
//

#ifndef PHYZIX_LINESEGMENTBOUNDARY_H
#define PHYZIX_LINESEGMENTBOUNDARY_H

#include "Boundary.h"

class LineSegmentBoundary : public Boundary
{
public:
    float x1;
    float y1;
    float x2;
    float y2;

    RuntimeBaseType getBaseType() const override
    {
        return RuntimeBaseType::LINE_SEGMENT_BOUNDARY;
    }

    LineSegmentBoundary(float x1, float y1, float x2, float y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}

    BoundaryIntersectionResult intersects(Boundary *o) override;
    float getLengthSquared();

    /**
     * @brief Return true if the input point is on the input line segement.
     */
    static bool pointOnLine(LineSegmentBoundary *line, float x, float y)
    {
        Vector b_a{line->x2 - line->x1, line->y2 - line->y1};
        Vector c_a{x - line->x1, y - line->y1};

        // If (B-A) cross (C-A) is not zero.
        if (Vector::cross(&b_a, &c_a))
        {
            return false;
        }

        float dot_product = Vector::dot(&b_a, &c_a);
        if (dot_product > 0 && dot_product < line->getLengthSquared())
        {
            return true;
        }

        return false;
    }
};

#endif // PHYZIX_LINESEGMENTBOUNDARY_H
