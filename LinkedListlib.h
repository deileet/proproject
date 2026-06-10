#pragma once
#include <iostream>
#include <string>
#include <initializer_list>
#include <sstream>
#include <stdexcept>
#include "ListNode.h"

namespace collections {
    template<typename T>
    class LinkedList {
    private:
        ListNode<T>* first;
        ListNode<T>* last;
        size_t count;

        void cloneFrom(LinkedList<T>& other) {
            ListNode<T>* current = other.first;
            while (current != nullptr) {
                push_back(current->value);
                current = current->nextNode;
            }
        }

    public:
        LinkedList() : first(nullptr), last(nullptr), count(0) {}

        LinkedList(std::initializer_list<T> init)
            : first(nullptr), last(nullptr), count(0) {
            for (auto& val : init) {
                push_back(val);
            }
        }

        LinkedList(LinkedList<T>& other)
            : first(nullptr), last(nullptr), count(0) {
            cloneFrom(other);
        }

        LinkedList(LinkedList<T>&& other) noexcept
            : first(other.first), last(other.last), count(other.count) {
            other.first = nullptr;
            other.last = nullptr;
            other.count = 0;
        }

        ~LinkedList() {
            clear();
        }

        LinkedList<T>& operator=(LinkedList<T>& other) {
            if (this != &other) {
                clear();
                cloneFrom(other);
            }
            return *this;
        }

        LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
            if (this != &other) {
                clear();
                first = other.first;
                last = other.last;
                count = other.count;
                other.first = nullptr;
                other.last = nullptr;
                other.count = 0;
            }
            return *this;
        }

        template<typename U>
        friend std::ostream& operator<<(std::ostream& os, LinkedList<U>& list) {
            os << list.asString();
            return os;
        }

        template<typename U>
        friend std::istream& operator>>(std::istream& is, LinkedList<U>& list) {
            list.clear();
            U val;
            while (is >> val) {
                list.push_back(val);
                if (is.peek() == '\n' || is.peek() == EOF) break;
            }
            return is;
        }

        void push_back(T& val) {
            ListNode<T>* newNode = new ListNode<T>(val);
            if (first == nullptr) {
                first = last = newNode;
            }
            else {
                last->nextNode = newNode;
                newNode->prevNode = last;
                last = newNode;
            }
            ++count;
        }

        void push_front(T& val) {
            ListNode<T>* newNode = new ListNode<T>(val);
            if (first == nullptr) {
                first = last = newNode;
            }
            else {
                newNode->nextNode = first;
                first->prevNode = newNode;
                first = newNode;
            }
            ++count;
        }

        void insert(size_t index, T& val) {
            if (index > count) {
                throw std::out_of_range("Индекс выходит за пределы списка");
            }

            if (index == 0) {
                push_front(val);
                return;
            }
            if (index == count) {
                push_back(val);
                return;
            }

            ListNode<T>* current = first;
            for (size_t i = 0; i < index; ++i) {
                current = current->nextNode;
            }

            ListNode<T>* newNode = new ListNode<T>(val);
            newNode->nextNode = current;
            newNode->prevNode = current->prevNode;
            current->prevNode->nextNode = newNode;
            current->prevNode = newNode;
            ++count;
        }

        void pop_back() {
            if (isEmpty()) {
                throw std::out_of_range("Список пуст");
            }

            if (count == 1) {
                delete first;
                first = last = nullptr;
            }
            else {
                ListNode<T>* temp = last;
                last = last->prevNode;
                last->nextNode = nullptr;
                delete temp;
            }
            --count;
        }

        void pop_front() {
            if (isEmpty()) {
                throw std::out_of_range("Список пуст");
            }

            if (count == 1) {
                delete first;
                first = last = nullptr;
            }
            else {
                ListNode<T>* temp = first;
                first = first->nextNode;
                first->prevNode = nullptr;
                delete temp;
            }
            --count;
        }

        void erase(size_t index) {
            if (index >= count) {
                throw std::out_of_range("Индекс выходит за пределы списка");
            }

            if (index == 0) {
                pop_front();
                return;
            }
            if (index == count - 1) {
                pop_back();
                return;
            }

            ListNode<T>* current = first;
            for (size_t i = 0; i < index; ++i) {
                current = current->nextNode;
            }

            current->prevNode->nextNode = current->nextNode;
            current->nextNode->prevNode = current->prevNode;
            delete current;
            --count;
        }

        bool remove(T& val) {
            int idx = indexOf(val);
            if (idx != -1) {
                erase(idx);
                return true;
            }
            return false;
        }

        int indexOf(T& val) {
            ListNode<T>* current = first;
            size_t idx = 0;
            while (current != nullptr) {
                if (current->value == val) {
                    return static_cast<int>(idx);
                }
                current = current->nextNode;
                ++idx;
            }
            return -1;
        }

        void setAt(size_t index, T& val) {
            if (index >= count) {
                throw std::out_of_range("Индекс выходит за пределы списка");
            }

            ListNode<T>* current = first;
            for (size_t i = 0; i < index; ++i) {
                current = current->nextNode;
            }
            current->value = val;
        }

        T& operator[](size_t index) {
            if (index >= count) {
                throw std::out_of_range("Индекс выходит за пределы списка");
            }

            ListNode<T>* current = first;
            for (size_t i = 0; i < index; ++i) {
                current = current->nextNode;
            }
            return current->value;
        }

        size_t getCount() {
            return count;
        }

        bool isEmpty() {
            return count == 0;
        }

        void clear() {
            ListNode<T>* current = first;
            while (current != nullptr) {
                ListNode<T>* temp = current;
                current = current->nextNode;
                delete temp;
            }
            first = last = nullptr;
            count = 0;
        }

        std::string asString() {
            std::stringstream ss;
            ss << "[";
            ListNode<T>* current = first;
            while (current != nullptr) {
                ss << current->value;
                if (current->nextNode != nullptr) {
                    ss << " <-> ";
                }
                current = current->nextNode;
            }
            ss << "]";
            return ss.str();
        }

        ListNode<T>* getFirst() {
            return first;
        }
    };
}
