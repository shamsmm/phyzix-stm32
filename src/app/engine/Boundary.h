//
// Created by shams on 8/7/24.
//

#ifndef PHYZIX_BOUNDARY_H
#define PHYZIX_BOUNDARY_H


#include <cstdint>
#include "Vector.h"
#include "app/lib/rtti.h"

class Boundary;

/**
 * @struct Boundaries
 * @brief A struct to hold a list of boundaries
 * @warning The list is not managed by the struct, it is the responsibility of the user to manage the memory
 * @note This is a workaround for the lack of dynamic arrays standard libraries for low-power embedded systems
 */
struct Boundaries {
    Boundary ** list; /**< dynamic array of Boundary pointers */
    uint16_t count; /**< number of boundaries in the list */
};

/**
 * @struct BoundaryIntersectionResult
 * @brief A struct to hold the result of a *possible* intersection between two boundaries
 */
struct BoundaryIntersectionResult {
    /** a boolean to indicate if the boundaries intersected */
    bool intersected = false;
    /** the normal vector of the intersection, pointing from the other boundary to the current boundary BoundaryIntersectionResult::it */
    Vector normal{0, 0};
    /** the current boundary */
    Boundary * it;
    /** the other boundary */
    Boundary * other;
};

/**
 * @class Boundary
 * @brief An abstract class to represent a boundary
 */
class Boundary: public RuntimeBaseTypeIdentifiable {
public:
    float e = 0.8; /**< Coefficient of restitution */

    RuntimeBaseType getBaseType() const override {
        return RuntimeBaseType::BOUNDARY;
    }

    /**
     * @brief A pure virtual function to check if the boundary intersects with another boundary
     * @param other
     * @return ::BoundaryIntersectionResult
     */
    virtual BoundaryIntersectionResult intersects(Boundary * other) = 0;

    /**
     * @brief A static function to check if two boundaries (list) intersect
     * @param b1
     * @param b2
     * @return ::BoundaryIntersectionResult
     * @see ::Boundaries
     */
    static BoundaryIntersectionResult intersects(Boundaries b1, Boundaries b2) {
        for(int i = 0; i < b1.count; ++i) {
            for (int j = i; j < b2.count; ++j) {
                auto intersection = b1.list[i]->intersects(b2.list[j]);
                if (intersection.intersected)
                    return intersection;
            }
        }

        return {false, Vector(0,0)};
    }
};

#endif //PHYZIX_BOUNDARY_H
