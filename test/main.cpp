#include <cstdint>
#include <iostream>
#include <cassert>
#include <cmath>
#include "app/math/Math.h"
#include "app/engine/Boundary.h"
#include "app/engine/CircleBoundary.h"
#include "app/engine/Scene.h"
#include "app/engine/LineSegmentBoundary.h"

volatile uint32_t Tick;

using namespace std;

#define ALMOST_EQUALS(x,y) fabs(x - y) < 0.001
#define ALMOST_EQUALS_LOOSELY(x,y) fabs(x - y) < 0.01

void math_tests();
void vector_tests();
void boundary_tests();

int main() {
    cout << "=================== Tests **STARTED**.            ===================" << endl;

    cout << "=================== Maths Tests.                  ===================" << endl;
    math_tests();

    cout << "=================== Vector Tests.                 ===================" << endl;
    vector_tests();

    cout << "=================== Boundary Tests.               ===================" << endl;
    boundary_tests();

    cout << "=================== Tests **ENDED** successfully. ===================" << endl;
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

    assert(ALMOST_EQUALS_LOOSELY(Math::cos(0), cos(0)));
    assert(ALMOST_EQUALS_LOOSELY(Math::cos(M_PI), cos(M_PI)));
    assert(ALMOST_EQUALS_LOOSELY(Math::cos(M_PI + 0.5), cos(M_PI + 0.5)));
    assert(ALMOST_EQUALS_LOOSELY(Math::cos(2 * M_PI + 0.5), cos(2 * M_PI + 0.5)));
    assert(ALMOST_EQUALS_LOOSELY(Math::cos(M_PI/2), cos(M_PI/2)));
    assert(ALMOST_EQUALS_LOOSELY(Math::cos(3.223), cos(3.223)));
    assert(ALMOST_EQUALS_LOOSELY(Math::cos(0.456), cos(0.456)));
    assert(ALMOST_EQUALS_LOOSELY(Math::cos(2 * M_PI), cos(0)));
    assert(ALMOST_EQUALS_LOOSELY(Math::sin(1.45), sin(1.45)));
    assert(ALMOST_EQUALS_LOOSELY(Math::cos(-0), cos(-0)));
    assert(ALMOST_EQUALS_LOOSELY(Math::cos(-M_PI), cos(-M_PI)));
    assert(ALMOST_EQUALS_LOOSELY(Math::cos(-M_PI -0.5), cos(-M_PI - 0.5)));
    assert(ALMOST_EQUALS_LOOSELY(Math::cos(-2 * M_PI - 0.5), cos(-2 * M_PI - 0.5)));
    assert(ALMOST_EQUALS_LOOSELY(Math::cos(-M_PI/2), cos(-M_PI/2)));
    assert(ALMOST_EQUALS_LOOSELY(Math::cos(-3.223), cos(-3.223)));
    assert(ALMOST_EQUALS_LOOSELY(Math::cos(-0.456), cos(-0.456)));
    assert(ALMOST_EQUALS_LOOSELY(Math::cos(-2 * M_PI), cos(-0)));
    assert(ALMOST_EQUALS_LOOSELY(Math::sin(-1.45), sin(-1.45)));

    assert(ALMOST_EQUALS_LOOSELY(Math::atan(1), atan(1)));
    assert(ALMOST_EQUALS_LOOSELY(Math::atan(0.1), atan(0.1)));
    assert(ALMOST_EQUALS_LOOSELY(Math::atan(8), atan(8)));
    assert(ALMOST_EQUALS_LOOSELY(Math::atan(10), atan(10)));
    assert(ALMOST_EQUALS_LOOSELY(Math::atan(-1), atan(-1)));
    assert(ALMOST_EQUALS_LOOSELY(Math::atan(-0.1), atan(-0.1)));
    assert(ALMOST_EQUALS_LOOSELY(Math::atan(-8), atan(-8)));
    assert(ALMOST_EQUALS_LOOSELY(Math::atan(-10), atan(-10)));
}

void vector_tests() {

    Vector a = {1,1};
    assert(ALMOST_EQUALS_LOOSELY(a.getDirection(), atan(1.0/1)));
    assert(ALMOST_EQUALS_LOOSELY(a.getMagnitude(), sqrt(2)));

    Vector b = {3,4};
    assert(ALMOST_EQUALS_LOOSELY(b.getDirection(), atan(4.0/3)));
    assert(ALMOST_EQUALS_LOOSELY(b.getMagnitude(), 5));

    Vector x = {1, 0};
    Vector a_x = Vector(-sqrt(2) * sin(atan(1/1) - 0), sqrt(2) * cos(atan(1/1) - 0));
    assert(ALMOST_EQUALS_LOOSELY(a_x.x, a.getResolvedAround(x).x));
    assert(ALMOST_EQUALS_LOOSELY(a_x.y, a.getResolvedAround(x).y));

    Vector wall = {-1,0};
    Vector a_wall = Vector(-sqrt(2) * sin(atan(1/1) - Math::PI), sqrt(2) * cos(atan(1/1) - Math::PI));
    assert(ALMOST_EQUALS_LOOSELY(a_wall.x, a.getResolvedAround(wall).x));
    assert(ALMOST_EQUALS_LOOSELY(a_wall.y, a.getResolvedAround(wall).y));

    Vector v = {0, -10};
    Vector ground = {0, 1};
    Vector v_g = v.getResolvedAround(ground);
    v_g.y *= -1;
    v = v_g.getUnResolvedFrom(ground);
    assert(v.y == 10);

    Vector c = {0, -1};
    assert(ALMOST_EQUALS(c.getDirection(), 270 * 2 * Math::PI/360));

    Vector *v1 = new Vector(2, 4);
    Vector *v2 = new Vector(3, -1);

    assert(Vector::cross(v1, v2) == -14);
    assert(Vector::dot(v1, v2) == 2);
}

void boundary_tests() {
    Boundary * b1, * b2;

    b1 = new CircleBoundary(5, 5 , 3);
    b2 = new CircleBoundary(20 + 0.1, 5 , 12);

    assert(!b1->intersects(b2).intersected);

    b1 = new CircleBoundary(5, 5 , 3);
    b2 = new CircleBoundary(20 - 0.1, 5 , 12);
    assert(b1->intersects(b2).intersected);

    b1 = new CircleBoundary(5, 5 , 3);
    b2 = new CircleBoundary(20 - 0.1, 5 - 0.1 , 12);
    assert(b1->intersects(b2).intersected);

    b1 = new CircleBoundary(5, 5 , 3);
    b2 = new CircleBoundary(20 - 0.1, 5 + 0.1 , 12);
    assert(b1->intersects(b2).intersected);

    auto * scene = new Scene(160, 256);
    scene->boundaries.list = new Boundary * [4];
    scene->boundaries.count = 4;
    scene->boundaries.list[0] = new LineSegmentBoundary(0.0,0.0,0,160.0); // "|.."
    scene->boundaries.list[1] = new LineSegmentBoundary(0.0,0,128,0.0); // "__"
    scene->boundaries.list[2] = new LineSegmentBoundary(128,0.0,128,160.0); // "..|"
    scene->boundaries.list[3] = new LineSegmentBoundary(0.0,160,128,160.0); // "^^"

    CircleBoundary * b = new CircleBoundary(50,50,5);

    assert(!b->intersects(scene->boundaries.list[0]).intersected);
    assert(!b->intersects(scene->boundaries.list[1]).intersected);
    assert(!b->intersects(scene->boundaries.list[2]).intersected);
    assert(!b->intersects(scene->boundaries.list[3]).intersected);

    b->x = 2;
    assert(b->intersects(scene->boundaries.list[0]).intersected);
    assert(b->intersects(scene->boundaries.list[0]).normal.getDirection() == 0);
    assert(!b->intersects(scene->boundaries.list[1]).intersected);
    assert(!b->intersects(scene->boundaries.list[2]).intersected);
    assert(!b->intersects(scene->boundaries.list[3]).intersected);

    b->x = 126;
    assert(!b->intersects(scene->boundaries.list[0]).intersected);
    assert(!b->intersects(scene->boundaries.list[1]).intersected);
    assert(b->intersects(scene->boundaries.list[2]).intersected);
    assert(b->intersects(scene->boundaries.list[2]).normal.getDirection() == Math::PI);
    assert(!b->intersects(scene->boundaries.list[3]).intersected);

    LineSegmentBoundary* l1 = new LineSegmentBoundary(1, 1, 4, 4);
    LineSegmentBoundary* l2 = new LineSegmentBoundary(5, 5, 8, 8);

    assert(l1->getLengthSquared() == 18);
    assert(LineSegmentBoundary::pointOnLine(l1, 2.001, 2));

    BoundaryIntersectionResult intersection = l1->intersects(l2);

}