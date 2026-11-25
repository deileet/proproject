#include "ReplaceMultiplesTask.h"

#include <utility>

/**
 * @details Конструктор просто передаёт параметры базовому классу Exercise,
 * который создаст и заполнит матрицу.
 */
miit::algebra::ReplaceMultiplesTask::ReplaceMultiplesTask(
    const std::size_t rowCount, const std::size_t columnCount, Generator& gen)
    : Exercise(rowCount, columnCount, gen)
{
}

/**
 * @details Готовая матрица просто передаётся базовому конструктору.
 */
miit::algebra::ReplaceMultiplesTask::ReplaceMultiplesTask(Matrix<int> source, Generator& gen)
    : Exercise(std::move(source), gen)
{
}

/**
 * @details Внешний цикл идёт по столбцам, внутренний — по строкам.
 * Это соответствует формулировке «каждого столбца».
 * Остаток от деления на 3 равен нулю и для отрицательных чисел,
 * поэтому -6, -9 и т. д. тоже заменяются.
 */
void miit::algebra::ReplaceMultiplesTask::solve()
{
    constexpr int divisor = 3;

    const std::size_t rowCount = this->matrix.getRows();
    const std::size_t columnCount = this->matrix.getColumns();

    for (std::size_t column = 0; column < columnCount; ++column)
    {
        for (std::size_t row = 0; row < rowCount; ++row)
        {
            if (this->matrix[row][column] % divisor == 0)
            {
                this->matrix[row][column] = 0;
            }
        }
    }
}
