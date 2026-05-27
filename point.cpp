#include "point.h"
#include <cmath>
#include <limits>

Point::Point(double x, double y)
{
    this->x = x;
    this->y = y;
}

double Point::getX() const
{
    return this->x;
}

double Point::getY() const
{
    return this->y;
}

bool Point::operator==(const Point& p) const
{
    const double eps = std::numeric_limits<double>::epsilon();
    return (std::abs(x - p.x) < eps && std::abs(y - p.y) < eps);
}

bool Point::operator!=(const Point& p) const
{
    return !(*this == p);
}