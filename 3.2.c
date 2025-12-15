#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief считывает целое значение с клавиатуры с проверкой ввода
 * @return считанное значение
 */
int getValue(void);

/**
 * @brief считывает вещественное значение с клавиатуры с проверкой ввода
 * @return считанное значение
 */
double getDouble(void);

/**
 * @brief вычисляет сумму членов ряда
 * @param n число членов
 * @return возвращает рассчитанную сумму
 */
double getSumN(const int n);

/**
 * @brief вычисляет сумму ряда с заданной точностью e
 * @param e требуемая точность
 * @return возвращает рассчитанную сумму
 */
double getSumE(const double e);

/**
 * @brief высчитывает коэффициент рекуррентного выражения
 * @param i текущий индекс члена ряда
 * @return возвращает рассчитанное значения коэффициента
 */
double getRecurent(const int i);

/**
 * @brief проверяет что значение неотрицательное
 * @param value проверяемое значение
 */
void checkPositive(const double value);

/**
 * @brief точка входа в программу
 * @return возвращает 0 если программа выполнена корректно
 */
int main(void)
{
    printf("Enter n:\n");
    const int n = getValue();
    checkPositive(n);

    const double sumN = getSumN(n);
    printf("The sum of the %d numbers in the sequence is equal to %.6lf\n", n + 1, sumN);

    printf("Enter e:\n");
    const double e = getDouble();
    checkPositive(e);

    const double sumE = getSumE(e);
    printf("The sum of the sequence with precision %lf is equal to %.6lf\n", e, sumE);

    return 0;
}

int getValue(void)
{
    int value = 0;
    if (!(scanf("%d", &value)))
    {
        fprintf(stderr, "Error\n");
        exit(1);
    }
    return value;
}

double getDouble(void)
{
    double value = 0;
    if (!(scanf("%lf", &value))) 
    {
        fprintf(stderr, "Error\n");
        exit(1);
    }
    return value;
}

double getSumN(const int n)
{
    double current = 1.0;
    double result = current;    
    for (int i = 0; i < n; i++) 
    {
        current *= getRecurent(i);
        result += current;
    }
    return result;
}

double getRecurent(const int i)
{
    return -1.0 / ((i + 2) * (i + 1));
}

void checkPositive(const double value)
{
    if (value < __DBL_EPSILON__) 
    {
        fprintf(stderr, "Error.\n");
        exit(1);
    }
}

double getSumE(const double e)
{
    double current = 1.0;
    double result = 0.0;
    for (int i = 0; fabs(current) > e; i++) 
    {
        result += current;
        current *= getRecurent(i);
    }
    return result;
}
