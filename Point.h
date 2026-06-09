#pragma once
#include <iostream>

namespace geometry {
    class Point {
    private:
        double x;
        double y;
        double z;

    public:
        Point(double x = 0.0, double y = 0.0, double z = 0.0);
        double getX();
        double getY();
        double getZ();
        double distanceTo(Point& other);
        bool operator==(Point& other);
        bool operator!=(Point& other);
        friend std::ostream& operator<<(std::ostream& os, Point& point);
        friend std::istream& operator>>(std::istream& is, Point& point);
    };
}
