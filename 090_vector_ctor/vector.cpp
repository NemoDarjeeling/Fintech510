#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */

Vector2D::Vector2D (): x(0.00), y(0.00) {}

Vector2D::Vector2D (double init_x, double init_y): x(init_x), y(init_y) {}

Vector2D Vector2D::operator+(const Vector2D & rhs) const {//const inside, don't change things passed in; const outside, don't change things returned
    Vector2D ans;
    ans.x = x + rhs.x;
    ans.y = y + rhs.y;
    return ans;//return const, a=ans, if shallow copy, can not change a; if deep copy, can change a; but under no circunstances can you change ans
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
    return x * rhs.x + y * rhs.y;
}

void Vector2D::print() const {
    printf("<%.2f, %.2f>", x, y);
}