#pragma once

/**
 * @brief Класс Точка на плоскости
 */
class Point
{
private:
    /**
     * @brief Координата X
     */
    double x;
    /**
     * @brief Координата Y
     */
    double y;

public:
    /**
     * @brief Конструктор точки
     * @param x координата X (по умолчанию 0)
     * @param y координата Y (по умолчанию 0)
     */
    Point(double x = 0, double y = 0);

    /**
     * @brief Получение координаты X
     * @return координата X
     */
    double getX() const;

    /**
     * @brief Получение координаты Y
     * @return координата Y
     */
    double getY() const;

    /**
     * @brief Проверка на равенство точек
     * @param p точка для сравнения
     * @return true, если точки равны
     */
    bool operator==(const Point& p) const;

    /**
     * @brief Проверка на неравенство точек
     * @param p точка для сравнения
     * @return true, если точки не равны
     */
    bool operator!=(const Point& p) const;
};