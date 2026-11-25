#include "CppUnitTest.h"

#include <sstream>
#include <stdexcept>
#include <vector>

#include "ConstGenerator.h"
#include "IStreamGenerator.h"
#include "Matrix.h"
#include "RandomGenerator.h"
#include "RemoveRowsTask.h"
#include "ReplaceMultiplesTask.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace miit::algebra;

namespace Variant12Tests
{
    /**
     * @brief Тесты шаблонного класса Matrix
     */
    TEST_CLASS(MatrixTests)
    {
    public:
        /** @brief Пустая матрица имеет нулевые размеры и пустую строку */
        TEST_METHOD(DefaultConstructorCreatesEmptyMatrix)
        {
            const Matrix<int> matrix;
            Assert::AreEqual(static_cast<std::size_t>(0), matrix.getRows());
            Assert::AreEqual(static_cast<std::size_t>(0), matrix.getColumns());
            Assert::AreEqual(std::string(""), matrix.toString());
        }

        /** @brief Конструктор размера создаёт нули */
        TEST_METHOD(ParameterizedConstructorFillsWithZero)
        {
            const Matrix<int> matrix(2, 3);
            Assert::AreEqual(static_cast<std::size_t>(2), matrix.getRows());
            Assert::AreEqual(static_cast<std::size_t>(3), matrix.getColumns());
            Assert::AreEqual(0, matrix[1][2]);
        }

        /** @brief Копия не зависит от оригинала, перемещение опустошает источник */
        TEST_METHOD(CopyAndMoveConstructors)
        {
            Matrix<int> source(2, 2);
            source[0][0] = 7;

            const Matrix<int> copy(source);
            Assert::AreEqual(7, copy[0][0]);

            const Matrix<int> moved(std::move(source));
            Assert::AreEqual(7, moved[0][0]);
            Assert::AreEqual(static_cast<std::size_t>(0), source.getRows());
        }

        /** @brief Индексация работает и выбрасывает исключение за границей */
        TEST_METHOD(SubscriptChecksBounds)
        {
            Matrix<int> matrix(1, 1);
            matrix[0][0] = 4;
            Assert::AreEqual(4, matrix[0][0]);
            Assert::ExpectException<std::out_of_range>([&matrix]() { matrix[1][0] = 1; });
        }

        /** @brief Вывод и ввод матрицы согласованы между собой */
        TEST_METHOD(StreamRoundTrip)
        {
            std::istringstream input("2 2\n1 2\n3 4");
            Matrix<int> matrix;
            input >> matrix;

            std::ostringstream output;
            output << matrix;

            Assert::AreEqual(static_cast<std::size_t>(2), matrix.getRows());
            Assert::AreEqual(4, matrix[1][1]);
            Assert::AreEqual(std::string("2 2\n1\t2\n3\t4"), output.str());
        }
    };

    /**
     * @brief Тесты трёх реализаций Generator
     */
    TEST_CLASS(GeneratorTests)
    {
    public:
        /** @brief ConstGenerator возвращает одно и то же значение */
        TEST_METHOD(ConstGeneratorAlwaysReturnsSameValue)
        {
            const ConstGenerator generator(42);
            Assert::AreEqual(42, generator.generate());
            Assert::AreEqual(42, generator.generate());
        }

        /** @brief RandomGenerator не выходит за диапазон */
        TEST_METHOD(RandomGeneratorKeepsRange)
        {
            RandomGenerator generator(-5, 5);
            for (int i = 0; i < 100; ++i)
            {
                const int value = generator.generate();
                Assert::IsTrue(value >= -5 && value <= 5);
            }
        }

        /** @brief IStreamGenerator читает числа из потока по очереди */
        TEST_METHOD(StreamGeneratorReadsValues)
        {
            std::istringstream input("10 20 30");
            IStreamGenerator generator(input);
            Assert::AreEqual(10, generator.generate());
            Assert::AreEqual(20, generator.generate());
            Assert::AreEqual(30, generator.generate());
        }
    };

    /**
     * @brief Тесты двух заданий варианта 12
     */
    TEST_CLASS(TaskTests)
    {
    public:
        /** @brief Кратные 3 и отрицательные кратные заменяются нулём */
        TEST_METHOD(ReplaceMultiplesOfThree)
        {
            std::istringstream input("3 4 5 -6 7 9 1 0 8");
            IStreamGenerator generator(input);
            ReplaceMultiplesTask task(3, 3, generator);
            task.solve();

            const Matrix<int>& result = task.getMatrix();
            Assert::AreEqual(0, result[0][0]);
            Assert::AreEqual(4, result[0][1]);
            Assert::AreEqual(0, result[1][0]);
            Assert::AreEqual(0, result[1][2]);
            Assert::AreEqual(1, result[2][0]);
            Assert::AreEqual(8, result[2][2]);
        }

        /** @brief Удаляются только строки со вторым элементом больше предпоследнего */
        TEST_METHOD(RemoveRowsBySecondAndPreLast)
        {
            std::istringstream input(
                "5 1 2 9 "
                "5 8 2 9 "
                "5 3 7 9");
            IStreamGenerator generator(input);
            RemoveRowsTask task(3, 4, generator);
            task.solve();

            const Matrix<int>& result = task.getMatrix();
            Assert::AreEqual(static_cast<std::size_t>(2), result.getRows());
            Assert::AreEqual(static_cast<std::size_t>(4), result.getColumns());
            Assert::AreEqual(1, result[0][1]);
            Assert::AreEqual(3, result[1][1]);
        }

        /** @brief Один столбец — сравнить не с чем, строки остаются */
        TEST_METHOD(SingleColumnMatrixIsKept)
        {
            std::istringstream input("1 2 3");
            IStreamGenerator generator(input);
            RemoveRowsTask task(3, 1, generator);
            task.solve();

            Assert::AreEqual(static_cast<std::size_t>(3), task.getMatrix().getRows());
        }
    };
}
