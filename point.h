#pragma once 

class Point
{
private:
    double x_coord;
    double y_coord;
public:
    Point(double x_val = 0, double y_val = 0);
    double get_x();
    double get_y();
};

bool check_equal(Point first_p, Point second_p);
