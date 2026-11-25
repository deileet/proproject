#pragma once

#include <cstddef>

#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Первое задание варианта 12
     *
     * Заменить нулём каждый элемент, который делится на 3 без остатка,
     * просматривая матрицу по столбцам.
     */
    class ReplaceMultiplesTask : public Exercise
    {
    public:
        /**
         * @brief Конструктор
         * @param rowCount Количество строк
         * @param columnCount Количество столбцов
         * @param gen Генератор для первичного заполнения матрицы
         */
        ReplaceMultiplesTask(const std::size_t rowCount, const std::size_t columnCount, Generator& gen);

        /**
         * @brief Конструктор из готовой матрицы
         * @param source Матрица, с которой нужно работать
         * @param gen Генератор (для единообразия с базовым классом)
         */
        ReplaceMultiplesTask(Matrix<int> source, Generator& gen);

        /**
         * @brief Заменить кратные трём элементы нулями
         * @details Изменяет внутреннюю матрицу, возвращаемую getMatrix()
         */
        void solve() override;
    };
}
