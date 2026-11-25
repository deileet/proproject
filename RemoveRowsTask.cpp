#include "RemoveRowsTask.h"

#include <utility>
#include <vector>

/**
 * @details Конструктор просто передаёт параметры базовому классу Exercise,
 * который создаст и заполнит матрицу.
 */
miit::algebra::RemoveRowsTask::RemoveRowsTask(
    const std::size_t rowCount, const std::size_t columnCount, Generator& gen)
    : Exercise(rowCount, columnCount, gen)
{
}

/**
 * @details Готовая матрица передаётся базовому конструктору без повторного
 * заполнения генератором. Так второй пункт варианта работает с исходными данными.
 */
miit::algebra::RemoveRowsTask::RemoveRowsTask(Matrix<int> source, Generator& gen)
    : Exercise(std::move(source), gen)
{
}

/**
 * @details Второй элемент имеет индекс 1, предпоследний — columnCount - 2.
 * Если столбцов меньше двух, сравнивать не с чем и метод сразу выходит.
 *
 * Перебор идёт СНИЗУ ВВЕРХ. Когда мы удаляем строку, строки выше не меняют
 * свои индексы, поэтому последующие проверки остаются правильными. Если бы мы шли
 * сверху вниз, после удаления индексы съехали бы и часть строк была бы пропущена.
 *
 * Удаление выполняется методом Matrix::removeRow() — без создания новой матрицы.
 * Это проще для понимания и экономит память.
 */
void miit::algebra::RemoveRowsTask::solve()
{
    const std::size_t rowCount = this->matrix.getRows();
    const std::size_t columnCount = this->matrix.getColumns();

    if (rowCount == 0 || columnCount < 2)
    {
        return;
    }

    constexpr std::size_t secondIndex = 1;
    const std::size_t preLastIndex = columnCount - 2;

    for (std::size_t row = rowCount; row > 0; --row)
    {
        const std::size_t index = row - 1;
        const std::vector<int> currentRow = this->matrix.getRow(index);

        if (currentRow[secondIndex] > currentRow[preLastIndex])
        {
            this->matrix.removeRow(index);
        }
    }
}
