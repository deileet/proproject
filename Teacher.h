#pragma once
#include "Person.h"
#include <string>

/**
 * @brief Перечислимый тип для должностей преподавателей
 */
enum class Position
{
    Professor,           /** Профессор */
    AssociateProfessor,  /** Доцент */
    SeniorLecturer,      /** Старший преподаватель */
    Assistant            /** Ассистент */
};

/**
 * @brief Класс Преподаватель
 */
class Teacher : public Person
{
private:
    /**
     * @brief Должность преподавателя
     */
    Position position;

    /**
     * @brief Стаж работы (лет)
     */
    uint8_t experience;

public:
    /**
     * @brief Конструктор преподавателя
     * @param fullName Полное имя
     * @param gender Пол
     * @param birthDate Дата рождения
     * @param position Должность
     * @param experience Стаж работы
     */
    Teacher(const FullName& fullName = FullName(), 
            Gender gender = Gender::Male, 
            const Date& birthDate = Date(),
            Position position = Position::Assistant, 
            uint8_t experience = 0);

    /**
     * @brief Получение должности
     * @return должность
     */
    Position getPosition() const;

    /**
     * @brief Получение стажа
     * @return стаж работы
     */
    uint8_t getExperience() const;

    /**
     * @brief Сериализация в строку
     * @return строковое представление преподавателя
     */
    std::string toString() const override;

    /**
     * @brief Оператор вывода преподавателя
     * @param os поток вывода
     * @param teacher объект Teacher
     * @return поток вывода
     */
    friend std::ostream& operator<<(std::ostream& os, const Teacher& teacher);

    /**
     * @brief Оператор ввода преподавателя
     * @param is поток ввода
     * @param teacher объект Teacher
     * @return поток ввода
     */
    friend std::istream& operator>>(std::istream& is, Teacher& teacher);
};