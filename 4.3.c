
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#define scanf_s scanf
 
/**
 * @brief Считывает значение, введенное с клавиатуры с проверкой ввода
 * @return Считанное значение
 */
int Value();
 
/**
 * @brief Получение размера массива
 * @param message сообщение пользователю
 * @return Размер массива
 */
size_t getSize(char* message);
 
/**
 * @brief Заполнение массива с клавиатуры
 * @param arr Указатель на массив
 * @param rows Количество строк массива
 * @param columns Количество столбцов массива
 */
void fillArray(int** arr, const size_t rows, const size_t columns);
 
/**
 * @brief Вывод массива на экран
 * @param arr Массив
 * @param rows Количество строк массива
 * @param columns Количество столбцов массива
 */
void printArray(int** arr, const size_t rows, const size_t columns);
 
/**
 * @brief Заполнение массива случайными числами
 * @param arr Массив
 * @param rows Количество строк массива
 * @param columns Количество столбцов массива
 */
void fillRandom(int** arr, const size_t rows, const size_t columns);
 
/**
 * @brief Создаёт массив по указанным пользователем вводным данным
 * @param rows количество строк массива
 * @param columns количество столбцов массива
 * @return полученный массив
 */
int** getArray(const size_t rows, const size_t columns);
 
/**
 * @brief Освобождает память, выделенную под массив
 * @param arr массив
 * @param rows количество строк массива
 */
void freeArray(int** arr, const size_t rows);
 
/**
 * @brief Создаёт копию массива
 * @param arr Исходный массив
 * @param rows Количество строк массива
 * @param columns Количество столбцов массива
 * @return Полученный массив
 */
int** copyArray(int** arr, const size_t rows, const size_t columns);
 
/**
 * @brief Находит максимальный по модулю элемент в столбце
 * @param arr Массив
 * @param rows Количество строк массива
 * @param column Индекс столбца
 * @return Максимальный по модулю элемент
 */
int findMaxAbsInColumn(int** arr, const size_t rows, const size_t column);
 
/**
 * @brief Заменяет четный элемент каждого столбца максимальным по модулю
 * @param arr Массив
 * @param rows Количество строк массива
 * @param columns Количество столбцов массива
 */
void replaceEvenWithMaxAbs(int** arr, const size_t rows, const size_t columns);
 
/**
 * @brief Определяет, какие столбцы нужно удалить (первый элемент четный)
 * @param arr Массив
 * @param rows Количество строк массива
 * @param columns Количество столбцов массива
 * @return Количество столбцов для удаления
 */
size_t columnsToDelete(int** arr, const size_t rows, const size_t columns);
 
/**
 * @brief Удаляет столбцы, в которых первый элемент четный
 * @param arr Исходный массив
 * @param newArr Новый массив
 * @param rows Количество строк массива
 * @param columns Количество столбцов исходного массива
 * @param newCols Количество столбцов после удаления
 */
void deleteColumns(int** arr, int** newArr, const size_t rows, const size_t columns, const size_t newCols);
 
/**
 * @brief RANDOM - заполнение массива случайными числами
 * @brief MANUAL - заполнение массива вручную.
 */
enum {RANDOM = 1, MANUAL = 2};
 
/**
 * @brief Точка входа в программу
 * @return 0, если программа выполнена корректно
 */
int main()
{
    srand(time(NULL)); 
    size_t rows = getSize("Введите количество строк массива: ");
    size_t columns = getSize("Введите количество столбцов массива: ");
    
    int** arr = getArray(rows, columns);
    
    printf("Выберите способ заполнения массива:\n"
           "%d - случайными числами\n"
           "%d - вручную\n"
           "Введите нужный номер заполнения: ",
           RANDOM, MANUAL);
           
    int choice = Value();
    switch (choice)
    {
        case RANDOM:
            fillRandom(arr, rows, columns);
            break;
        case MANUAL:
            fillArray(arr, rows, columns);
            break;
        default:
            printf("Ошибка!\n");
            freeArray(arr, rows);
            return 1;
    }
    
    printf("\nИсходный массив (%zux%zu):\n", rows, columns);
    printArray(arr, rows, columns);
    

    printf("\n--- Задача 1 ---\n");
    printf("Замена четного элемента каждого столбца максимальным по модулю\n");
    int** modifiedArr = copyArray(arr, rows, columns);
    replaceEvenWithMaxAbs(modifiedArr, rows, columns);
    printf("Массив после замены:\n");
    printArray(modifiedArr, rows, columns);
    

    printf("\n--- Задача 2 ---\n");
    printf("Удаление столбцов, в которых первый элемент четный\n");
    size_t colsToDelete = columnsToDelete(arr, rows, columns);
    size_t newCols = columns - colsToDelete;
    
    if (newCols == 0) {
        printf("Все столбцы имеют четный первый элемент! Невозможно создать массив.\n");
    } else {
        int** reducedArr = getArray(rows, newCols);
        deleteColumns(arr, reducedArr, rows, columns, newCols);
        printf("Массив после удаления столбцов (%zux%zu):\n", rows, newCols);
        printArray(reducedArr, rows, newCols);
        freeArray(reducedArr, rows);
    }
    
    printf("Удалено столбцов: %zu\n", colsToDelete);

    freeArray(modifiedArr, rows);
    freeArray(arr, rows);
    
    return 0;
}
 
int Value()
{
    int value = 0;
    if (!scanf_s("%d", &value))
    {
        printf("Ошибка ввода!\n");
        abort();
    }
    return value;
}
 
size_t getSize(char* message)
{
    printf("%s", message);
    int value = Value();
    if (value <= 0)
    {
        printf("Ошибка: размер должен быть положительным!\n");
        abort();
    }
    return (size_t)value;
}
 
void fillArray(int** arr, const size_t rows, const size_t columns)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            printf("Введите элемент [%zu][%zu]: ", i, j);
            arr[i][j] = Value();
        }
    }
}
 
void printArray(int** arr, const size_t rows, const size_t columns)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            printf("%5d", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
 
void fillRandom(int** arr, const size_t rows, const size_t columns)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            arr[i][j] = (rand() % 201) - 100;
        }
    }
    printf("Массив заполнен случайными числами от -100 до 100\n");
}
 
int** getArray(const size_t rows, const size_t columns)
{
    int** arr = malloc(rows * sizeof(int*));
    if (arr == NULL)
    {
        printf("Ошибка выделения памяти.\n");
        exit(1);
    }
    
    for (size_t i = 0; i < rows; i++)
    {
        arr[i] = malloc(columns * sizeof(int));
        if (arr[i] == NULL)
        {
            printf("Ошибка выделения памяти.\n");
            for (size_t j = 0; j < i; j++)
            {
                free(arr[j]);
            }
            free(arr);
            exit(1);
        }
    }
    
    return arr;
}
 
void freeArray(int** arr, const size_t rows)
{
    for (size_t i = 0; i < rows; i++)
    {
        free(arr[i]);
    }
    free(arr);
}
 
int** copyArray(int** arr, const size_t rows, const size_t columns)
{
    int** copyArr = getArray(rows, columns);
    
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            copyArr[i][j] = arr[i][j];
        }
    }
    
    return copyArr;
}
 
int findMaxAbsInColumn(int** arr, const size_t rows, const size_t column)
{
    int maxAbs = 0;
    int maxValue = arr[0][column];
    
    for (size_t i = 0; i < rows; i++)
    {
        int currentAbs = abs(arr[i][column]);
        if (currentAbs > maxAbs)
        {
            maxAbs = currentAbs;
            maxValue = arr[i][column];
        }
    }
    
    return maxValue;
}
 
void replaceEvenWithMaxAbs(int** arr, const size_t rows, const size_t columns)
{
    for (size_t j = 0; j < columns; j++)
    {
        int maxAbsValue = findMaxAbsInColumn(arr, rows, j);
        int replaced = 0;
    
        for (size_t i = 0; i < rows; i++)
        {
            if (arr[i][j] % 2 == 0)
            {
                printf("Столбец %zu: элемент [%zu][%zu] = %d заменен на %d\n",
                       j, i, j, arr[i][j], maxAbsValue);
                arr[i][j] = maxAbsValue;
                replaced = 1;
                break; 
            }
        }
        
        if (!replaced)
        {
            printf("Столбец %zu: нет четных элементов для замены\n", j);
        }
    }
}
 
size_t columnsToDelete(int** arr, const size_t rows, const size_t columns)
{
    size_t count = 0;
    
    for (size_t j = 0; j < columns; j++)
    {
        if (arr[0][j] % 2 == 0)
        {
            count++;
        }
    }
    
    return count;
}
 
void deleteColumns(int** arr, int** newArr, const size_t rows, const size_t columns, const size_t newCols)
{
    size_t newColIndex = 0;
    
    for (size_t j = 0; j < columns; j++)
    {

        if (arr[0][j] % 2 != 0)
        {
            for (size_t i = 0; i < rows; i++)
            {
                newArr[i][newColIndex] = arr[i][j];
            }
            newColIndex++;
        }
        else
        {
            printf("Столбец %zu удален (первый элемент %d четный)\n", j, arr[0][j]);
        }
    }
}