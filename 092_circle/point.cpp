#include "point.hpp"

#include <ctype.h>
#include <cmath>
#include <cstdio>
#include <stdlib.h>

Point::Point(): x(0.00), y(0.00) {}

void Point::move(double dx, double dy) {
    x += dx;
    y += dy;
}

double Point::distanceFrom(const Point & p) {
    double distance = std::sqrt(((p.x - x) * (p.x - x)) + ((p.y - y) * (p.y - y)));
    return distance;
}