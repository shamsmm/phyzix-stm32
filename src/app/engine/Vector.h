//
// Created by shams on 9/10/24.
//

#ifndef PHYZIX_VECTOR_H
#define PHYZIX_VECTOR_H


#include "app/math/Math.h"

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

    Vector getNormal() const {
        float magnitude = getMagnitude();
        return {this->x / magnitude, this->y / magnitude};
    }
};


#endif //PHYZIX_VECTOR_H
