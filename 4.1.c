#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define scanf_s scanf

/**
 * @brief Получение целочисленного значения от пользователя
 * @return Введенное значение
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
 * @param size Размер массива
 */
void fillArray(int* arr,const size_t size);

/**
 * @brief Заполнение массива случайными числами в диапазоне [-10;10]
 * @param arr Указатель на массив
 * @param size Размер массива
 */
void fillRandom(int* arr,const size_t size);

/**
 * @brief Вывод массива на экран
 * @param arr Указатель на массив
 * @param size Размер массива
 */
void printArray(const int* arr,const size_t size);

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
int CountPositiveA(const int* arr,const size_t size,const int A);

/**
 * @brief Поиск первой пары соседних элементов с суммой меньше заданного числа
 * @param arr Указатель на массив
 * @param size Размер массива
 * @param target Заданное число
 * @return Индекс первого элемента пары или -1 если пара не найдена
 */
int FirstPairSum(const int* arr,const size_t size,const int target);

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
    size_t size = getSize("Enter the size of the array:");
    int* arr = malloc(size * sizeof(int));
    if (arr == NULL)
    {
        printf("Error!");
        exit(1);
    }
    printf("Choose a way to fill in the array:\n"
           "%d - random numbers [-10;10], %d - manually:", RANDOM, MANUAL);
    int choice = Value();
    switch(choice)
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
    
    printf("\n1. Replacing the second element with the maximum one among the negative ones:\n");
    SecondMaxNegative(arr, size);
    printf("Array after replacement: ");
    printArray(arr, size);
    
    printf("\n2. Enter the number A: ");
    int A = Value();
    int count = CountPositiveA(arr, size, A);
    printf("The number of positive elements not exceeding %d in absolute value %d\n", A, count);
    
    printf("\n3. Enter a number to compare with the sum of the pair: ");
    int target = Value();
    int pairIndex = FirstPairSum(arr, size, target);
    if (pairIndex != -1)
    {
        printf("The first pair of neighboring elements with a sum less than is found %d\n", target);
        printf("Index of the first element of the pair: %d\n", pairIndex);
    }
    else
    {
        printf("No pairs of neighboring elements with a sum less than were found. %d\n", target);
    }
    free(arr);
    return 0;
}

int Value()
{
    int value = 0;
    if (!scanf_s("%d", &value))
    {
        fprintf(stderr,"Error!\n");
        exit(1);
    }
    return value;
}

size_t getSize(char* message)
{
    printf("%s",message);
    int value = Value();
    if (value <= 0)
    {
        fprintf(stderr, "Ошибка!\n");
        exit(1);
    }
    return value;
}

void fillArray(int* arr,const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("Enter the element:");
        arr[i] = Value();
    }
}

void fillRandom(int* arr,const size_t size)
{
    srand(time(NULL));
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = (rand() % 21) - 10;
    }
}

void printArray(const int* arr,const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void SecondMaxNegative(int* arr, const size_t size)
{
    if (size < 2)
    {
        printf("The array is too small to replace the second element!\n");
        return;
    }
    
    int max_negative = -11;
    int found = 0;
    
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] < 0)
        {
            if (found == 0 || arr[i] > max_negative)
            {
                max_negative = arr[i];
                found = 1;
            }
        }
    }
    
    if (found == 1)
    {
        printf("Maximum negative element: %d\n", max_negative);
        arr[1] = max_negative;
    }
    else
    {
        printf("There are no negative elements in the array.\n");
    }
}

int CountPositiveA(const int* arr,const size_t size,const int A)
{
    int count = 0;
    
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] > 0)
        {
            if (arr[i] <= A && arr[i] >= -A)
            {
                count++;
            }
        }
    }
    
    return count;
}

int FirstPairSum(const int* arr,const size_t size,const int target)
{
    if (size < 2)
    {
        printf("The array is too small to search for pairs!\n");
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