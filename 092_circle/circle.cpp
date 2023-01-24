#include <cstdio>
#include <ctype.h>
#include <cmath>
#include <stdlib.h>

//如果在对应的hpp里面include过了，就不用再在cpp里面include了#include "point.hpp"
#include "circle.hpp"

Circle::Circle(): center(), radius(0.00) {}

Circle::Circle(Point init_c, double init_r): center(init_c), radius(init_r) {}

void Circle::move (double dx, double dy) {
    center.Point::move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
    double intersec = 0.00;
    double distance = center.Point::distanceFrom(otherCircle.center);
    if (distance >= (radius + otherCircle.radius)) {
        intersec = 0.00;
        return intersec;
    }
    else if (distance <= fabs(radius - otherCircle.radius) && distance >= 0) {
        if (radius > otherCircle.radius) {
            intersec = M_PI * otherCircle.radius * otherCircle.radius;
            return intersec;
        }
        else {
            intersec = M_PI * radius * radius;
            return intersec;
        }
    }
    else {
        double A1 = 2 * acos((distance * distance + radius * radius - otherCircle.radius * otherCircle.radius) / (2 * distance * radius));
        double A2 = 2 * acos((distance * distance + otherCircle.radius * otherCircle.radius - radius * radius) / (2 * distance * otherCircle.radius));
        double s1 = 0.5 * radius * radius * sin(A1) +0.5 * otherCircle.radius * otherCircle.radius * sin(A2);
        double s2 = (A1) / 2 * radius * radius + (A2) / 2 * otherCircle.radius * otherCircle.radius;
        intersec = s2 -s1;
        return intersec;
    }
}
