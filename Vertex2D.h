#pragma once

/**
*@brief Класс для работы с двумерными координатами.
*/
class Vertex2D
{
private:
    /**
    *@brief Значение абсциссы.
    */
    double xPos;
    /**
    *@brief Значение ординаты.
    */
    double yPos;

public:
    /**
    *@brief Инициализирует объект точки.
    *@param xVal Начальная координата x.
    *@param yVal Начальная координата y.
    */
    Vertex2D(const double xVal = 0.0, const double yVal = 0.0);

    /**
    *@brief Получает текущую координату x.
    *@return Значение x.
    */
    double abscissa() const;

    /**
    *@brief Получает текущую координату y.
    *@return Значение y.
    */
    double ordinate() const;
};

/**
*@brief Выполняет проверку идентичности двух точек.
*@param lhs Первая точка для сравнения.
*@param rhs Вторая точка для сравнения.
*@return true, если точки совпадают, иначе false.
*/
bool areCoincident(const Vertex2D& lhs, const Vertex2D& rhs);
