#pragma once
#include <iostream>
#include <string>

/**
 * @brief Класс Полное имя
 */
class FullName
{
private:
    /**
     * @brief Фамилия
     */
    std::string surname;

    /**
     * @brief Имя
     */
    std::string name;

    /**
     * @brief Отчество
     */
    std::string patronymic;

public:
    /**
     * @brief Конструктор полного имени
     * @param surname Фамилия
     * @param name Имя
     * @param patronymic Отчество
     */
    FullName(const std::string& surname = "", const std::string& name = "", const std::string& patronymic = "");

    /**
     * @brief Получение фамилии
     * @return фамилия
     */
    std::string getSurname() const;

    /**
     * @brief Получение имени
     * @return имя
     */
    std::string getName() const;

    /**
     * @brief Получение отчества
     * @return отчество
     */
    std::string getPatronymic() const;

    /**
     * @brief Оператор вывода полного имени
     * @param os поток вывода
     * @param fullName объект FullName
     * @return поток вывода
     */
    friend std::ostream& operator<<(std::ostream& os, const FullName& fullName);

    /**
     * @brief Оператор ввода полного имени
     * @param is поток ввода
     * @param fullName объект FullName
     * @return поток ввода
     */
    friend std::istream& operator>>(std::istream& is, FullName& fullName);

    /**
     * @brief Сериализация в строку
     * @return строковое представление ФИО
     */
    std::string toString() const;
};