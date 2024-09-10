#include <cstdint>
#include <iostream>
#include <cassert>
#include <cmath>
#include "app/math/Math.h"
#include "app/engine/Boundary.h"
#include "app/engine/CircleBoundary.h"

volatile uint32_t Tick;

using namespace std;

#define ALMOST_EQUALS(x,y) fabs(x - y) < 0.001

void math_tests();
void boundary_tests();

int main() {
    cout << "=================== Tests started.            ===================" << endl;

    cout << "=================== Maths Tests.              ===================" << endl;
    math_tests();

    cout << "=================== Boundary Tests.           ===================" << endl;
    boundary_tests();

    cout << "=================== Tests ended successfully. ===================" << endl;
}

void math_tests() {
    assert(ALMOST_EQUALS(Math::pow(2.5, 3), pow(2.5, 3)));
    assert(ALMOST_EQUALS(Math::pow(17, 2), pow(17, 2)));
    assert(ALMOST_EQUALS(Math::pow(17, -2), pow(17, -2)));

    assert(ALMOST_EQUALS(Math::fabs(-1.223), fabs(-1.223)));
    assert(ALMOST_EQUALS(Math::fabs(-9.653), fabs(-9.653)));
    assert(ALMOST_EQUALS(Math::fabs(8.572), fabs(8.572)));

    assert(ALMOST_EQUALS(Math::sqrt(5), sqrt(5)));
    assert(ALMOST_EQUALS(Math::sqrt(4), sqrt(4)));
    assert(ALMOST_EQUALS(Math::sqrt(2.5), sqrt(2.5)));
    assert(ALMOST_EQUALS(Math::sqrt(100), sqrt(100)));
}

void boundary_tests() {
    Boundary * b1, * b2;

    b1 = new CircleBoundary(5, 5 , 3);
    b2 = new CircleBoundary(20 + 0.1, 5 , 12);
    assert(!b1->intersects(b2));

    b1 = new CircleBoundary(5, 5 , 3);
    b2 = new CircleBoundary(20 - 0.1, 5 , 12);
    assert(b1->intersects(b2));

    b1 = new CircleBoundary(5, 5 , 3);
    b2 = new CircleBoundary(20 - 0.1, 5 - 0.1 , 12);
    assert(b1->intersects(b2));

    b1 = new CircleBoundary(5, 5 , 3);
    b2 = new CircleBoundary(20 - 0.1, 5 + 0.1 , 12);
    assert(b1->intersects(b2));
}