#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief считывает целое значение с проверкой ввода
 * @return Введенное значение
 */
int getInt();

/**
 * @brief считывает вещественное значение с проверкой ввода
 * @return Введенное значение
 */
double getDouble();

/**
 * @brief рассчитывает сумму первых n членов последовательности
 * @param n - количество членов для суммирования
 * @return рассчитанная сумма
 */
double sumN(const int n);

/**
 * @brief рассчитывает сумму членов с точностью e
 * @param e - заданная точность (минимальное значение члена)
 * @return рассчитанная сумма
 */
double sumE(const double e);

/**
 * @brief проверяет, что число положительное
 * @param value - проверяемое значение
 */
void checkValue(const double value);



/**
 * @brief Точка входа в программу
 * @return возвращает 0, если программма выполнена корректно
 */
int main(void)
{
    printf("Enter value n: ");
    int n = getInt();
    checkValue(n);
    printf("Sum of the first %d terms of the series = %.4lf\n", n, sumN(n));
    printf("Enter value e: ");
    double e = getDouble();
    checkValue(e);
    printf("sum of the first terms of the series with accuracy %.5lf = %.5lf\n", e, sumE(e));    
    return 0;
}

int getInt()
{
    int value = 0;
    if (!scanf("%d", &value))
    {
        fprintf(stderr, "Error\n");
        exit(1);
    }
    return value;
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

void checkValue(const double value)
{
    if (value <= __DBL_EPSILON__)
    {
        fprintf(stderr, "Value have to be positive\n");
        exit(1);
    }
}

double sumN(const int n)
{
    double current = 1.0;
    double sum = current;
    double fact_k = 1.0;
    double fact_k1 = 1.0;
    
    for (int k = 1; k < n; k++)
    {
        fact_k = fact_k * k;
        fact_k1 = fact_k * (k + 1);
        if (k % 2 == 0) {
            current = 1.0 / (fact_k * fact_k1);
        } else {
            current = -1.0 / (fact_k * fact_k1);
        }
        sum += current;
    }
    
    return sum;
}

double sumE(const double e)
{
    double current = 1.0;
    double sum = 0.0;
    int k = 0;
    double fact_k = 1.0;
    double fact_k1 = 1.0;
    while (fabs(current) >= e)
    {
        sum += current;
        k++;
        if (k == 0) {
            current = 1.0;
        } else {
            fact_k = fact_k * k;
            fact_k1 = fact_k * (k + 1);
            if (k % 2 == 0) {
                current = 1.0 / (fact_k * fact_k1);
            } else {
                current = -1.0 / (fact_k * fact_k1);
            }
        }
    }
    
    return sum;
}