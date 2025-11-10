#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES
/**
 *@brief Программа вычисляет функцию А, когда известны переменные x,y,z
 *@param x Переменная x
 *@param y Переменная y
 *@param z Переменная z
 *@return Возвращает вычисленную функцию 
 */

double getA(const double x, const double y, const double z);
/**
 * @brief Программа вычисляет функцию B, когда известны переменные x,y,z
 * @param x Переменная x
 * @param y Переменная y
 * @param z Переменная z
 * @return Возвращает вычисленную функцию
 */
double getB(const double x, const double y, const double z);

/**
 * @brief Точка входа
 * @return Возвращает 0, если программа выполнена корректно
 */

int main(void)
{
    const double x =1.4, y=3.1, z=0.5;
    printf("A = %lf\n",getA(x,y,z));
    printf("B = %lf\n",getB(x,y,z));
    return 0;
}
double getA(const double x, const double y, const double z)
{
    return pow((z*x*sin(2*x)+exp(-2*x)*(x+y)),0.5);
}
double getB(const double x, const double y, const double z)
{
    return exp(2*x)*log(z+x)-pow(y,3*x)*log(y-x);
}