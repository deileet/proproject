#include "Point.h"
#include "Hexagon.h"
#include <iostream> 
#include <cmath>

using namespace std;

Figure::Figure(Point& center_p, double rad, Point& edge_p)
{
    origin = Point(center_p.get_x(), center_p.get_y());
    border_point = Point(edge_p.get_x(), edge_p.get_y());
    outer_radius = rad;

    double actual_dist = sqrt(pow(edge_p.get_x() - center_p.get_x(), 2) +
        pow(edge_p.get_y() - center_p.get_y(), 2));

    if (abs(actual_dist - rad) > std::numeric_limits<double>::epsilon() || rad <= 0 || check_equal(center_p, edge_p))
    {
        cout << "Ошибка 2\n";
        exit(1);
    }
}

double Figure::calculate_edge()
{
    return outer_radius;
}

double Figure::calculate_square()
{
    return (1.5 * sqrt(3.0)) * pow(outer_radius, 2);
}
