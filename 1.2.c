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
 * @brief проверяет,что переменная положительная
 * @param value значение проверяемой переменно
 */
void checkValue(const double value);
 
 
/**
 * @brief Программа вычисляет площадь круга, если известна длина
 * @param length Параметр длины круга
 * @return Возвращает вычисленную площадь круга  
 */
double getSquare(const double length);
 
 
/**
 * @brief Точка входа в программу
 * @return возвращает 0, если программма выполнена корректно
 */
int main(void){
    printf("Enter value:\n");
    double length = getValue();
    checkValue(length);
    printf("square = %.2lf\n", getSquare(length));
    return 0;
}
 
double getValue(void){
    double value = 0;
    if (!scanf("%lf", &value))
    {
        fprintf(stderr, "Error\n");
        exit(1);
    }
    return value;
}
 
void checkValue(const double value){
    if (!(value >= DBL_EPSILON))
    {
        fprintf(stderr, "Value have to be possitive\n");
        exit(1);
    }
}
 
double getSquare(const double length){
    double rad = length / (2 * (M_PI));
    return rad * rad * (M_PI);
}
