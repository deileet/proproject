#include "ConstGenerator.h"

/**
 * @details Поле объявлено const, поэтому его можно инициализировать
 * только в списке инициализации конструктора.
 */
miit::algebra::ConstGenerator::ConstGenerator(const int val)
    : value(val)
{
}

/**
 * @details Никакого состояния не меняется: метод просто возвращает сохранённое число.
 */
int miit::algebra::ConstGenerator::generate()
{
    return this->value;
}
