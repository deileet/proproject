#pragma once

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Генератор, всегда возвращающий одно и то же число
     *
     * Используется для заполнения матрицы одинаковым значением (константой).
     */
    class ConstGenerator : public Generator
    {
    private:
        /** @brief Константное значение, возвращаемое при каждом вызове */
        const int value;

    public:
        /**
         * @brief Конструктор
         * @param val Значение константы (по умолчанию 0)
         */
        explicit ConstGenerator(const int val = 0);

        /**
         * @brief Получить константное значение
         * @return Всегда значение поля value
         */
        int generate() override;
    };
}
