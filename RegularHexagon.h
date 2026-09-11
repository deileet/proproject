#pragma once
#include "Vertex2D.h"

/**
*@brief Класс для моделирования правильного шестиугольника.
*/
class RegularHexagon
{
private:
    /**
    *@brief Центральная точка фигуры.
    */
    Vertex2D centerPos;
    /**
    *@brief Дистанция от центра до вершины.
    */
    double circumradius;

    /**
    *@brief Проверяет корректность параметров фигуры.
    *@param radius Величина радиуса.
    *@param center Точка центра.
    *@param probe Точка на окружности.
    *@return true, если параметры корректны, иначе false.
    */
    static bool shapeIsValid(const double radius, const Vertex2D& center, const Vertex2D& probe);

public:
    /**
    *@brief Конструктор правильного шестиугольника.
    *@param center Точка центра.
    *@param radius Величина радиуса.
    *@param probe Точка на окружности.
    */
    RegularHexagon(const Vertex2D& center, const double radius, const Vertex2D& probe);

    /**
    *@brief Определяет размер стороны фигуры.
    *@return Длина стороны.
    */
    double sideLength() const;

    /**
    *@brief Вычисляет общую площадь фигуры.
    *@return Значение площади.
    */
    double surfaceArea() const;
};
