#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

/**
 * @brief - Программа вычисляет периметр треугольника
 * @param x - Значение параметра x
 * @param y - Значение параметра y
 * @param z - Значение параметра z
 * @return - Возвращает полученную функцию периметра треугольника 
 */

double getPerimeter(const double x, const double y, const double z);


/**
 * @brief - Программа вычисляет площадь треугольника
 * @param x - Значение параметра x
 * @param y - Значение параметра y
 * @param z - Значение параметра z
 * @return - Возвращает полученную функцию площадь треугольника 
 */

double getArea(const double x, const double y, const double z);


/**
 * @brief Считывает значение, введенное с клавиатуры с проверкой ввода
 * @return Считанное значение
 */
double getValue(void);


/**
 * @brief Проверяет,что переменная положительная
 * @param value Значение проверяемой переменно
 */
void checkValue(const double value);


/**
 * @brief Проверяет, что треугольник существует
 * @return При правильном выполнении 0, иначе возвращает 1
 */
double isTriangle(const double x, const double y, const double z);


/**
 * @brief Программа запрашивает у пользователя стороны, затем при правильности введенных сторон, расчитываеет периметр и площадь треугольника
 * @return Возвращает 0 при правильном выполнении программы
 */

int main(void)
{
    printf("Write the first side:\n");
    const double x = getValue();
    checkValue(x);
    printf("Write the second side:\n");
    const double y = getValue();
    checkValue(y);
    printf("Write the third side:\n");
    const double z = getValue();
    checkValue(z);
    isTriangle(x, y, z);
    printf("Perimeter = %.2lf\n", getPerimeter(x,y,z));
    printf("Area = %.2lf\n", getArea(x,y,z));
    return 0;
}

double getValue(void)
{
    double value = 0;
    if (!scanf("%lf", &value))
    {
        fprintf(stderr, "Error\n");
        exit(1);
    }
    return value;
}


void checkValue(const double value)
{
    if (!(value >= DBL_EPSILON))
    {
        fprintf(stderr, "Value have to be possitive\n");
        exit(1);
    }
}

double isTriangle(const double x, const double y, const double z)
{
    if (!((x + z - y > DBL_EPSILON) && (x + y - z > DBL_EPSILON) && (z + y - x > DBL_EPSILON)))
    {
        fprintf(stderr, "Such a triangle does not exist\n");
        exit(1);
    }
}

double getPerimeter(const double x, const double y, const double z)
{
    return x + y + z;
}

double getArea(const double x, const double y, const double z)
{
    const double p = (x + y + z) / 2;
    return sqrt(p * (p - x) * (p - y) * (p - z));
}