#include "Vertex2D.h"
#include <cmath>
#include <limits>

Vertex2D::Vertex2D(const double xVal, const double yVal) : xPos(xVal), yPos(yVal)
{
}

double Vertex2D::abscissa() const
{
    return xPos;
}

double Vertex2D::ordinate() const
{
    return yPos;
}

bool areCoincident(const Vertex2D& lhs, const Vertex2D& rhs)
{
    const double eps = std::numeric_limits<double>::epsilon();
    const bool xMatches = std::abs(lhs.abscissa() - rhs.abscissa()) < eps;
    const bool yMatches = std::abs(lhs.ordinate() - rhs.ordinate()) < eps;
    return xMatches && yMatches;
}
