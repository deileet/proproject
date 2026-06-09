#include "CppUnitTest.h"
#include "../TetrahedronLib/Tetrahedron.h"
#include "../TetrahedronLib/Point.h"
#include <sstream>
#include <cmath>
#include <memory>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace geometry;

namespace Tests
{
    TEST_CLASS(PointTests)
    {
    public:
        TEST_METHOD(DefaultConstructor_Success)
        {
            Point p;
            Assert::AreEqual(0.0, p.getX());
            Assert::AreEqual(0.0, p.getY());
            Assert::AreEqual(0.0, p.getZ());
        }

        TEST_METHOD(ParameterizedConstructor_Success)
        {
            double x = 3.5;
            double y = 7.2;
            double z = 1.8;
            Point p(x, y, z);
            Assert::AreEqual(x, p.getX());
            Assert::AreEqual(y, p.getY());
            Assert::AreEqual(z, p.getZ());
        }

        TEST_METHOD(DistanceTo_Success)
        {
            Point p1(0, 0, 0);
            Point p2(3, 4, 0);
            double expected1 = 5.0;

            Point p3(1, 2, 2);
            Point p4(4, 6, 10);
            double expected2 = std::sqrt(89.0);

            double dist1 = p1.distanceTo(p2);
            double dist2 = p3.distanceTo(p4);

            Assert::AreEqual(expected1, dist1, 1e-6);
            Assert::AreEqual(expected2, dist2, 1e-6);
        }

        TEST_METHOD(EqualityOperator_Success)
        {
            Point p1(2.5, 3.5, 4.5);
            Point p2(2.5, 3.5, 4.5);
            Point p3(2.5, 4.0, 4.5);
            Assert::IsTrue(p1 == p2);
            Assert::IsFalse(p1 == p3);
        }

        TEST_METHOD(InequalityOperator_Success)
        {
            Point p1(2.5, 3.5, 4.5);
            Point p2(2.5, 3.5, 4.5);
            Point p3(2.5, 4.0, 4.5);
            Assert::IsFalse(p1 != p2);
            Assert::IsTrue(p1 != p3);
        }

        TEST_METHOD(OutputStreamOperator_Success)
        {
            Point p(3.14, 2.71, 1.41);
            std::stringstream ss;
            ss << p;
            std::string result = ss.str();
            Assert::IsTrue(result.find("(") != std::string::npos);
            Assert::IsTrue(result.find(")") != std::string::npos);
        }

        TEST_METHOD(InputStreamOperator_Success)
        {
            Point p;
            std::stringstream ss("(15.5, 20.3, 25.7)");
            double expectedX = 15.5;
            double expectedY = 20.3;
            double expectedZ = 25.7;
            ss >> p;
            Assert::AreEqual(expectedX, p.getX());
            Assert::AreEqual(expectedY, p.getY());
            Assert::AreEqual(expectedZ, p.getZ());
        }
    };

    TEST_CLASS(TetrahedronTests)
    {
    public:
        TEST_METHOD(DefaultConstructor_Success)
        {
            Tetrahedron t;
            Assert::IsTrue(true);
        }

        TEST_METHOD(ConstructorWithPoints_Success)
        {
            Point p1(1, 1, 1);
            Point p2(1, -1, -1);
            Point p3(-1, 1, -1);
            Point p4(-1, -1, 1);
            double expectedSurface = std::sqrt(3.0) * 8.0;
            double expectedVolume = std::sqrt(2.0) * std::pow(std::sqrt(8.0), 3) / 12.0;
            Tetrahedron t(p1, p2, p3, p4);
            Assert::AreEqual(expectedSurface, t.getSurfaceArea(), 1e-6);
            Assert::AreEqual(expectedVolume, t.getVolume(), 1e-6);
        }

        TEST_METHOD(ConstructorWithCoordinates_Success)
        {
            double expectedSurface = std::sqrt(3.0) * 8.0;
            Tetrahedron t(1, 1, 1, 1, -1, -1, -1, 1, -1, -1, -1, 1);
            Assert::AreEqual(expectedSurface, t.getSurfaceArea(), 1e-6);
        }

        TEST_METHOD(CopyConstructor_Success)
        {
            Point p1(1, 1, 1);
            Point p2(1, -1, -1);
            Point p3(-1, 1, -1);
            Point p4(-1, -1, 1);
            Tetrahedron original(p1, p2, p3, p4);
            Tetrahedron copy(original);
            Assert::IsTrue(original == copy);
        }

        TEST_METHOD(AssignmentOperator_Success)
        {
            Point p1(1, 1, 1);
            Point p2(1, -1, -1);
            Point p3(-1, 1, -1);
            Point p4(-1, -1, 1);
            Tetrahedron original(p1, p2, p3, p4);
            Tetrahedron assigned;
            assigned = original;
            Assert::IsTrue(original == assigned);
        }

        TEST_METHOD(EqualityOperator_Success)
        {
            Point p1(1, 1, 1);
            Point p2(1, -1, -1);
            Point p3(-1, 1, -1);
            Point p4(-1, -1, 1);
            Tetrahedron t1(p1, p2, p3, p4);
            Tetrahedron t2(p1, p2, p3, p4);
            Tetrahedron t3(Point(0, 0, 0), 2.0, SphereType::Circumscribed);
            Assert::IsTrue(t1 == t2);
            Assert::IsFalse(t1 == t3);
        }

        TEST_METHOD(InequalityOperator_Success)
        {
            Point p1(1, 1, 1);
            Point p2(1, -1, -1);
            Point p3(-1, 1, -1);
            Point p4(-1, -1, 1);
            Tetrahedron t1(p1, p2, p3, p4);
            Tetrahedron t2(p1, p2, p3, p4);
            Tetrahedron t3(Point(0, 0, 0), 2.0, SphereType::Circumscribed);
            Assert::IsFalse(t1 != t2);
            Assert::IsTrue(t1 != t3);
        }

        TEST_METHOD(GetSurfaceArea_Edge1_Success)
        {
            Tetrahedron t(Point(0, 0, 0), 1.0, SphereType::Circumscribed);
            double expected = std::sqrt(3.0);
            double result = t.getSurfaceArea();
            Assert::AreEqual(expected, result, 1e-6);
        }

        TEST_METHOD(GetSurfaceArea_Edge2_Success)
        {
            Tetrahedron t(Point(0, 0, 0), 2.0, SphereType::Inscribed);
            double expected = 4.0 * std::sqrt(3.0);
            double result = t.getSurfaceArea();
            Assert::AreEqual(expected, result, 1e-6);
        }

        TEST_METHOD(GetVolume_Edge1_Success)
        {
            Tetrahedron t(Point(0, 0, 0), 1.0, SphereType::Circumscribed);
            double expected = std::sqrt(2.0) / 12.0;
            double result = t.getVolume();
            Assert::AreEqual(expected, result, 1e-6);
        }

        TEST_METHOD(GetVolume_Edge2_Success)
        {
            Tetrahedron t(Point(0, 0, 0), 2.0, SphereType::Inscribed);
            double expected = std::sqrt(2.0) * 8.0 / 12.0;
            double result = t.getVolume();
            Assert::AreEqual(expected, result, 1e-6);
        }

        TEST_METHOD(ToString_Success)
        {
            Point p1(1, 1, 1);
            Point p2(1, -1, -1);
            Point p3(-1, 1, -1);
            Point p4(-1, -1, 1);
            Tetrahedron t(p1, p2, p3, p4);
            std::string result = t.ToString();
            Assert::IsTrue(result.find("Tetrahedron") != std::string::npos);
            Assert::IsTrue(result.find("v1=") != std::string::npos);
            Assert::IsTrue(result.find("v2=") != std::string::npos);
            Assert::IsTrue(result.find("v3=") != std::string::npos);
            Assert::IsTrue(result.find("v4=") != std::string::npos);
        }

        TEST_METHOD(InvalidVertices_ThrowsException)
        {
            auto func = []() {
                Tetrahedron t(0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3);
                };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        TEST_METHOD(NegativeEdgeLength_ThrowsException)
        {
            auto func = []() {
                Tetrahedron t(Point(0, 0, 0), -1.0, SphereType::Circumscribed);
                };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        TEST_METHOD(ZeroEdgeLength_ThrowsException)
        {
            auto func = []() {
                Tetrahedron t(Point(0, 0, 0), 0.0, SphereType::Circumscribed);
                };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        TEST_METHOD(Polymorphism_Success)
        {
            Point p1(1, 1, 1);
            Point p2(1, -1, -1);
            Point p3(-1, 1, -1);
            Point p4(-1, -1, 1);
            Tetrahedron t(p1, p2, p3, p4);
            double expectedSurface = std::sqrt(3.0) * 8.0;
            RegularSolid* solid = &t;
            double result = solid->getSurfaceArea();
            Assert::AreEqual(expectedSurface, result, 1e-6);
        }

        TEST_METHOD(CreateFromCircumscribedSphere_Success)
        {
            Point center(1.0, 2.0, 3.0);
            double edgeLength = 2.0;
            double expected = edgeLength * edgeLength * std::sqrt(3.0);
            Tetrahedron t = Tetrahedron::createFromCircumscribedSphere(center, edgeLength);
            Assert::AreEqual(expected, t.getSurfaceArea(), 1e-6);
        }

        TEST_METHOD(CreateFromInscribedSphere_Success)
        {
            Point center(1.0, 2.0, 3.0);
            double edgeLength = 3.0;
            double expected = edgeLength * edgeLength * std::sqrt(3.0);
            Tetrahedron t = Tetrahedron::createFromInscribedSphere(center, edgeLength);
            Assert::AreEqual(expected, t.getSurfaceArea(), 1e-6);
        }

        TEST_METHOD(GetVertices_Success)
        {
            Point p1(1, 1, 1);
            Point p2(1, -1, -1);
            Point p3(-1, 1, -1);
            Point p4(-1, -1, 1);
            Tetrahedron t(p1, p2, p3, p4);
            std::vector<Point> verts = t.getVertices();
            Assert::AreEqual(size_t(4), verts.size());
        }
    };
}
