#pragma once

#include <random>

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Генератор псевдослучайных чисел в заданном диапазоне
     *
     * Использует std::mt19937 как источник случайных бит и
     * std::uniform_int_distribution для равномерного распределения
     * на отрезке [minValue; maxValue].
     */
    class RandomGenerator : public Generator
    {
    private:
        /** @brief Левая граница диапазона (не меняется после создания) */
        const int minValue;

        /** @brief Правая граница диапазона (не меняется после создания) */
        const int maxValue;

        /** @brief Генератор псевдослучайных чисел (состояние меняется при вызове) */
        std::mt19937 engine;

        /** @brief Распределение, превращающее случайные биты в число из диапазона */
        std::uniform_int_distribution<int> distribution;

    public:
        /**
         * @brief Конструктор генератора
         * @param min Левая граница диапазона
         * @param max Правая граница диапазона
         * @details Если min больше max, границы автоматически меняются местами
         */
        RandomGenerator(const int min, const int max);

        /**
         * @brief Получить очередное случайное число
         * @return Число из диапазона [minValue; maxValue]
         */
        int generate() override;
    };
}
