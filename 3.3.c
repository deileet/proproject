#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

/**
 * @brief Считывает вещественное значение с клавиатуры с проверкой ввода
 * @return считанное значение
 */
double getDouble(void);

/**
 * @brief Проверяет, что минимальное значение меньше максимального
 * @param min минимальное значение промежутка
 * @param max максимальное значение промежутка
 */
void checkMM(const double min, const double max);

/**
 * @brief Проверяет, что число положительное
 * @param value проверяемое значение
 */
void checkPositive(const double value);

/**
 * @brief Вычисляет функцию f(x) = -ln(2 + 2x + x²)
 * @param x значение параметра x
 * @return рассчитанное значение
 */
double lnFunc(const double x);

/**
 * @brief Вычисляет коэффициент рекуррентного выражения
 * @param n текущий индекс
 * @param x значение параметра x
 * @return рассчитанное значение 
 */
double getRecurrent(const int n, const double x);

/**
 * @brief Считает сумму членов последовательности с точностью e
 * @param e заданная точность
 * @param x значение параметра x
 * @return рассчитанное значение
 */
double getSumE(const double e, const double x);


/**
 * @brief Точка входа в программу
 * @return 0, если программа выполнена корректно, иначе 1
 */
int main(void)
{
    printf("Enter the starting value: ");
    double min = getDouble();
    printf("Enter the final value: ");
    double max = getDouble();
    checkMM(min, max);
    printf("Enter step: ");
    double step = getDouble();
    checkPositive(step);
    printf("Enter precision e: ");
    double e = getDouble();
    checkPositive(e);
    
    for (double x = min; x <= max + DBL_EPSILON; x += step)
    {
        printf("x = %.4lf, f(x) = %.6lf, S = %.6lf\n", x, lnFunc(x), getSumE(e, x));
    }
    return 0;
}

double getDouble(void)
{
    double value = 0;
    if (!scanf("%lf", &value))
    {
        fprintf(stderr, "Error!\n");
        exit(1);
    }
    return value;
}

void checkMM(const double min, const double max)
{
    if (min - DBL_EPSILON >= max)
    {
        fprintf(stderr, "Error!\n");
        exit(1);
    }
}

void checkPositive(const double value)
{
    if (value <= DBL_EPSILON)
    {
        fprintf(stderr, "Error!\n");
        exit(1);
    }
}

double lnFunc(const double x)
{
    return -log(2.0 + 2.0 * x + x * x);
}

double getRecurrent(const int n, const double x)
{
    return -(1.0 + x) * (1.0 + x) * n / (n + 1.0); //разложение ряда
}

double getSumE(const double e, const double x)
{
    double current = -(1.0 + x) * (1.0 + x);  // а0
    double sum = current;
    
    for (int n = 1; fabs(current) > e; n++)
    {
        current *= getRecurrent(n, x);
        sum += current;
    }
    return sum;
}
