#include <iostream>
#include "LinkedListLib.h"
#include <clocale>

using namespace collections;

int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "=== Демонстрация работы с линейным двусвязным списком ===\n\n";

    std::cout << "1. Конструктор со списком инициализации:\n";
    LinkedList<int> list1 = { 10, 20, 30, 40, 50 };
    std::cout << "list1: " << list1 << "\n";
    std::cout << "Размер: " << list1.getCount() << "\n";
    std::cout << "Пустой? " << (list1.isEmpty() ? "да" : "нет") << "\n\n";

    std::cout << "2. Конструктор копирования:\n";
    LinkedList<int> list2(list1);
    std::cout << "list2 (копия list1): " << list2 << "\n\n";

    std::cout << "3. Конструктор перемещения:\n";
    LinkedList<int> list3(std::move(list2));
    std::cout << "list3 (перемещён из list2): " << list3 << "\n";
    std::cout << "list2 после перемещения: " << list2 << "\n";
    std::cout << "list2 размер: " << list2.getCount() << ", пуст? "
        << (list2.isEmpty() ? "да" : "нет") << "\n\n";

    std::cout << "4. Оператор присваивания:\n";
    LinkedList<int> list4;
    list4 = list1;
    std::cout << "list4 (присвоен list1): " << list4 << "\n\n";

    std::cout << "5. Оператор присваивания перемещением:\n";
    LinkedList<int> list5;
    list5 = std::move(list4);
    std::cout << "list5 (перемещён из list4): " << list5 << "\n";
    std::cout << "list4 после перемещения: " << list4 << "\n\n";

    std::cout << "6. Вставка элементов:\n";
    list1.push_back(60);
    std::cout << "После push_back(60): " << list1 << "\n";

    list1.push_front(5);
    std::cout << "После push_front(5): " << list1 << "\n";

    list1.insert(3, 25);
    std::cout << "После insert(3, 25): " << list1 << "\n\n";

    std::cout << "7. Удаление элементов:\n";
    list1.pop_back();
    std::cout << "После pop_back(): " << list1 << "\n";

    list1.pop_front();
    std::cout << "После pop_front(): " << list1 << "\n";

    list1.erase(2);
    std::cout << "После erase(2): " << list1 << "\n";

    list1.remove(30);
    std::cout << "После remove(30): " << list1 << "\n\n";

    std::cout << "8. Поиск элемента:\n";
    std::cout << "list1: " << list1 << "\n";
    int findVal = 40;
    int idx = list1.indexOf(findVal);
    if (idx != -1) {
        std::cout << "Элемент " << findVal << " найден на позиции " << idx << "\n";
    }
    else {
        std::cout << "Элемент " << findVal << " не найден\n";
    }

    findVal = 100;
    idx = list1.indexOf(findVal);
    if (idx != -1) {
        std::cout << "Элемент " << findVal << " найден на позиции " << idx << "\n";
    }
    else {
        std::cout << "Элемент " << findVal << " не найден\n";
    }
    std::cout << "\n";

    std::cout << "9. Модификация элемента:\n";
    std::cout << "До изменения: " << list1 << "\n";
    list1.setAt(1, 99);
    std::cout << "После setAt(1, 99): " << list1 << "\n\n";

    std::cout << "10. Оператор доступа по индексу:\n";
    std::cout << "list1[0] = " << list1[0] << "\n";
    std::cout << "list1[2] = " << list1[2] << "\n";
    list1[1] = 100;
    std::cout << "После list1[1] = 100: " << list1 << "\n\n";

    std::cout << "11. Итерация по элементам:\n";
    std::cout << "Элементы списка: ";
    for (size_t i = 0; i < list1.getCount(); ++i) {
        std::cout << list1[i];
        if (i < list1.getCount() - 1) std::cout << " <-> ";
    }
    std::cout << "\n\n";

    std::cout << "12. Работа с пустым списком:\n";
    LinkedList<int> emptyList;
    std::cout << "Пустой список: " << emptyList << "\n";
    std::cout << "Размер: " << emptyList.getCount() << "\n";
    std::cout << "Пустой? " << (emptyList.isEmpty() ? "да" : "нет") << "\n";
    emptyList.push_back(42);
    std::cout << "После push_back(42): " << emptyList << "\n";
    std::cout << "Размер: " << emptyList.getCount() << "\n\n";

    std::cout << "13. Демонстрация обратного обхода (особенность двусвязного списка):\n";
    LinkedList<int> demoList = { 1, 2, 3, 4, 5 };
    std::cout << "Список: " << demoList << "\n";
    std::cout << "Обратный обход: [";
    for (int i = static_cast<int>(demoList.getCount()) - 1; i >= 0; --i) {
        std::cout << demoList[i];
        if (i > 0) std::cout << " <-> ";
    }
    std::cout << "]\n\n";

    std::cout << "14. Очистка списка:\n";
    std::cout << "До очистки: " << list5 << "\n";
    list5.clear();
    std::cout << "После clear(): " << list5 << "\n";
    std::cout << "Размер: " << list5.getCount() << "\n\n";

    std::cout << "15. Проверка на исключения:\n";
    LinkedList<int> testList;
    try {
        std::cout << "Попытка получить элемент из пустого списка: ";
        testList[0];
    }
    catch (std::out_of_range& e) {
        std::cout << "Исключение: " << e.what() << "\n";
    }
    try {
        std::cout << "Попытка удалить из пустого списка: ";
        testList.pop_front();
    }
    catch (std::out_of_range& e) {
        std::cout << "Исключение: " << e.what() << "\n";
    }
    try {
        std::cout << "Попытка вставить по неверному индексу: ";
        testList.insert(5, 10);
    }
    catch (std::out_of_range& e) {
        std::cout << "Исключение: " << e.what() << "\n";
    }

    std::cout << "\nПрограмма завершена успешно.\n";
    return 0;
}
