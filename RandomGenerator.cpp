#include "RandomGenerator.h"

/**
 * @details Инициализация идёт в списке инициализации в том же порядке,
 * в котором поля объявлены в заголовочном файле. Условие min < max
 * сначала нормализует границы, затем они копируются в константные поля,
 * после чего создаётся distribution с уже правильными границами.
 */
miit::algebra::RandomGenerator::RandomGenerator(const int min, const int max)
    : minValue(min < max ? min : max),
      maxValue(min < max ? max : min),
      engine(std::random_device{}()),
      distribution(minValue, maxValue)
{
}

/**
 * @details Обращение distribution(engine) возвращает следующее число
 * равномерного распределения. Внутреннее состояние engine при этом меняется,
 * поэтому метод не объявлен const.
 */
int miit::algebra::RandomGenerator::generate()
{
    return this->distribution(this->engine);
}
