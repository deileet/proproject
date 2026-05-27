#pragma once
#include "point.h"

/**
 * @brief Класс Прямая на плоскости
 */
class Line
{
private:
    /**
     * @brief Первая точка прямой
     */
    Point p1;
    /**
     * @brief Вторая точка прямой
     */
    Point p2;

public:
    /**
     * @brief Конструктор прямой по двум точкам
     * @param point1 первая точка
     * @param point2 вторая точка
     */
    Line(const Point& point1, const Point& point2);

    /**
     * @brief Проверка принадлежности точки прямой
     * @param p проверяемая точка
     * @return true, если точка лежит на прямой
     */
    bool isPointOnLine(const Point& p) const;

    /**
     * @brief Вычисление расстояния от точки до прямой
     * @param p точка, от которой вычисляется расстояние
     * @return расстояние от точки до прямой
     */
    double distanceToPoint(const Point& p) const;
};