#pragma once

#include <iostream>

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Генератор, читающий значения из потока ввода
     *
     * Реализует тот же интерфейс Generator, но вместо случайного числа
     * извлекает очередное целое из std::istream. По умолчанию используется
     * стандартный поток ввода std::cin, как и в условии задания.
     */
    class IStreamGenerator : public Generator
    {
    private:
        /** @brief Ссылка на поток, откуда берутся числа */
        std::istream& in;

    public:
        /**
         * @brief Конструктор
         * @param in Поток ввода; по умолчанию std::cin
         */
        explicit IStreamGenerator(std::istream& in = std::cin);

        /**
         * @brief Считать очередное число из потока
         * @return Считанное значение (0, если ввод уже не удался)
         */
        int generate() override;
    };
}
