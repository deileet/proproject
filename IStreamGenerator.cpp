#include "IStreamGenerator.h"

/**
 * @details Ссылочное поле обязательно инициализировать в списке
 * инициализации — так объект будет ссылаться именно на переданный поток.
 */
miit::algebra::IStreamGenerator::IStreamGenerator(std::istream& in)
    : in(in)
{
}

/**
 * @details Если в потоке больше нет корректных данных, operator>> оставляет
 * значение value равным нулю, поэтому метод безопасно вернёт 0.
 */
int miit::algebra::IStreamGenerator::generate()
{
    int value = 0;
    this->in >> value;
    return value;
}
