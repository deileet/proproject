#include "Point.h"
#include <limits>
#include <cmath>

Point::Point(double x_val, double y_val) : x_coord(x_val), y_coord(y_val)
{
}

double Point::get_x()
{
    return x_coord;
}

double Point::get_y()
{
    return y_coord;
}

bool check_equal(Point first_p, Point second_p)
{
    return std::abs(first_p.get_x() - second_p.get_x()) < std::numeric_limits<double>::epsilon() &&
        std::abs(first_p.get_y() - second_p.get_y()) < std::numeric_limits<double>::epsilon();
}
