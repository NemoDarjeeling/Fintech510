#include <cmath>
#include <cstdio>

class Point {
private:
    double x;
    double y;
public:
    Point ();//default constructor
    void move(double dx, double dy);
    double distanceFrom(const Point & p);
};