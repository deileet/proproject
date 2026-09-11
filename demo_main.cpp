#include <clocale>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include "DoublyLinkedList.h"

using namespace chains;

namespace
{
    /**
    *@brief Печатает содержимое списка с подписью.
    *@tparam T Тип данных, хранящихся в списке.
    *@param caption Подпись перед выводом.
    *@param chain Список для вывода.
    */
    template <typename T>
    void printChain(const std::string& caption, const DoublyLinkedList<T>& chain)
    {
        std::cout << caption << ": " << chain << "\n";
    }

    /**
    *@brief Возвращает короткий ответ на вопрос «пуст ли список».
    *@tparam T Тип данных, хранящихся в списке.
    *@param chain Список для проверки.
    *@return «да», если список пуст, иначе «нет».
    */
    template <typename T>
    const char* emptyWord(const DoublyLinkedList<T>& chain)
    {
        return chain.empty() ? "да" : "нет";
    }

    /**
    *@brief Раздел 1: конструктор со списком инициализации и базовые сведения.
    */
    void sectionConstruction()
    {
        std::cout << "--- 1. Создание списка ---\n";

        const DoublyLinkedList<int> chain1 = { 10, 20, 30, 40, 50 };
        printChain("chain1 после инициализации", chain1);
        std::cout << "Элементов в chain1: " << chain1.size() << "\n";
        std::cout << "chain1 пуст? " << emptyWord(chain1) << "\n\n";
    }

    /**
    *@brief Раздел 2: копирование и перемещение списков.
    */
    void sectionCopying()
    {
        std::cout << "--- 2. Копирование и перемещение ---\n";

        const DoublyLinkedList<int> source = { 10, 20, 30, 40, 50 };
        DoublyLinkedList<int> chain2(source);
        printChain("chain2 (копия)            ", chain2);

        DoublyLinkedList<int> chain3(std::move(chain2));
        printChain("chain3 (перемещён)        ", chain3);
        printChain("chain2 (после перемещения)", chain2);
        std::cout << "chain2 теперь содержит: " << chain2.size()
                  << " элементов; пуст? " << emptyWord(chain2) << "\n";

        DoublyLinkedList<int> chain4;
        chain4 = source;
        printChain("chain4 (= source)          ", chain4);

        DoublyLinkedList<int> chain5;
        chain5 = std::move(chain4);
        printChain("chain5 (= move(chain4))     ", chain5);
        printChain("chain4 (после перемещения)", chain4);

        std::cout << "\n";
    }

    /**
    *@brief Раздел 3: добавление элементов.
    */
    void sectionAdding()
    {
        std::cout << "--- 3. Добавление элементов ---\n";

        DoublyLinkedList<int> chain6 = { 1, 2, 3 };
        printChain("начальное состояние", chain6);

        chain6.pushBack(4);
        printChain("после pushBack(4)  ", chain6);

        chain6.pushFront(0);
        printChain("после pushFront(0) ", chain6);

        chain6.insertAt(2, 99);
        printChain("после insertAt(2, 99)", chain6);

        chain6.insertAt(chain6.size(), 5);
        printChain("после insertAt(size(), 5)", chain6);

        std::cout << "\n";
    }

    /**
    *@brief Раздел 4: удаление элементов.
    */
    void sectionDeleting()
    {
        std::cout << "--- 4. Удаление элементов ---\n";

        DoublyLinkedList<int> chain7 = { 0, 1, 99, 2, 3, 4, 5 };
        printChain("исходная цепочка", chain7);

        chain7.popBack();
        printChain("после popBack()    ", chain7);

        chain7.popFront();
        printChain("после popFront()   ", chain7);

        chain7.deleteAt(1);
        printChain("после deleteAt(1)  ", chain7);

        const bool erasedFirst = chain7.removeFirstOf(2);
        std::cout << "Первый найденный 2 удалён? " << (erasedFirst ? "да" : "нет") << "\n";
        printChain("после removeFirstOf(2)", chain7);

        const bool erasedMissing = chain7.removeFirstOf(42);
        std::cout << "Значение 42 найдено и удалено? " << (erasedMissing ? "да" : "нет") << "\n";
        printChain("список не изменился", chain7);

        std::cout << "\n";
    }

    /**
    *@brief Раздел 5: поиск и изменение значений.
    */
    void sectionSearchingAndChanging()
    {
        std::cout << "--- 5. Поиск и изменение ---\n";

        DoublyLinkedList<int> chain8 = { 10, 20, 25, 30, 40, 50 };
        printChain("рабочая цепочка", chain8);

        const int hitIndex = chain8.findIndexOf(30);
        std::cout << "Позиция значения 30: " << hitIndex << "\n";

        const int missIndex = chain8.findIndexOf(777);
        std::cout << "Позиция значения 777: " << missIndex << "\n";

        chain8.assignAt(1, 99);
        printChain("после assignAt(1, 99)", chain8);

        std::cout << "chain8[0] = " << chain8[0] << "\n";
        chain8[0] = 7;
        printChain("после chain8[0] = 7", chain8);

        std::cout << "\n";
    }

    /**
    *@brief Раздел 6: обход списка в прямом и обратном направлении.
    */
    void sectionTraversal()
    {
        std::cout << "--- 6. Обход в обе стороны ---\n";

        const DoublyLinkedList<int> chain9 = { 7, 99, 25, 30, 50 };
        printChain("список", chain9);

        std::cout << "Прямой обход:    [";
        for (std::size_t i = 0; i < chain9.size(); ++i)
        {
            std::cout << chain9[i];
            if (i + 1 < chain9.size())
            {
                std::cout << " <-> ";
            }
        }
        std::cout << "]\n";

        std::cout << "Обратный обход:  [";
        for (std::size_t i = chain9.size(); i > 0; --i)
        {
            std::cout << chain9[i - 1];
            if (i > 1)
            {
                std::cout << " <-> ";
            }
        }
        std::cout << "]\n\n";
    }

    /**
    *@brief Раздел 7: пустой список, полная очистка и защита от ошибок.
    */
    void sectionEmptyAndSafety()
    {
        std::cout << "--- 7. Пустой список, очистка, исключения ---\n";

        DoublyLinkedList<int> blank;
        printChain("blank сразу после создания", blank);
        std::cout << "Размер: " << blank.size() << "; пуст? " << emptyWord(blank) << "\n";

        blank.pushBack(42);
        printChain("после blank.pushBack(42)", blank);

        blank.clearAll();
        printChain("после полной очистки", blank);

        try
        {
            static_cast<void>(blank[0]);
        }
        catch (const std::out_of_range& error)
        {
            std::cout << "Исключение при blank[0]: " << error.what() << "\n";
        }

        try
        {
            blank.popFront();
        }
        catch (const std::out_of_range& error)
        {
            std::cout << "Исключение при popFront(): " << error.what() << "\n";
        }

        try
        {
            blank.insertAt(7, 100);
        }
        catch (const std::out_of_range& error)
        {
            std::cout << "Исключение при insertAt(7, 100): " << error.what() << "\n";
        }

        std::cout << "\n";
    }
}

/**
*@brief Точка входа: последовательно запускает все разделы демонстрации.
*@return 0, если программа выполнена успешно.
*/
int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Демонстрация шаблонного двусвязного списка DoublyLinkedList\n";
    std::cout << "============================================================\n\n";

    sectionConstruction();
    sectionCopying();
    sectionAdding();
    sectionDeleting();
    sectionSearchingAndChanging();
    sectionTraversal();
    sectionEmptyAndSafety();

    std::cout << "Демонстрация отработала без ошибок.\n";
    return EXIT_SUCCESS;
}
