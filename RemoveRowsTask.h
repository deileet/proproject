#pragma once

#include <cstddef>

#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Второе задание варианта 12
     *
     * Удалить все строки, у которых второй элемент строго больше
     * предпоследнего элемента той же строки.
     */
    class RemoveRowsTask : public Exercise
    {
    public:
        /**
         * @brief Конструктор
         * @param rowCount Количество строк
         * @param columnCount Количество столбцов
         * @param gen Генератор для первичного заполнения матрицы
         */
        RemoveRowsTask(const std::size_t rowCount, const std::size_t columnCount, Generator& gen);

        /**
         * @brief Конструктор из готовой матрицы
         * @param source Матрица, с которой нужно работать
         * @param gen Генератор (для единообразия с базовым классом)
         */
        RemoveRowsTask(Matrix<int> source, Generator& gen);

        /**
         * @brief Удалить подходящие строки
         * @details Если столбцов меньше двух, сравнивать нечего и матрица не меняется
         */
        void solve() override;
    };
}
