#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
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
 * @param dlina Параметр длины круга
 * @return Возвращает вычисленную площадь круга  
 */
double getSquare(const double dlina);
 
 
/**
 * @brief Точка входа в программу
 * @return возвращает 0, если программма выполнена корректно
 */
int main(void){
    printf("Введите число:\n");
    double dlina = getValue();
    checkValue(dlina);
    printf("square = %.2lf\n", getSquare(dlina));
    return 0;
}
 
double getValue(void){
    double value = 0;
    if (!scanf("%lf", &value))
    {
        printf("Error\n");
        abort();
    }
    return value;
}
 
void checkValue(const double value){
    if (value <= 0)
    {
        printf("Value have to be possitive\n");
        abort();
    }
}
 
double getSquare(const double dlina){
    double rad = dlina / (2 * M_PI);
    return rad * rad * M_PI;
}