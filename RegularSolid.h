#pragma once
#include <iostream>
#include <string>

namespace geometry {
    class RegularSolid {
    public:
        virtual ~RegularSolid() = default;
        virtual double getSurfaceArea() = 0;
        virtual double getVolume() = 0;
        virtual std::string ToString() = 0;
        virtual void read(std::istream& is) = 0;
        friend std::ostream& operator<<(std::ostream& os, RegularSolid& solid);
        friend std::istream& operator>>(std::istream& is, RegularSolid& solid);
        static std::string ToString(RegularSolid& solid);
        static RegularSolid* readFromStream(std::istream& is);
    };
}
