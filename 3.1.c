#include <stdio.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>

/**
 * @brief считывает значение,
 * введенное с клавиатуры с проверкой ввода
 * @return считанное значение
 */
double getValue();

/**
 * @brief проверяет,что переменная положительная
 * @param step значение проверяемой переменной
 */
void checkStep(const double step);

/**
 * @brief рассчитывает значение функции y по заданной формуле
 * @param x значение x
 * @return 
 */
double getY(const double x);


/**
 * @brief проверят, больше ли старт функции или нет
 * @return возвращает ошибку, если старт больше чем конец, иначе ничего не возвращает
 */
void checkStartEnd(const double start, const double end);

/**
 * @brief Точка входа в программу
 * @return возвращает 0, если программма выполнена корректно
 */
int main(void)
{
	
    printf("Enter the starting value: ");
	const double start = getValue();
	printf("Enter the final value: ");
	const double end = getValue();
	checkStartEnd(start, end);
	printf("Enter step: ");
	const double step = getValue();
	checkStep(step);
	for (double x = start; x <= end + DBL_EPSILON; x = x + step)
	{
        printf("x = %.2lf, y = %.4lf\n", x, getY(x));
	}
	return 0;
}


double getY(const double x)
{
    return 3 * x - 14 + exp(x) - exp(-x);
}

double getValue(void)
{
	double value = 0;
	if (!scanf_s("%lf", &value))
	{
		fprintf(stderr, "Error\n");
		exit(1);    
	}
	return value;
}

void checkStep(const double step)
{
	if (step <= DBL_EPSILON)
	{
		fprintf(stderr, "Error!\n");
		exit(1);
	}	
}


void checkStartEnd(const double start, const double end)
{
	if (start > end + DBL_EPSILON)
	{
		fprintf(stderr, "Error!");
		exit(1);
	}
}
