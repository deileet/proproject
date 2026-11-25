#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Шаблонный двумерный массив (матрица)
     * @tparam T Тип элементов матрицы (в задании используется int)
     *
     * Хранилище — вектор векторов: data[i] это i-я строка, data[i][j] — элемент.
     * Дополнительно хранятся размеры rows и columns, чтобы не вычислять их
     * каждый раз через size().
     */
    template <typename T>
    class Matrix
    {
    private:
        /** @brief Вектор строк; каждая строка — вектор элементов типа T */
        std::vector<std::vector<T>> data;

        /** @brief Количество строк */
        std::size_t rows = 0;

        /** @brief Количество столбцов */
        std::size_t columns = 0;

    public:
        /**
         * @brief Конструктор по умолчанию
         * @details Создаёт пустую матрицу 0×0. Благодаря инициализаторам
         * полей rows и columns равны нулю даже при = default.
         */
        Matrix() = default;

        /**
         * @brief Конструктор матрицы заданного размера
         * @param rowCount Количество строк
         * @param columnCount Количество столбцов
         * @details Все элементы автоматически инициализируются нулями
         * благодаря value-initialization в std::vector<T>(columnCount).
         */
        Matrix(const std::size_t rowCount, const std::size_t columnCount)
            : data(rowCount, std::vector<T>(columnCount)),
              rows(rowCount),
              columns(columnCount)
        {
        }

        /** @brief Конструктор копирования (глубокое копирование за счёт std::vector) */
        Matrix(const Matrix&) = default;

        /** @brief Конструктор перемещения (передаёт владение буферами векторов) */
        Matrix(Matrix&&) noexcept = default;

        /** @brief Деструктор: освобождение памяти выполняет std::vector */
        ~Matrix() = default;

        /** @brief Оператор присваивания копированием */
        Matrix& operator=(const Matrix&) = default;

        /** @brief Оператор присваивания перемещением */
        Matrix& operator=(Matrix&&) noexcept = default;

        /**
         * @brief Получить количество строк
         * @return Значение поля rows
         */
        std::size_t getRows() const noexcept
        {
            return this->rows;
        }

        /**
         * @brief Получить количество столбцов
         * @return Значение поля columns
         */
        std::size_t getColumns() const noexcept
        {
            return this->columns;
        }

        /**
         * @brief Получить строку для чтения и изменения
         * @param rowIndex Индекс строки (отсчёт с нуля)
         * @return Ссылка на вектор-строку
         * @throw std::out_of_range Если индекс больше или равен числу строк
         */
        std::vector<T>& operator[](const std::size_t rowIndex)
        {
            if (rowIndex >= this->rows)
            {
                throw std::out_of_range("Индекс строки вышел за границы матрицы");
            }
            return this->data[rowIndex];
        }

        /**
         * @brief Получить строку только для чтения
         * @param rowIndex Индекс строки (отсчёт с нуля)
         * @return Константная ссылка на вектор-строку
         * @throw std::out_of_range Если индекс больше или равен числу строк
         */
        const std::vector<T>& operator[](const std::size_t rowIndex) const
        {
            if (rowIndex >= this->rows)
            {
                throw std::out_of_range("Индекс строки вышел за границы матрицы");
            }
            return this->data[rowIndex];
        }

        /**
         * @brief Получить копию строки
         * @param rowIndex Индекс строки
         * @return Вектор значений строки
         * @details Возвращается копия, поэтому изменить матрицу через результат нельзя
         */
        std::vector<T> getRow(const std::size_t rowIndex) const
        {
            return this->operator[](rowIndex);
        }

        /**
         * @brief Удалить строку по индексу
         * @param index Индекс удаляемой строки (отсчёт с нуля)
         * @details Удаление делается на месте: вектор строк сдвигает хвост влево,
         * а счётчик rows уменьшается на единицу. Это проще, чем строить новую матрицу.
         * Вызывающий должен идти снизу вверх, чтобы индексы нижних строк не сдвигались.
         * @throw std::out_of_range Если index больше или равен числу строк
         */
        void removeRow(const std::size_t index)
        {
            if (index >= this->rows)
            {
                throw std::out_of_range("Индекс удаляемой строки вышел за границы матрицы");
            }
            this->data.erase(this->data.begin() + static_cast<std::ptrdiff_t>(index));
            --this->rows;
        }

        /**
         * @brief Заполнить матрицу значениями генератора
         * @param generator Генератор, у которого будет вызван generate() для каждой ячейки
         * @details Обход идёт построчно: строка за строкой, внутри строки слева направо.
         * Результат приводится к типу T через static_cast.
         */
        void fill(Generator& generator)
        {
            for (auto& row : this->data)
            {
                for (auto& item : row)
                {
                    item = static_cast<T>(generator.generate());
                }
            }
        }

        /**
         * @brief Представить содержимое матрицы в виде строки
         * @return Элементы разделены табуляцией, строки — переносом строки
         */
        std::string toString() const
        {
            std::ostringstream stream;
            for (std::size_t i = 0; i < this->rows; ++i)
            {
                for (std::size_t j = 0; j < this->columns; ++j)
                {
                    stream << this->data[i][j];
                    if (j + 1 < this->columns)
                    {
                        stream << '\t';
                    }
                }
                if (i + 1 < this->rows)
                {
                    stream << '\n';
                }
            }
            return stream.str();
        }

        /**
         * @brief Оператор вывода матрицы в поток
         * @param os Поток вывода
         * @param matrix Матрица, которую нужно вывести
         * @return Тот же поток для цепочки вызовов
         * @details Сначала пишутся размеры "строки столбцы", затем содержимое
         */
        friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
        {
            os << matrix.getRows() << ' ' << matrix.getColumns() << '\n';
            os << matrix.toString();
            return os;
        }

        /**
         * @brief Оператор ввода матрицы из потока
         * @param is Поток ввода
         * @param matrix Матрица, которая будет перезаписана
         * @return Тот же поток
         * @details Ожидаемый формат: сначала два числа — размеры, затем все элементы.
         * Временная матрица нужна, чтобы при ошибке чтения исходная матрица не изменилась.
         */
        friend std::istream& operator>>(std::istream& is, Matrix<T>& matrix)
        {
            std::size_t rowCount = 0;
            std::size_t columnCount = 0;
            if (!(is >> rowCount >> columnCount))
            {
                return is;
            }

            if (rowCount == 0 && columnCount == 0)
            {
                matrix = Matrix<T>();
                return is;
            }
            if (rowCount == 0 || columnCount == 0)
            {
                is.setstate(std::ios::failbit);
                return is;
            }

            Matrix<T> temp(rowCount, columnCount);
            for (std::size_t i = 0; i < rowCount; ++i)
            {
                for (std::size_t j = 0; j < columnCount; ++j)
                {
                    if (!(is >> temp[i][j]))
                    {
                        return is;
                    }
                }
            }
            matrix = std::move(temp);
            return is;
        }
    };
}
