#pragma once
#include "FullName.h"
#include "Date.h"
#include <iostream>
#include <vector>
#include <string>
#include <functional>

/**
 * @brief Перечислимый тип для пола
 */
enum class Gender
{
    Male,
    Female
};

/**
 * @brief Абстрактный базовый класс Персона
 */
class Person
{
protected:
    /**
     * @brief Полное имя персоны
     */
    FullName fullName;

    /**
     * @brief Пол персоны
     */
    Gender gender;

    /**
     * @brief Дата рождения
     */
    Date birthDate;

public:
    /**
     * @brief Конструктор персоны
     * @param fullName Полное имя
     * @param gender Пол
     * @param birthDate Дата рождения
     */
    Person(const FullName& fullName = FullName(), Gender gender = Gender::Male, const Date& birthDate = Date());

    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Person() = default;

    /**
     * @brief Получение полного имени
     * @return полное имя
     */
    FullName getFullName() const;

    /**
     * @brief Получение пола
     * @return пол
     */
    Gender getGender() const;

    /**
     * @brief Получение даты рождения
     * @return дата рождения
     */
    Date getBirthDate() const;

    /**
     * @brief Сериализация в строку
     * @return строковое представление персоны
     */
    virtual std::string toString() const;

    /**
     * @brief Статический метод вывода объектов по выбранному критерию сортировки
     * @param persons вектор персон
     * @param comparator функция сравнения
     * @param os поток вывода
     */
    static void printSorted(const std::vector<Person>& persons, 
                           std::function<bool(const Person&, const Person&)> comparator,
                           std::ostream& os = std::cout);

    /**
     * @brief Оператор вывода персоны
     * @param os поток вывода
     * @param person объект Person
     * @return поток вывода
     */
    friend std::ostream& operator<<(std::ostream& os, const Person& person);

    /**
     * @brief Оператор ввода персоны
     * @param is поток ввода
     * @param person объект Person
     * @return поток ввода
     */
    friend std::istream& operator>>(std::istream& is, Person& person);
};