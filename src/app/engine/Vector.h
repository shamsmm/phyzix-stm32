//
// Created by shams on 9/10/24.
//

#ifndef PHYZIX_VECTOR_H
#define PHYZIX_VECTOR_H


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
};


#endif //PHYZIX_VECTOR_H
