//
// Created by shams on 8/8/24.
//

#ifndef PHYZIX_LINESEGMENTBOUNDARY_H
#define PHYZIX_LINESEGMENTBOUNDARY_H


#include "Boundary.h"

class LineSegmentBoundary : public Boundary{
public:
    float x1;
    float y1;
    float x2;
    float y2;

    RuntimeBaseType getBaseType() const override {
        return RuntimeBaseType::LINE_SEGMENT_BOUNDARY;
    }

    LineSegmentBoundary(float x1, float y1, float x2, float y2): x1(x1), y1(y1), x2(x2), y2(y2) {}

    BoundaryIntersectionResult intersects(Boundary * o) override;
};


#endif //PHYZIX_LINESEGMENTBOUNDARY_H
