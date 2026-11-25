#pragma once

#include <cstddef>
#include <utility>

#include "Generator.h"
#include "Matrix.h"

namespace miit::algebra
{
    /**
     * @brief Базовый абстрактный класс задания
     *
     * Агрегирует (содержит в себе) матрицу и генератор. В конструкторе
     * сразу создаётся матрица нужного размера и заполняется через генератор.
     * Конкретные задания переопределяют solve().
     */
    class Exercise
    {
    protected:
        /** @brief Матрица, с которой работает задание */
        Matrix<int> matrix;

        /** @brief Ссылка на генератор, использованный при заполнении матрицы */
        Generator& generator;

    public:
        /**
         * @brief Конструктор
         * @param rowCount Количество строк матрицы
         * @param columnCount Количество столбцов матрицы
         * @param gen Генератор значений (ссылка на существующий объект, не копия)
         * @details Сначала создаётся матрица, затем вызывается matrix.fill(generator)
         */
        Exercise(const std::size_t rowCount, const std::size_t columnCount, Generator& gen)
            : matrix(rowCount, columnCount), generator(gen)
        {
            this->matrix.fill(this->generator);
        }

        /**
         * @brief Конструктор из уже готовой матрицы
         * @param source Готовая матрица; она перемещается во внутреннее поле
         * @param gen Генератор (сохраняется для единообразия всех заданий)
         * @details Нужен, чтобы второе задание работало с ИСХОДНОЙ матрицей,
         * а не с результатом первого задания. Это делает два пункта варианта
         * независимыми, как и требует условие.
         */
        Exercise(Matrix<int> source, Generator& gen)
            : matrix(std::move(source)), generator(gen)
        {
        }

        /**
         * @brief Виртуальный деструктор по умолчанию
         */
        virtual ~Exercise() = default;

        /**
         * @brief Выполнить задание
         * @details Чисто виртуальный метод: обязателен к переопределению в наследниках
         */
        virtual void solve() = 0;

        /**
         * @brief Получить текущее состояние матрицы
         * @return Константная ссылка на внутреннюю матрицу (изменить её нельзя)
         */
        const Matrix<int>& getMatrix() const noexcept
        {
            return this->matrix;
        }
    };
}
