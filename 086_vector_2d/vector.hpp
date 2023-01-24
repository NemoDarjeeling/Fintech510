/* write your class interface in this file
   write function definitions only if they are very short
 */
#include <cmath>
#include <cstdio>

class Vector2D {
private:
  double x;
  double y;
public:
  Vector2D ();

  Vector2D (double init_x, double init_y);

  double getMagnitude() const {
    return std::sqrt((x * x) + (y * y));  
  }

  Vector2D operator+(const Vector2D & rhs) const;

  Vector2D & operator+=(const Vector2D & rhs);

  double dot(const Vector2D & rhs) const;

  void print() const;
};