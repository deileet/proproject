#include <cstdlib>
#include <iostream>
#include <string>
#include "RegularHexagon.h"

namespace
{
    void prepareConsole()
    {
#ifdef _WIN32
        std::system("chcp 1251 > nul");
#else
#endif
    }

    /**
    *@brief Выполняет чтение координат из стандартного потока.
    *@param hint Пояснительное сообщение для пользователя.
    *@return Объект созданной точки.
    */
    Vertex2D readVertex(const std::string& hint)
    {
        std::cout << hint << '\n';

        double xVal = 0.0;
        double yVal = 0.0;
        std::cin >> xVal >> yVal;

        if (std::cin.fail())
        {
            std::cout << "Ошибка 1\n";
            std::exit(EXIT_FAILURE);
        }

        return Vertex2D(xVal, yVal);
    }

    /**
    *@brief Выполняет чтение радиуса описанной окружности.
    *@return Значение радиуса.
    */
    double readRadius()
    {
        std::cout << "Введите радиус описанной окружности R: " << '\n';

        double radius = 0.0;
        std::cin >> radius;

        if (std::cin.fail() || radius <= 0.0)
        {
            std::cout << "Ошибка 1\n";
            std::exit(EXIT_FAILURE);
        }

        return radius;
    }
}

/**
*@brief Точка входа в программу.
*@return 0, если программа выполнена корректно.
*/
int main()
{
    prepareConsole();

    const Vertex2D center = readVertex("Введите координаты центра (x y): ");
    const double radius = readRadius();
    const Vertex2D probe = readVertex("Введите точку на окружности (x y): ");

    const RegularHexagon hexagon(center, radius, probe);

    std::cout << "Длина стороны: " << hexagon.sideLength() << std::endl;
    std::cout << "Площадь фигуры: " << hexagon.surfaceArea() << std::endl;

    return EXIT_SUCCESS;
}
