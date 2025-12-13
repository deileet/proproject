#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
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
size_t getSize(char* message);

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
 * @brief Вставляет элемент со значением K перед всеми элементами, в записи которых есть цифра 1
 * @param copyArr Исходный массив
 * @param size Размер массива
 * @return 1, если хотя бы один элемент был изменён, 0 если замены не произошло
 */
int insertK(const int* copyArr, const size_t size);

/**
 * @brief Формирует новый массив M той же длины, что и P по правилу
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
    srand(time(NULL));
    size_t size = getSize("Enter the size of the array: ");
    int* arr = malloc(size * sizeof(int));
    if (arr == NULL)
    {
        printf("Error!\n");
        exit(1);
    }
    printf("Choose a way to fill in the array:\n"
           "%d - random numbers [-10;10]\n"
           "%d - manually\n"
           "Enter the required filling number: ",
           RANDOM, MANUAL);

    int choice = Value();
    switch (choice)
    {
        case RANDOM:
            fillRandom(arr, size);
            break;
        case MANUAL:
            fillArray(arr, size);
            break;
        default:
            printf("Error!\n");
            free(arr);
            exit(1);
    }
    printf("The original array: ");
    printArray(arr, size);
    
    int* copyArr = copyArray(arr, size);
    printf("\n1. Replacing the last positive element with the second element:\n");
    if (replaceLastPositive(copyArr, size))
    {
        printArray(copyArr, size);
    }
    
    printf("\n2. Inserting the maximum element before the elements with the number 1:\n");
    insertK(arr, size);
    
    printf("\n3. Forming an array M from an array P:\n");
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
        fprintf(stderr, "Error, incorrect value entered!\n");
        exit(1);       
    }
    return value;
}

size_t getSize(char* message)
{
    printf("%s", message);
    int value = Value();
    if (value <= 0)
    {
        fprintf(stderr, "Error");
        exit(1);
    }
    return (size_t)value;
}

void fillArray(int* arr, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("Enter a number: ");
        arr[i] = Value();
        printf("\n");
    }
}

void printArray(const int* arr, const size_t size)
{
    printf("Current array: ");
    for (size_t i = 0; i < size; i++)
    {
        printf("%5d", arr[i]);
    }
    printf("\n");
}

void fillRandom(int* arr, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = (rand() % 21) - 10;
    }
}

int* copyArray(const int* arr, const size_t size)
{
    int* copyArr = malloc(sizeof(int) * size);
    if (copyArr == NULL)
    {
        fprintf(stderr, "Error!\n");
        exit(1);
    }
    for (size_t i = 0; i < size; i++)
    {
        copyArr[i] = arr[i];
    }
    return copyArr;
}

int replaceLastPositive(int* copyArr, const size_t size)
{
    if (size < 2)
    {
        printf("The array is too small!\n");
        exit(1);
    }
    
    int lastPositiveIndex = -1;
    for (int i = size - 1; i >= 0; i--)
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
        printf("There are no positive elements.\n");
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

int insertK(const int* copyArr, const size_t size)
{
    int maxElement = INT_MIN;
    for (size_t i = 0; i < size; i++)
    {
        if (copyArr[i] > maxElement)
        {
            maxElement = copyArr[i];
        }
    }
    
    printf("Maximum element: %d\n", maxElement);
    
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
        fprintf(stderr, "There are no elements with the number 1.\n");
        exit(1);
    }
    
    size_t newSize = size + count;
    int* newArr = malloc(newSize * sizeof(int));
    if (newArr == NULL)
    {
        fprintf(stderr, "Error!\n");
        exit(1);
    }
    
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
    if (size == 0)
    {
        fprintf(stderr, "The array P is empty!\n");
        exit(1);
    }
    
    int* M = malloc(size * sizeof(int));
    if (M == NULL)
    {
        fprintf(stderr, "Error!\n");
        exit(1);
    }
    
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