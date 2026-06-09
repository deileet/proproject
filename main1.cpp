#include <iostream>
#include <string>
#include "point.h"
#include "line.h"

/**
 * @brief Считывает значение, введенное с клавиатуры
 * @param report строка информации для пользователя
 * @return считанное значение
 */
double getValue(const std::string report = "");

/**
 * @brief Точка входа в программу
 * @return 0, если программа выполнена корректно
 */
int main()
{
    std::cout << "=== Определение прямой двумя точками ===" << std::endl;
    
    std::cout << "\nВведите координаты первой точки прямой:" << std::endl;
    double x1 = getValue(" x1: ");
    double y1 = getValue(" y1: ");
    Point point1(x1, y1);
    
    std::cout << "\nВведите координаты второй точки прямой:" << std::endl;
    double x2 = getValue(" x2: ");
    double y2 = getValue(" y2: ");
    Point point2(x2, y2);
    
    Line myLine(point1, point2);
    
    std::cout << "\nВведите координаты третьей точки для проверки:" << std::endl;
    double x3 = getValue(" x3: ");
    double y3 = getValue(" y3: ");
    Point point3(x3, y3);
    
    std::cout << "\n=== Результаты ===" << std::endl;
    if (myLine.isPointOnLine(point3))
    {
        std::cout << "Точка (" << x3 << ", " << y3 << ") ПРИНАДЛЕЖИТ заданной прямой." << std::endl;
    }
    else
    {
        std::cout << "Точка (" << x3 << ", " << y3 << ") НЕ принадлежит заданной прямой." << std::endl;
    }
    
    double distance = myLine.distanceToPoint(point3);
    std::cout << "Расстояние от точки (" << x3 << ", " << y3 << ") до прямой: " << distance << std::endl;
    
    return 0;
}

double getValue(const std::string report)
{
    std::cout << report;
    double value = 0;
    std::cin >> value;
    if (std::cin.fail())
    {
        std::cout << "Ошибка ввода!" << std::endl;
        exit(1);
    }
    return value;
}
