#include <stdio.h>
#include <math.h>

/**
 * @brief рассчитывает значение функции y по заданной формуле
 * @param x значение 
 * @return 
 */
double getY(void);

/**
 * @brief Точка входа в программу
 * @return возвращает 0, если программма выполнена корректно
 */
int main(void)
{
	getY();
    return 0;
}

double getY(void)
{
    for (double x = 1;  x - 3  <=  1e-10  ; x = x + 0.2)
    {
       printf("y = %.4lf\n",  3 *  x - 14 + exp(x) - exp(-x));
    }
    return 0;
}