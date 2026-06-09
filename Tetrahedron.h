#pragma once
#include "RegularSolid.h"
#include "Point.h"
#include <vector>

namespace geometry {
    enum class SphereType {
        Inscribed,
        Circumscribed
    };

    class Tetrahedron : public RegularSolid {
    private:
        enum { VERTEX_COUNT = 4 };
        std::vector<Point> vertices;
        bool isValidTetrahedron();
        double getEdgeLength();

    public:
        Tetrahedron();
        Tetrahedron(Point& p1, Point& p2, Point& p3, Point& p4);
        Tetrahedron(double x1, double y1, double z1,
            double x2, double y2, double z2,
            double x3, double y3, double z3,
            double x4, double y4, double z4);
        Tetrahedron(Point& center, double edgeLength, SphereType sphereType);
        Tetrahedron(Tetrahedron& other);
        Tetrahedron& operator=(Tetrahedron& other);
        double getSurfaceArea() override;
        double getVolume() override;
        std::string ToString() override;
        void read(std::istream& is) override;
        bool operator==(Tetrahedron& other);
        bool operator!=(Tetrahedron& other);
        std::vector<Point> getVertices();
        static std::string ToString(Tetrahedron& tetrahedron);
        static Tetrahedron readFromStream(std::istream& is);
        static Tetrahedron createFromCircumscribedSphere(Point& center, double edgeLength);
        static Tetrahedron createFromInscribedSphere(Point& center, double edgeLength);
    };
}
