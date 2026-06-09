#pragma once
#include "Point.h"

class Figure
{
private:
    Point origin;
    Point border_point;
    double outer_radius;

public:
    Figure(Point& center_p, double rad, Point& edge_p);
    double calculate_edge();
    double calculate_square();
};
