#include "line.h"
#include <iostream>
#include <cmath>

Line::Line(const Point& point1, const Point& point2)
{
    this->p1 = point1;
    this->p2 = point2;

    if (p1 == p2)
    {
        std::cout << "Ошибка: Точки совпадают! Прямая не может быть определена." << std::endl;
        exit(1);
    }
}

bool Line::isPointOnLine(const Point& p) const
{
    double crossProduct = (p.getX() - p1.getX()) * (p2.getY() - p1.getY()) - 
                          (p.getY() - p1.getY()) * (p2.getX() - p1.getX());
    
    const double eps = 1e-9;
    return std::abs(crossProduct) < eps;
}

double Line::distanceToPoint(const Point& p) const
{
    double numerator = std::abs((p2.getY() - p1.getY()) * p.getX() - 
                                (p2.getX() - p1.getX()) * p.getY() + 
                                p2.getX() * p1.getY() - 
                                p2.getY() * p1.getX());
    
    double denominator = std::sqrt(std::pow(p2.getY() - p1.getY(), 2) + 
                                   std::pow(p2.getX() - p1.getX(), 2));
    
    return numerator / denominator;
}