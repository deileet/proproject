#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 

/**
 * @brief считывает значение, введенное с клавиатуры с проверкой ввода
 * @return Возвращает считанное значение
 */
double getValue(void);
 
 

/**
 * @brief проверяет,что переменная положительная
 * @param value значение проверяемой переменно
 */
void checkValue(const double value);
 

 
/**
 * @brief Программа вычисляет давление цистерны, если известна высота
 * @param height Параметр высоты цистерны
 * @return Возвращает вычисленное давление 
 */
double getPressure(const double height);



/**
 * @brief Точка входа в программу
 * @return возвращает 0, если программма выполнена корректно
 */
int main(void){
    printf("Введите число:\n");
    double height = getValue();
    checkValue(height);
    printf("Pressure = %.2lf\n", getPressure(height));
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
 
double getPressure(const double height){
    const double g = 9.8, p = 1000;
    return height * g * p;
}