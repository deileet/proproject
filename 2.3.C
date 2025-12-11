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
 * @brief Программа проверяет, можно ли вырезать из круга с радиусом r прямоугольники a*b и c*d
 * @param r Параметр r
 * @param a Параметр a
 * @param b Параметр b
 * @param c Параметр c
 * @param d Параметр d
 * @return возвращает bool значение
 */

bool canICutTwoPlates(const double r, const double a, const double b, const double c, const double d);


/**
 * @brief Точка входа в программу
 * @return возвращает 0, если программма выполнена корректно
 */
int main(void)
{   printf("Enter radius:\n");
    const double r = getValue();
    checkValue(r);
    printf("Enter value a:\n");
    const double a = getValue();
    checkValue(a);
    printf("Enter value b:\n");
    const double b = getValue();
    checkValue(b);
    printf("Enter value c:\n");
    const double c = getValue();
    checkValue(c);
    printf("Enter value d:\n");
    const double d = getValue();
    checkValue(d);
    if (canICutTwoPlates(r,a,b,c,d))
    {
      printf("Rectangles can be cut from a given circle!\n");  
    }
    else
    {
        printf("Rectangles can'not be cut from a given circle!\n");
    }
    return 0;
}
 
double getValue(void)
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
    if (!(value >= DBL_EPSILON))
    {
        fprintf(stderr, "Value have to be possitive\n");
        exit(1);
    }
}
 
 
bool canICutTwoPlates(const double r, const double a, const double b, const double c, const double d)
{
    if (((a * b + c * d) - (M_PI * r * r) <= DBL_EPSILON) &&
        (sqrt(a * a + b * b) - (2 * r) <= DBL_EPSILON) &&
       (sqrt(c * c + d * d) - (2 * r) <= DBL_EPSILON))
    {
        if (sqrt(a * a + b * b) + sqrt(c * c + d * d) - 2 * r <= DBL_EPSILON) return true;
        else if (fmax(a, c) <= 2 * r && (b + d) <= 2 * r) return true;
        else if (fmax(a, d) <= 2 * r && (b + c) <= 2 * r) return true;
        else if (fmax(b, c) <= 2 * r && (a + d) <= 2 * r) return true;
        else if (fmax(b, d) <= 2 * r && (a + c) <= 2 * r) return true;
    
    }

    return false;

} 


