//
// Created by shams on 8/8/24.
//

#ifndef PHYZIX_MATH_H
#define PHYZIX_MATH_H


class Math{
public:
    static float pow(float base, int exponent) {
        float result = 1;

        if (exponent > 0)
            while (exponent--)
                result *= base;
        else if (exponent < 0)
            while (exponent++)
                result /= base;

        return result;
    }

    static float fabs(float n) {
        return n < 0 ? -n : n;
    }

    static float sqrt(float n) {
        if (n == 0) return 0;

        double x = n;
        double y = 1.0;
        double epsilon = 0.000001; // Desired precision

        while (fabs(x - y) > epsilon) {
            x = (x + y) / 2;
            y = n / x;
        }

        return x;
    }
};


#endif //PHYZIX_MATH_H
