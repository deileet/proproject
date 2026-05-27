#include <iostream>
#include <string>
#include "PriorityQueue.h"

using namespace std;

enum Actions
{
    EXIT = 0,
    INSERT = 1,
    GET_MAX,
    GET_MIN,
    REMOVE_MAX,
    SHOW_QUEUE
};

void ERROR(const string text)
{
    cerr << text << endl;
    exit(1);
}

int get_choice()
{
    int number = 0;
    cin >> number;
    if (cin.fail())
    {
        ERROR("Ошибка ввода");
    }
    return number;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    
    PriorityQueue queue;
    
    cout << "Укажите начальное количество элементов очереди: ";
    int n = get_choice();
    
    if (n < 0)
    {
        ERROR("Ошибка: количество элементов не может быть отрицательным.");
    }
    
    if (n > 0)
    {
        cout << "Введите " << n << " элементов очереди: " << endl;
        for (int i = 0; i < n; ++i)
        {
            int val = get_choice();
            queue.insert(val);
        }
    }
    
    cout << "Изначальная очередь: " << queue << endl;
    
    bool running = true;
    while (running)
    {
        cout << "\nВыберите действие: " << endl
             << INSERT << " - Вставить элемент" << endl
             << GET_MAX << " - Получить максимальный" << endl
             << GET_MIN << " - Получить минимальный" << endl
             << REMOVE_MAX << " - Удалить максимальный" << endl
             << SHOW_QUEUE << " - Показать очередь" << endl
             << EXIT << " - Выход" << endl;
        cout << "Ваш выбор: ";
        
        int choice = get_choice();
        
        try
        {
            switch (choice)
            {
                case INSERT:
                {
                    cout << "Введите значение: ";
                    int val = get_choice();
                    queue.insert(val);
                    cout << "После добавления: " << queue.to_string() << endl;
                    break;
                }
                case GET_MAX:
                    cout << "Максимум: " << queue.get_max() << endl;
                    break;
                case GET_MIN:
                    cout << "Минимум: " << queue.get_min() << endl;
                    break;
                case REMOVE_MAX:
                    queue.remove_max();
                    cout << "После удаления: " << queue.to_string() << endl;
                    break;
                case SHOW_QUEUE:
                    cout << "Очередь: " << queue.to_string() << endl;
                    break;
                case EXIT:
                    running = false;
                    break;
                default:
                    ERROR("Неверный выбор!");
            }
        }
        catch (const exception& e)
        {
            cout << "Ошибка: " << e.what() << endl;
        }
    }
    
    if (!queue.is_empty())
    {
        cout << "\n=== Демонстрация операторов ===" << endl;
        queue << 100;
        cout << "После << 100: " << queue << endl;
        
        int extracted = 0;
        queue >> extracted;
        cout << "Извлечено: " << extracted << endl;
        cout << "Итог: " << queue << endl;
    }
    
    return 0;
}