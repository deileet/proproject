#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

/**
 * @brief Считывает вещественное значение с клавиатуры с проверкой ввода
 * @return считанное значение
 */
double getDouble();

/**
 * @brief Проверяет, что минимальное значение меньше максимального
 * @param min минимальное значение промежутка
 * @param max максимальное значение промежутка
 */
void checkMM(const double min, const double max);

/**
 * @brief Проверяет, что шаг функции положительный
 * @param step значение шага функции
 */
void checkStep(const double step);

/**
 * @brief Проверяет, что число положительное
 * @param value проверяемое значение
 */
void checkPositive(const double value);

/**
 * @brief Вычисляет натуральный логарифм
 * @param x значение параментра x
 * @return рассчитанное значение
 */
double LnFunc(const double x);

/**
 * @brief Вычисляет коэффициент рекуррентного выражения
 * @param n текущий индекс
 * @param x значение параментра x
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
    printf("Enter starting value: ");
    const double min = getDouble();
    printf("Enter final value: ");
    const double max = getDouble();
    checkMM(min, max);
    printf("Enter step: ");
    const double step = getDouble();
    checkStep(step);
    printf("Enter precision e: ");
    const double e = getDouble();
    checkPositive(e);
    for (double x = min; x <= max + DBL_EPSILON; x += step)
    {
        double func_val = LnFunc(x);
        double sum_val = getSumE(e, x);
        printf("x = %.4lf, f(x) = %.6lf, S = %.6lf\n", x, func_val, sum_val);
    }
    return 0;
}

double getDouble()
{
    double value = 0;
    if (!scanf("%lf", &value))
    {
        fprintf(stderr, "Error\n");
        exit(1);
    }
    return value;
}

void checkMM(const double min, const double max)
{
    if (min - DBL_EPSILON >= max)
    {
        fprintf(stderr, "Error, the minimum value must be less than the maximum!\n");
        exit(1);
    }
}

void checkStep(const double step)
{
    if (step <= __DBL_EPSILON__)
    {
        fprintf(stderr, "Value have to be positive\n");
        exit(1);
    }
}

void checkPositive(const double value)
{
    if (value <= __DBL_EPSILON__)
    {
        fprintf(stderr, "Value have to be positive\n");
        exit(1);
    }
}

double LnFunc(const double x)
{
    return -log(2.0 + 2.0 * x + x * x);
}

double getRecurrent(const int n, const double x)
{
    if (x + 1.0 == DBL_EPSILON) return 0;
    return -1 * (1.0 + x) * (1.0 + x) * n / (n + 1.0);
}

double getSumE(const double e, const double x)
{
    double current = -((1.0 + x) * (1.0 + x));
    double sum = current;
    
    for (int n = 1; fabs(current) - e > DBL_EPSILON; n++)
    {
        current *= getRecurrent(n, x);
        sum += current;
    }
    return sum;
}