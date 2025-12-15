#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define scanf_s scanf  

/**
 * @brief Считывает значение, введенное с клавиатуры с проверкой ввода
 * @return Считанное значение
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
 * @brief Вывод массива на экран
 * @param arr Указатель на массив
 * @param size Размер массива
 */
void printArray(const int* arr, const size_t size);

/**
 * @brief Заполнение массива случайными числами в диапазоне [-10;10]
 * @param arr Указатель на массив
 * @param size Размер массива
 */
void fillRandom(int* arr, const size_t size);

/**
 * @brief Создаёт копию массива
 * @param arr Исходный массив
 * @param size Размер массива
 * @return Полученный массив
 */
int* copyArray(const int* arr, const size_t size);

/**
 * @brief Заменяет последний положительный элемент массива на второй элемент
 * @param copyArr Массив, в котором выполняется замена
 * @param size Размер массива
 * @return 1, если замена выполнена успешно, иначе 0
 */
int replaceLastPositive(int* copyArr, const size_t size);

/**
 * @brief Проверяет, содержит ли число цифру 1
 * @param num Число для проверки
 * @return 1 - содержит цифру 1, 0 - не содержит
 */
int containsDigitOne(int num);

/**
 * @brief Вставляет максимальное значение перед элементами, содержащими цифру 1
 * @param copyArr Исходный массив
 * @param size Размер массива
 * @return 1, если хотя бы один элемент был изменён, 0 если замены не произошло
 */
int insertMaxBeforeOnes(const int* copyArr, const size_t size);

/**
 * @brief Формирует новый массив M из массива P по правилу
 * @param copyArr Исходный массив P
 * @param size Размер массива
 * @return 1, если массив M успешно сформирован, 0 если не сформирован
 */
int fromPtoM(const int* copyArr, const size_t size);

/**
 * @brief RANDOM - заполнение массива случайными числами
 * @brief MANUAL - заполнение массива вручную.
 */
enum {RANDOM = 1, MANUAL};

/**
 * @brief Точка входа в программу.
 * @return 0, если программа выполнена корректно.
 */
int main(void)
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    
    size_t size = getSize("Введите размер массива: ");
    int* arr = malloc(size * sizeof(int));
    checkPointer(arr);
    
    printf("Выберите способ заполнения массива:\n"
           "%d - случайными числами\n"
           "%d - вручную\n"
           "Введите нужный номер заполнения: ",
           RANDOM, MANUAL);

    int choice = Value();
    switch (choice)
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
    
    int* copyArr = copyArray(arr, size);
    
    printf("\n1. Замена последнего положительного элемента массива на второй элемент:\n");
    if (replaceLastPositive(copyArr, size))
    {
        printArray(copyArr, size);
    }
    
    printf("\n2. Вставка максимального элемента перед элементами, содержащими цифру 1:\n");
    insertMaxBeforeOnes(arr, size);
    
    printf("\n3. Формирование массива M из массива P:\n");
    fromPtoM(arr, size);
    
    free(copyArr);
    free(arr);
    return 0;
}

int Value(void)
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
    return (size_t)value;
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
        printf("Введите элемент: ");
        arr[i] = Value();
        printf("\n");
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
    
    printf("Текущий массив: ");
    for (size_t i = 0; i < size; i++)
    {
        printf("%5d", arr[i]);
    }
    printf("\n");
}

int* copyArray(const int* arr, const size_t size)
{
    checkPointer(arr);
    
    int* copyArr = malloc(size * sizeof(int));
    checkPointer(copyArr);
    
    for (size_t i = 0; i < size; i++)
    {
        copyArr[i] = arr[i];
    }
    return copyArr;
}

int replaceLastPositive(int* copyArr, const size_t size)
{
    checkPointer(copyArr);
    
    if (size < 2)
    {
        printf("Массив слишком мал!\n");
        exit(1);
    }
    
    int lastPositiveIndex = -1;
    for (int i = (int)size - 1; i >= 0; i--)
    {
        if (copyArr[i] > 0)
        {
            lastPositiveIndex = i;
            break;
        }
    }
    
    if (lastPositiveIndex != -1)
    {
        copyArr[lastPositiveIndex] = copyArr[1];
        return 1;
    }
    else
    {
        printf("Положительных элементов нет.\n");
        return 0;
    }
}

int containsDigitOne(int num)
{
    num = abs(num);
    if (num == 0) return 0;
    
    while (num > 0)
    {
        if (num % 10 == 1) return 1;
        num /= 10;
    }
    return 0;
}

int insertMaxBeforeOnes(const int* copyArr, const size_t size)
{
    checkPointer(copyArr);
    
    if (size == 0)
    {
        printf("Массив пуст!\n");
        exit(1);
    }
    
    int maxElement = copyArr[0];
    for (size_t i = 1; i < size; i++)
    {
        if (copyArr[i] > maxElement)
        {
            maxElement = copyArr[i];
        }
    }
    
    printf("Максимальный элемент: %d\n", maxElement);
    
    size_t count = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (containsDigitOne(copyArr[i]))
        {
            count++;
        }
    }
    
    if (count == 0)
    {
        printf("Элементов, содержащих цифру 1, нет.\n");
        exit(1);
    }
    
    size_t newSize = size + count;
    int* newArr = malloc(newSize * sizeof(int));
    checkPointer(newArr);
    
    size_t j = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (containsDigitOne(copyArr[i]))
        {
            newArr[j++] = maxElement;
            newArr[j++] = copyArr[i];
        }
        else
        {
            newArr[j++] = copyArr[i];
        }
    }
    
    printArray(newArr, newSize);
    free(newArr);
    return 1;
}

int fromPtoM(const int* copyArr, const size_t size)
{
    checkPointer(copyArr);
    
    if (size == 0)
    {
        printf("Массив P пуст, нельзя сформировать новый массив!\n");
        exit(1);
    }
    
    int* M = malloc(size * sizeof(int));
    checkPointer(M);
    
    for (size_t i = 0; i < size; i++)
    {
        size_t number = i + 1;
        if (number % 3 == 0)
        {
            M[i] = (int)number * copyArr[i];
        }
        else
        {
            M[i] = -copyArr[i] * (int)(number + 1);
        }
    }
    
    printArray(M, size);
    free(M);
    return 1;
}
