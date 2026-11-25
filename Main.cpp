#include <cstddef>
#include <iostream>
#include <memory>

#include "ConstGenerator.h"
#include "IStreamGenerator.h"
#include "RandomGenerator.h"
#include "RemoveRowsTask.h"
#include "ReplaceMultiplesTask.h"

using namespace miit::algebra;

/**
 * @brief Способы заполнения матрицы, предлагаемые пользователю
 */
enum class FillMethod
{
    Random = 1,   ///< Случайные числа в диапазоне
    Keyboard = 2, ///< Числа, вводимые с клавиатуры
    Constant = 3  ///< Одно и то же число для всех ячеек
};

/**
 * @brief Спросить пользователя и создать один из трёх генераторов
 * @return Умный указатель на созданный генератор или nullptr при неверном выборе
 * @details std::unique_ptr сам удалит объект в конце области видимости
 */
std::unique_ptr<Generator> createGenerator()
{
    std::cout << "Выберите способ заполнения:\n"
              << static_cast<int>(FillMethod::Random) << " - случайными числами\n"
              << static_cast<int>(FillMethod::Keyboard) << " - с клавиатуры\n"
              << static_cast<int>(FillMethod::Constant) << " - константой\n";

    int choice = 0;
    std::cin >> choice;

    switch (static_cast<FillMethod>(choice))
    {
    case FillMethod::Random:
    {
        int min = 0;
        int max = 0;
        std::cout << "Минимум диапазона: ";
        std::cin >> min;
        std::cout << "Максимум диапазона: ";
        std::cin >> max;
        return std::make_unique<RandomGenerator>(min, max);
    }
    case FillMethod::Keyboard:
    {
        std::cout << "Введите элементы матрицы:\n";
        return std::make_unique<IStreamGenerator>(std::cin);
    }
    case FillMethod::Constant:
    {
        int value = 0;
        std::cout << "Значение константы: ";
        std::cin >> value;
        return std::make_unique<ConstGenerator>(value);
    }
    default:
        std::cout << "Неверный выбор способа заполнения\n";
        return nullptr;
    }
}

/**
 * @brief Точка входа в демонстрационную программу
 * @return 0 при успешном завершении, 1 при неверном выборе генератора
 * @details Оба пункта варианта 12 — НЕЗАВИСИМЫЕ задания. Поэтому сначала
 * создаётся исходная матрица и её копия. Каждое задание получает свою копию
 * исходной матрицы и меняет только её. Так результат первого задания не портит
 * данные второго. Копия делается до вызова solve(), поэтому она остаётся исходной.
 */
int main()
{
    std::size_t rows = 0;
    std::size_t columns = 0;

    std::cout << "Количество строк: ";
    std::cin >> rows;
    std::cout << "Количество столбцов: ";
    std::cin >> columns;

    const std::unique_ptr<Generator> generator = createGenerator();
    if (!generator)
    {
        return 1;
    }

    // Первый объект сам заполнит матрицу через генератор.
    ReplaceMultiplesTask firstTask(rows, columns, *generator);

    // Сохраняем КОПИЮ исходной матрицы до изменений.
    const Matrix<int> originalMatrix = firstTask.getMatrix();

    // Второй объект работает с копией исходной матрицы, а не с результатом первого.
    RemoveRowsTask secondTask(originalMatrix, *generator);

    std::cout << "\n=== Задание 1. Кратные трём заменить нулями ===\n";
    std::cout << "Исходная матрица:\n" << originalMatrix << "\n";
    firstTask.solve();
    std::cout << "Результат:\n" << firstTask.getMatrix() << "\n";

    std::cout << "\n=== Задание 2. Удалить строки со вторым элементом больше предпоследнего ===\n";
    std::cout << "Исходная матрица:\n" << secondTask.getMatrix() << "\n";
    secondTask.solve();
    std::cout << "Результат:\n" << secondTask.getMatrix() << "\n";

    return 0;
}
