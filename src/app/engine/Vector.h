//
// Created by shams on 9/10/24.
//

#ifndef PHYZIX_VECTOR_H
#define PHYZIX_VECTOR_H

#include "app/math/Math.h"
#ifndef TEST
#include "app/lib/printf.h"
#endif

class Vector
{
public:
    float x; // can be a_x, v_x, x, i, ..
    float y; // can be a_y, v_y, y, j, ..

    Vector(float x, float y) : x(x), y(y) {}

    Vector operator+(Vector other) const
    {
        return {this->x + other.x, this->y + other.y};
    }

    Vector operator*(float scalar) const
    {
        return {this->x * scalar, this->y * scalar};
    }

    float operator*(Vector other) const
    {
        // dot product
        return this->x * other.x + this->y * other.y;
    }

    float getMagnitude() const
    {
        return Math::sqrt(Math::pow(this->x, 2) + Math::pow(this->y, 2));
    }

    float getDirection() const
    {
        if (Math::sign(y) == 1)
        {
            if (Math::sign(x) == 1)
            {
                // First Quad
                return Math::atan(y, x);
            }
            else
            {
                // Second Quad
                return Math::PI - Math::atan(y, x);
            }
        }
        else
        {
            if (Math::sign(x) == 1)
            {
                // Fourth Quad
                return Math::PI + Math::PI - Math::atan(y, x);
            }
            else
            {
                // Third Quad
                return Math::PI + Math::atan(y, x);
            }
        }
    }

    Vector getNormal() const
    {
        float magnitude = getMagnitude();
        return {this->x / magnitude, this->y / magnitude};
    }

    Vector getPerpendicular() const
    {
        return {-this->y, this->x};
    }

    Vector getResolvedAround(Vector normal) const
    {
        float magnitude = getMagnitude();
        float angle = this->getDirection() - normal.getDirection();
        return {-magnitude * Math::sin(angle), magnitude * Math::cos(angle)};
    }

    Vector getUnResolvedFrom(Vector normal) const
    {
        float magnitude = getMagnitude();
        float angle = normal.getDirection();
        return {magnitude * Math::cos(angle), magnitude * Math::sin(angle)};
    }

    static float cross(Vector *v1, Vector *v2)
    {
        return (float)(v1->x * v2->y - v1->y * v2->x);
    }

    static float dot(Vector *v1, Vector *v2)
    {
        return v1->x * v2->x + v1->y * v2->y;
    }

#ifndef TEST
    void print(bool verbose = true) const
    {
        if (verbose)
            printf("Vector x: %f, y: %f (%f, %f)\n", x, y, getMagnitude(), getDirection() * 180 / Math::PI);
        else
            printf("%f |_ %f\n", getMagnitude(), getDirection() * 180 / Math::PI);
    }
#endif
};

#endif // PHYZIX_VECTOR_H
