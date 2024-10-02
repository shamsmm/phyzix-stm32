//
// Created by shams on 9/12/24.
//

#ifndef PHYZIX_BOUNDARYCALCULATIONS_H
#define PHYZIX_BOUNDARYCALCULATIONS_H

/**
 * @class BoundaryCalculations
 * @brief A class that contains static methods for common calculating intersections between boundaries
 */
class BoundaryCalculations {
public:
    /**
     * @brief Check if a ::LineSegmentBoundary and a ::CircleBoundary intersect or not
     * @param line the line boundary
     * @param circle the circle boundary
     * @param flip whether to flip the order of the boundaries in the ::BoundaryIntersectionResult
     * @return the BoundaryIntersectionResult
     * @note This method is to be referenced twice once in the ::LineSegmentBoundary class and once in the ::CircleBoundary class
     */
    static BoundaryIntersectionResult intersects(LineSegmentBoundary * line, CircleBoundary * circle, bool flip = false) {
        double A = line->y2 - line->y1;
        double B = line->x1 - line->x2;
        double C = line->x2 * line->y1 - line->x1 * line->y2;

        if (A == 0) {
            // horizontal line
            if (Math::fabs(circle->y - (-C / B)) <= circle->r) {
                if (Math::min(line->x1, line->x2) <= circle->x && circle->x <= Math::max(line->x1, line->x2)) {
                    // Intersects
                    if (flip)
                        return {true, Vector(0, circle->y - (-C / B)).getNormal(), circle, line};
                    else
                        return {true, Vector(0, circle->y - (-C / B)).getNormal(), line, circle};
                }
            }
        }

        if (B == 0) {
            // vertical line
            if (Math::fabs(circle->x - (-C / A)) <= circle->r) {
                if (Math::min(line->y1, line->x2) <= circle->y && circle->y <= Math::max(line->y1, line->y2)) {
                    // Intersects
                    if (flip)
                        return {true, Vector(circle->x - (-C / A), 0).getNormal(), circle, line};
                    else
                        return {true, Vector(circle->x - (-C / A), 0).getNormal(), line, circle};
                }
            }
        }

        float D = C / B - circle->y;
        float a = 1 + A*A / (B * B);
        float b = -2 * circle->x + 2 * A * D / B;
        float c = circle->x * circle->x + D * D - circle->r * circle->r;

        float discriminant = b * b - 4 * a * c;
        if (discriminant >= 0) {
            // Intersects
            float sqrtDiscriminant = Math::sqrt(discriminant);
            float x1 = (-b + sqrtDiscriminant) / (2 * a);
            float x2 = (-b - sqrtDiscriminant) / (2 * a);
            float y1 = -A/B * x1 - C/B;
            float y2 = -A/B * x2 - C/B;

            if ((Math::min(line->x1, line->x2) <= x1 && x1 <= Math::max(line->x1, line->x2) &&
                 Math::min(line->y1, line->y2) <= y1 && y1 <= Math::max(line->y1, line->y2)) ||
                (Math::min(line->x1, line->x2) <= x2 && x2 <= Math::max(line->x1, line->x2) &&
                 Math::min(line->y1, line->y2) <= y2 && y2 <= Math::max(line->y1, line->y2))
                    ) {
                if (flip)
                    return {true, Vector(circle->x - (x1 + x2) / 2, circle->y - (y1 + y2) / 2).getNormal(), circle, line};
                else
                    return {true, Vector(circle->x - (x1 + x2) / 2, circle->y - (y1 + y2) / 2).getNormal(), line, circle};
            }
        }

        return {};
    }
};

#endif //PHYZIX_BOUNDARYCALCULATIONS_H
