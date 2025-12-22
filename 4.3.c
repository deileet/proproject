#include <stdio.h>
#include <stdlib.h>
#define scanf_s scanf

/**
 * @brief Проверяет указатель на NULL и завершает программу при обнаружении
 * @param ptr Указатель для проверки
 */
void checkPointer(const void* ptr);

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
size_t getSize(const char* message);    

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
 * @brief Проверяет корректность диапазона случайных чисел
 * @param start Начало диапазона
 * @param end Конец диапазона
 */
void checkRange(const int start, const int end);

/**
 * @brief Создаёт копию массива
 * @param arr Исходный массив
 * @param rows Количество строк массива
 * @param columns Количество столбцов массива
 * @return Полученный массив
 */
int** copyArray(int** arr, const size_t rows, const size_t columns);

/**
 * @brief Заменяет четный элемент каждого столбца максимальным по модулю
 * @param arr Массив
 * @param rows Количество строк массива
 * @param columns Количество столбцов массива
 */
void replaceEvenWithMaxAbs(int** arr, const size_t rows, const size_t columns);

/**
 * @brief Определяет, какие столбцы нужно удалить
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
enum {RANDOM = 1, MANUAL};

/**
 * @brief Точка входа в программу
 * @return 0, если программа выполнена корректно
 */
int main(void)
{
    size_t rows = getSize("Enter the number of rows in the array: ");
    size_t columns = getSize("Enter the number of columns in the array: ");
    int** arr = getArray(rows, columns);
    
    printf("Choose a way to fill in the array:\n"
           "%d - random numbers\n"
           "%d - manually\n"
           "Enter the required filling number: ",
           RANDOM, MANUAL);
    
    const int choice = Value();
    switch (choice)
    {
        case RANDOM:
            fillRandom(arr, rows, columns);
            break;
        case MANUAL:
            fillArray(arr, rows, columns);
            break;
        default:
            fprintf(stderr, "Error!\n");
            freeArray(arr, rows);
            exit(1);
    }
    
    printf("The original array:\n");
    printArray(arr, rows, columns);
    
    // 1. Замена четных элементов максимальными по модулю
    int** copyArr1 = copyArray(arr, rows, columns);
    replaceEvenWithMaxAbs(copyArr1, rows, columns);
    printf("Array after replacing even elements with maximum absolute values:\n");
    printArray(copyArr1, rows, columns);
    freeArray(copyArr1, rows);
    
    // 2. Удаление столбцов с четным первым элементом
    size_t newCols = columns - columnsToDelete(arr, rows, columns);
    
    if (newCols == 0)
    {
        printf("All columns have an even first element! Nothing to display.\n");
    }
    else
    {
        int** copyArr2 = getArray(rows, newCols);
        deleteColumns(arr, copyArr2, rows, columns, newCols);
        printf("Array after deleting columns with even first element:\n");
        printArray(copyArr2, rows, newCols);
        freeArray(copyArr2, rows);
    }
    
    freeArray(arr, rows);
    return 0;
}

void checkPointer(const void* ptr)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "Error!\n");
        exit(1);
    }
}

int Value()
{
    int value = 0;
    if (!scanf_s("%d", &value))
    {
        fprintf(stderr, "Error!\n");
        exit(1);
    }
    return value;
}

size_t getSize(const char* message)
{
    checkPointer(message);
    
    printf("%s", message);
    int value = Value();
    
    if (value <= 0)
    {
        fprintf(stderr, "Error!");
        exit(1);
    }
    
    return (size_t)value;
}

void fillArray(int** arr, const size_t rows, const size_t columns)
{
    checkPointer(arr);
    
    for (size_t i = 0; i < rows; i++)
    {
        checkPointer(arr[i]);
        
        for (size_t j = 0; j < columns; j++)
        {
            printf("Enter a[%zu,%zu] = ", i, j);
            arr[i][j] = Value();
        }
    }
}

void printArray(int** arr, const size_t rows, const size_t columns)
{
    checkPointer(arr);
    
    for (size_t i = 0; i < rows; i++)
    {
        checkPointer(arr[i]);
        
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
    checkPointer(arr);
    
    printf("Enter the beginning of the range of random numbers: ");
    int start = Value();
    printf("Enter the end of the range of random numbers: ");
    int end = Value();
    
    checkRange(start, end);
    
    for (size_t i = 0; i < rows; i++)
    {
        checkPointer(arr[i]);
        
        for (size_t j = 0; j < columns; j++)
        {
            arr[i][j] = (rand() % (end - start + 1)) + start;
        }
    }
}

int** getArray(const size_t rows, const size_t columns)
{
    int** arr = malloc(rows * sizeof(int*));
    if (arr == NULL)
    {
        printf("Error!\n");
        exit(1);
    }
    
    for (size_t i = 0; i < rows; i++)
    {
        arr[i] = malloc(columns * sizeof(int));
        if (arr[i] == NULL)
        {
            printf("Error!\n");
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
    if (arr == NULL)
    {
        return;
    }
    
    for (size_t i = 0; i < rows; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

void checkRange(const int start, const int end)
{
    if (start > end)
    {
        printf("Error!\n");
        exit(1);
    }
}

int** copyArray(int** arr, const size_t rows, const size_t columns)
{
    checkPointer(arr);
    
    int** copyArr = getArray(rows, columns);
    
    for (size_t i = 0; i < rows; i++)
    {
        checkPointer(arr[i]);
        
        for (size_t j = 0; j < columns; j++)
        {
            copyArr[i][j] = arr[i][j];
        }
    }
    
    return copyArr;
}

void replaceEvenWithMaxAbs(int** arr, const size_t rows, const size_t columns)
{
    checkPointer(arr);
    
    for (size_t j = 0; j < columns; j++)
    {
        
        int maxAbsValue = arr[0][j];
        int maxAbs = abs(arr[0][j]);
        
        for (size_t i = 1; i < rows; i++)
        {
            int currentAbs = abs(arr[i][j]);
            if (currentAbs > maxAbs)
            {
                maxAbs = currentAbs;
                maxAbsValue = arr[i][j];
            }
        }
        
    
        int replaced = 0;
        for (size_t i = 0; i < rows && !replaced; i++)
        {
            if (arr[i][j] % 2 == 0)
            {
                arr[i][j] = maxAbsValue;
                replaced = 1;
            }
        }
    }
}

size_t columnsToDelete(int** arr, const size_t rows, const size_t columns)
{
    checkPointer(arr);
    
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
    checkPointer(arr);
    checkPointer(newArr);
    
    size_t k = 0;
    for (size_t j = 0; j < columns; j++)
    {
        if (arr[0][j] % 2 != 0)
        {
            for (size_t i = 0; i < rows; i++)
            {
                newArr[i][k] = arr[i][j];
            }
            k++;
        }
    }
}
