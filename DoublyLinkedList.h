#pragma once

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

namespace chains
{
    /**
    *@brief Класс линейного двусвязного списка.
    *@tparam T Тип данных, хранящихся в списке.
    */
    template <typename T>
    class DoublyLinkedList
    {
    private:
        /**
        *@brief Один элемент цепочки: данные и две связи.
        */
        struct Element
        {
            /**
            *@brief Значение, хранящееся в элементе.
            */
            T payload;
            /**
            *@brief Указатель на предыдущий элемент.
            */
            Element* previous;
            /**
            *@brief Указатель на следующий элемент.
            */
            Element* next;

            /**
            *@brief Конструктор элемента.
            *@param value Значение для хранения в элементе.
            */
            explicit Element(const T& value)
                : payload(value), previous(nullptr), next(nullptr) {}
        };

        /**
        *@brief Указатель на первый элемент.
        */
        Element* headNode;
        /**
        *@brief Указатель на последний элемент.
        */
        Element* tailNode;
        /**
        *@brief Количество элементов в списке.
        */
        std::size_t nodeCount;

        /**
        *@brief Находит элемент по позиции (неконстантная версия).
        *@param position Позиция элемента.
        *@return Указатель на найденный элемент.
        */
        Element* locate(std::size_t position)
        {
            return const_cast<Element*>(
                static_cast<const DoublyLinkedList<T>*>(this)->locate(position));
        }

        /**
        *@brief Находит элемент по позиции (константная версия).
        *@param position Позиция элемента.
        *@return Константный указатель на найденный элемент.
        */
        const Element* locate(std::size_t position) const
        {
            if (position >= nodeCount)
            {
                throw std::out_of_range("Индекс выходит за пределы списка");
            }

            const Element* cursor = headNode;
            for (std::size_t step = 0; step < position; ++step)
            {
                cursor = cursor->next;
            }
            return cursor;
        }

    public:
        /**
        *@brief Конструктор по умолчанию: пустая цепочка.
        */
        DoublyLinkedList() : headNode(nullptr), tailNode(nullptr), nodeCount(0) {}

        /**
        *@brief Конструктор от списка инициализации.
        *@param values Список инициализации.
        */
        DoublyLinkedList(const std::initializer_list<T> values) : DoublyLinkedList()
        {
            for (const T& value : values)
            {
                pushBack(value);
            }
        }

        /**
        *@brief Конструктор копирования.
        *@param other Другой список.
        */
        DoublyLinkedList(const DoublyLinkedList& other) : DoublyLinkedList()
        {
            for (const Element* cursor = other.headNode; cursor != nullptr; cursor = cursor->next)
            {
                pushBack(cursor->payload);
            }
        }

        /**
        *@brief Конструктор перемещения.
        *@param other Другой список.
        */
        DoublyLinkedList(DoublyLinkedList&& other) noexcept
            : headNode(other.headNode), tailNode(other.tailNode), nodeCount(other.nodeCount)
        {
            other.headNode = nullptr;
            other.tailNode = nullptr;
            other.nodeCount = 0;
        }

        /**
        *@brief Деструктор.
        */
        ~DoublyLinkedList()
        {
            clearAll();
        }

        /**
        *@brief Оператор присваивания копированием.
        *@param other Другой список.
        *@return Ссылка на текущий объект.
        */
        DoublyLinkedList& operator=(const DoublyLinkedList& other)
        {
            if (this != &other)
            {
                clearAll();
                for (const Element* cursor = other.headNode; cursor != nullptr; cursor = cursor->next)
                {
                    pushBack(cursor->payload);
                }
            }
            return *this;
        }

        /**
        *@brief Оператор присваивания перемещением.
        *@param other Другой список.
        *@return Ссылка на текущий объект.
        */
        DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept
        {
            if (this != &other)
            {
                clearAll();
                headNode = other.headNode;
                tailNode = other.tailNode;
                nodeCount = other.nodeCount;
                other.headNode = nullptr;
                other.tailNode = nullptr;
                other.nodeCount = 0;
            }
            return *this;
        }

        /**
        *@brief Оператор вывода содержимого в поток.
        *@param output Поток вывода.
        *@param chain Список для вывода.
        *@return Ссылка на поток вывода.
        */
        template <typename U>
        friend std::ostream& operator<<(std::ostream& output, const DoublyLinkedList<U>& chain);

        /**
        *@brief Оператор чтения значений из потока.
        *@param input Поток ввода.
        *@param chain Список для заполнения.
        *@return Ссылка на поток ввода.
        */
        template <typename U>
        friend std::istream& operator>>(std::istream& input, DoublyLinkedList<U>& chain);

        /**
        *@brief Добавляет элемент в конец списка.
        *@param value Значение элемента.
        */
        void pushBack(const T& value)
        {
            Element* fresh = new Element(value);

            if (tailNode == nullptr)
            {
                headNode = fresh;
                tailNode = fresh;
            }
            else
            {
                tailNode->next = fresh;
                fresh->previous = tailNode;
                tailNode = fresh;
            }
            ++nodeCount;
        }

        /**
        *@brief Добавляет элемент в начало списка.
        *@param value Значение элемента.
        */
        void pushFront(const T& value)
        {
            Element* fresh = new Element(value);

            if (headNode == nullptr)
            {
                headNode = fresh;
                tailNode = fresh;
            }
            else
            {
                fresh->next = headNode;
                headNode->previous = fresh;
                headNode = fresh;
            }
            ++nodeCount;
        }

        /**
        *@brief Вставляет элемент на позицию position.
        *@param position Позиция для вставки.
        *@param value Значение элемента.
        */
        void insertAt(const std::size_t position, const T& value)
        {
            if (position > nodeCount)
            {
                throw std::out_of_range("Индекс выходит за пределы списка");
            }

            if (position == 0)
            {
                pushFront(value);
                return;
            }

            if (position == nodeCount)
            {
                pushBack(value);
                return;
            }

            Element* anchor = locate(position);
            Element* fresh = new Element(value);

            fresh->previous = anchor->previous;
            fresh->next = anchor;
            anchor->previous->next = fresh;
            anchor->previous = fresh;
            ++nodeCount;
        }

        /**
        *@brief Удаляет последний элемент.
        */
        void popBack()
        {
            if (nodeCount == 0)
            {
                throw std::out_of_range("Список пуст");
            }

            Element* doomed = tailNode;
            if (nodeCount == 1)
            {
                headNode = nullptr;
                tailNode = nullptr;
            }
            else
            {
                tailNode = tailNode->previous;
                tailNode->next = nullptr;
            }

            delete doomed;
            --nodeCount;
        }

        /**
        *@brief Удаляет первый элемент.
        */
        void popFront()
        {
            if (nodeCount == 0)
            {
                throw std::out_of_range("Список пуст");
            }

            Element* doomed = headNode;
            if (nodeCount == 1)
            {
                headNode = nullptr;
                tailNode = nullptr;
            }
            else
            {
                headNode = headNode->next;
                headNode->previous = nullptr;
            }

            delete doomed;
            --nodeCount;
        }

        /**
        *@brief Удаляет элемент на позиции position.
        *@param position Позиция элемента.
        */
        void deleteAt(const std::size_t position)
        {
            if (nodeCount == 0 || position >= nodeCount)
            {
                throw std::out_of_range("Индекс выходит за пределы списка");
            }

            if (position == 0)
            {
                popFront();
                return;
            }

            if (position == nodeCount - 1)
            {
                popBack();
                return;
            }

            Element* doomed = locate(position);
            doomed->previous->next = doomed->next;
            doomed->next->previous = doomed->previous;
            delete doomed;
            --nodeCount;
        }

        /**
        *@brief Удаляет первое найденное значение.
        *@param value Значение для удаления.
        *@return true, если элемент найден и удалён.
        */
        bool removeFirstOf(const T& value)
        {
            const int position = findIndexOf(value);
            if (position == -1)
            {
                return false;
            }

            deleteAt(static_cast<std::size_t>(position));
            return true;
        }

        /**
        *@brief Ищет позицию элемента по значению.
        *@param value Значение для поиска.
        *@return Позиция элемента или -1, если не найден.
        */
        int findIndexOf(const T& value) const
        {
            std::size_t position = 0;
            for (const Element* cursor = headNode; cursor != nullptr; cursor = cursor->next)
            {
                if (cursor->payload == value)
                {
                    return static_cast<int>(position);
                }
                ++position;
            }
            return -1;
        }

        /**
        *@brief Заменяет значение элемента на позиции.
        *@param position Позиция элемента.
        *@param value Новое значение.
        */
        void assignAt(const std::size_t position, const T& value)
        {
            Element* target = locate(position);
            target->payload = value;
        }

        /**
        *@brief Оператор доступа по индексу (неконстантный).
        *@param position Позиция элемента.
        *@return Ссылка на элемент.
        */
        T& operator[](const std::size_t position)
        {
            return locate(position)->payload;
        }

        /**
        *@brief Оператор доступа по индексу (константный).
        *@param position Позиция элемента.
        *@return Константная ссылка на элемент.
        */
        const T& operator[](const std::size_t position) const
        {
            return locate(position)->payload;
        }

        /**
        *@brief Получает количество элементов в списке.
        *@return Количество элементов.
        */
        std::size_t size() const
        {
            return nodeCount;
        }

        /**
        *@brief Проверяет, пуст ли список.
        *@return true, если список пуст.
        */
        bool empty() const
        {
            return nodeCount == 0;
        }

        /**
        *@brief Удаляет все элементы.
        */
        void clearAll()
        {
            Element* cursor = headNode;
            while (cursor != nullptr)
            {
                Element* nextStep = cursor->next;
                delete cursor;
                cursor = nextStep;
            }

            headNode = nullptr;
            tailNode = nullptr;
            nodeCount = 0;
        }

        /**
        *@brief Формирует строковое представление списка.
        *@return Строка вида [1 <-> 2 <-> 3].
        */
        std::string toText() const
        {
            std::ostringstream buffer;
            buffer << '[';

            const Element* cursor = headNode;
            while (cursor != nullptr)
            {
                buffer << cursor->payload;
                if (cursor->next != nullptr)
                {
                    buffer << " <-> ";
                }
                cursor = cursor->next;
            }

            buffer << ']';
            return buffer.str();
        }
    };

    /**
    *@brief Реализация оператора вывода.
    *@tparam U Тип данных, хранящихся в списке.
    *@param output Поток вывода.
    *@param chain Список для вывода.
    *@return Ссылка на поток вывода.
    */
    template <typename U>
    std::ostream& operator<<(std::ostream& output, const DoublyLinkedList<U>& chain)
    {
        output << chain.toText();
        return output;
    }

    /**
    *@brief Реализация оператора ввода.
    *@tparam U Тип данных, хранящихся в списке.
    *@param input Поток ввода.
    *@param chain Список для заполнения.
    *@return Ссылка на поток ввода.
    */
    template <typename U>
    std::istream& operator>>(std::istream& input, DoublyLinkedList<U>& chain)
    {
        chain.clearAll();

        U value;
        while (input >> value)
        {
            chain.pushBack(value);

            const int lookahead = input.peek();
            if (lookahead == '\n' || lookahead == std::char_traits<char>::eof())
            {
                break;
            }
        }
        return input;
    }
}
