#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define scanf_s scanf

/**
 * @brief Получение целочисленного значения от пользователя
 * @return Введенное значение
 */
int Value(void);

/**
 * @brief Получение размера массива
 * @param message сообщение пользователю
 * @return Размер массива
 */
size_t getSize(const char* message);

/**
 * @brief Проверка указателя на NULL
 * @param ptr Указатель для проверки
 */
void checkPointer(const void* ptr);

/**
 * @brief Заполнение массива с клавиатуры
 * @param arr Указатель на массив
 * @param size Размер массива
 */
void fillArray(int* arr, const size_t size);

/**
 * @brief Заполнение массива случайными числами в диапазоне [-10;10]
 * @param arr Указатель на массив
 * @param size Размер массива
 */
void fillRandom(int* arr, const size_t size);

/**
 * @brief Вывод массива на экран
 * @param arr Указатель на массив
 * @param size Размер массива
 */
void printArray(const int* arr, const size_t size);

/**
 * @brief Замена второго элемента на максимальный среди отрицательных
 * @param arr Указатель на массив
 * @param size Размер массива
 */
void SecondMaxNegative(int* arr, const size_t size);

/**
 * @brief Подсчет положительных элементов, не превосходящих по модулю A
 * @param arr Указатель на массив
 * @param size Размер массива
 * @param A Заданное число
 * @return Количество элементов
 */
int CountPositiveA(const int* arr, const size_t size, const int A);

/**
 * @brief Поиск первой пары соседних элементов с суммой меньше заданного числа
 * @param arr Указатель на массив
 * @param size Размер массива
 * @param target Заданное число
 * @return Индекс первого элемента пары или -1 если пара не найдена
 */
int FirstPairSum(const int* arr, const size_t size, const int target);

/**
 * @brief Создание копии массива
 * @param arr Указатель на исходный массив
 * @param size Размер массива
 * @return Указатель на копию массива
 */
int* createCopy(const int* arr, const size_t size);

/**
 * @brief RANDOM - Заполнение рандомными элементами
 * @brief MANUAL - Заполнение вручную
 */
enum {RANDOM = 1, MANUAL};

/**
 * @brief Точка входа в программу
 * @return Возвращает 0, если программа выполнена корректно, иначе 1
 */
int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    size_t size = getSize("Введите размер массива:");
    int* arr = malloc(size * sizeof(int));
    checkPointer(arr);
    
    printf("Выберите способ заполнения массива:\n"
           "%d - случайными числами, %d - вручную: ", RANDOM, MANUAL);
    int choice = Value();
    switch(choice)
    {
        case RANDOM:
            srand(time(NULL));
            fillRandom(arr, size);
            break;
        case MANUAL:
            fillArray(arr, size);
            break;
        default:
            fprintf(stderr, "Ошибка!\n");
            free(arr);
            exit(1);
    }

    printf("Исходный массив: ");
    printArray(arr, size);
    
    int* arr_copy = createCopy(arr, size);
    checkPointer(arr_copy);
    
    printf("\n1. Замена второго элемента на максимальный среди отрицательных:\n");
    SecondMaxNegative(arr_copy, size);
    printf("Массив после замены: ");
    printArray(arr_copy, size);
    free(arr_copy);
    
    printf("\n2. Введите число A: ");
    const int A = Value();
    const int count = CountPositiveA(arr, size, A);
    printf("Количество положительных элементов, не превосходящих %d по модулю: %d\n", A, count);
    
    printf("\n3. Введите число для сравнения с суммой пары: ");
    const int target = Value();
    const int pairIndex = FirstPairSum(arr, size, target);
    if (pairIndex != -1)
    {
        printf("Первая пара соседних элементов с суммой меньше %d найдена\n", target);
        printf("Индекс первого элемента пары: %d\n", pairIndex);
    }
    else
    {
        printf("Пар соседних элементов с суммой меньше %d не найдено\n", target);
    }
    
    free(arr);
    return 0;
}

int Value()
{
    int value = 0;
    if (!scanf_s("%d", &value))
    {
        fprintf(stderr, "Ошибка!\n");
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
        fprintf(stderr, "Ошибка!\n");
        exit(1);
    }
    return value;
}

void checkPointer(const void* ptr)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "Ошибка!\n");
        exit(1);
    }
}

void fillArray(int* arr, const size_t size)
{
    checkPointer(arr);
    
    for (size_t i = 0; i < size; i++)
    {
        printf("Введите элемент:");
        arr[i] = Value();
    }
}

void fillRandom(int* arr, const size_t size)
{
    checkPointer(arr);
    
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = (rand() % 21) - 10;
    }
}

void printArray(const int* arr, const size_t size)
{
    checkPointer(arr);
    
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* createCopy(const int* arr, const size_t size)
{
    checkPointer(arr);
    
    int* copy = malloc(size * sizeof(int));
    checkPointer(copy);
    
    for (size_t i = 0; i < size; i++)
    {
        copy[i] = arr[i];
    }
    
    return copy;
}

void SecondMaxNegative(int* arr, const size_t size)
{
    checkPointer(arr);
    
    if (size < 2)
    {
        printf("Массив слишком мал для замены второго элемента!\n");
        return;
    }
    
    int max_negative = -50; // введем сравнивание, потом присваиваем,
    int found = 0;
    
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] < 0 && (found == 0 || arr[i] > max_negative))
        {
            max_negative = arr[i];
            found = 1;
        }
    }
    
    if (found == 1)
    {
        printf("Максимальный отрицательный элемент: %d\n", max_negative);
        arr[1] = max_negative;
    }
    else
    {
        printf("В массиве нет отрицательных элементов.\n");
    }
}

int CountPositiveA(const int* arr, const size_t size, const int A)
{
    checkPointer(arr);
    
    int count = 0;
    
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] > 0 && abs(arr[i]) <= A)
        {
            count++;
        }
    }
    
    return count;
}

int FirstPairSum(const int* arr, const size_t size, const int target)
{
    checkPointer(arr);
    
    if (size < 2)
    {
        printf("Массив слишком мал для поиска пар!\n");
        return -1;
    }
    
    for (size_t i = 0; i < size - 1; i++)
    {
        if (arr[i] + arr[i + 1] < target)
        {
            return i;
        }
    }
    
    return -1;
}
