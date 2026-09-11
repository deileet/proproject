#include "RegularHexagon.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>

namespace
{
    const double TOLERANCE = std::numeric_limits<double>::epsilon();

    double gapBetween(const Vertex2D& first, const Vertex2D& second)
    {
        const double dx = first.abscissa() - second.abscissa();
        const double dy = first.ordinate() - second.ordinate();
        return std::sqrt(dx * dx + dy * dy);
    }
}

bool RegularHexagon::shapeIsValid(const double radius, const Vertex2D& center, const Vertex2D& probe)
{
    if (radius <= 0.0)
    {
        return false;
    }

    if (areCoincident(center, probe))
    {
        return false;
    }

    const double actualGap = gapBetween(center, probe);
    const double deviation = std::abs(actualGap - radius);
    return deviation <= TOLERANCE;
}

RegularHexagon::RegularHexagon(const Vertex2D& center, const double radius, const Vertex2D& probe)
{
    if (!shapeIsValid(radius, center, probe))
    {
        std::cout << "Ошибка 2\n";
        std::exit(EXIT_FAILURE);
    }

    centerPos = center;
    circumradius = radius;
}

double RegularHexagon::sideLength() const
{
    return circumradius;
}

double RegularHexagon::surfaceArea() const
{
    const double sqrt3 = std::sqrt(3.0);
    const double area = (3.0 * sqrt3) / 2.0;
    return area * circumradius * circumradius;
}
