//
// Created by shams on 9/10/24.
//

#ifndef PHYZIX_VECTOR_H
#define PHYZIX_VECTOR_H


#include "app/math/Math.h"
#include <cstdio>

class Vector {
public:
    float x; // can be a_x, v_x, x, i, ..
    float y; // can be a_y, v_y, y, j, ..

    Vector(float x, float y): x(x), y(y) {}

    Vector operator+(Vector other) const {
        return {this->x + other.x, this->y + other.y};
    }

    Vector operator*(float scalar) const {
        return {this->x * scalar, this->y * scalar};
    }

    float getMagnitude() const {
        return Math::sqrt(Math::pow(this->x, 2) + Math::pow(this->y, 2));
    }

    float getDirection() const {
        if (Math::sign(x) == 1 && Math::sign(y) == 1) {
            return Math::atan(y, x);
        } else if (Math::sign(x) == -1 && Math::sign(y) == 1) {
            return Math::PI - Math::atan(y, x);
        } else if (Math::sign(x) == -1 && Math::sign(y) == -1) {
            return Math::PI + Math::PI / 2 - Math::atan(y, x);
        } else if (Math::sign(x) == 1 && Math::sign(y) == -1) {
            return 2 * Math::PI - Math::atan(y, x);
        }
    }

    Vector getNormal() const {
        float magnitude = getMagnitude();
        return {this->x / magnitude, this->y / magnitude};
    }

    Vector getResolvedAround(Vector normal) const {
        float magnitude = getMagnitude();
        float angle = this->getDirection() - normal.getDirection();
        return { -magnitude * Math::sin(angle), magnitude * Math::cos(angle) };
    }

    void print() {
        printf("Vector x: %f, y: %f (%f, %f)\n", x, y, getMagnitude(), getDirection() * 180 / Math::PI);
    }
};


#endif //PHYZIX_VECTOR_H
