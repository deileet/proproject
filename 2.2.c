#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
/**
 * @brief считывает значение, введенное с клавиатуры с проверкой ввода
 * @return считанное значение
 */
double getValue(void);
 
/**
 * @brief Программа вычисляет вычисленное значение y, если известно введенное число
 * @param x Параметр x
 * @return Возвращает вычисленное значение y
 */
double getY(const double x);
 
 
/**
 * @brief Точка входа в программу
 * @return возвращает 0, если программма выполнена корректно
 */
int main(void)
{
    printf("enter x value:\n");
    const double x = getValue();
    printf("y = %.2lf\n ", getY(x));
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
 
 
double getY(const double x)
{
    const double a = 1.6;
    if ((x - a)  > DBL_EPSILON)
    {
        return exp(a * x) - 2.5;
    }
    else if (fabs(x) < DBL_EPSILON)
    {
        return 3;
    }
    else if ((x - a) < DBL_EPSILON)
    {
        return a / x + sin(x);
    }
    else
    {
        return NAN;
    }
}