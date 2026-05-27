#pragma once
#include <iostream>
#include <string>
#include <cstdint>

/**
 * @brief Перечислимый тип для месяцев
 */
enum class Month
{
    January = 1,
    February = 2,
    March = 3,
    April = 4,
    May = 5,
    June = 6,
    July = 7,
    August = 8,
    September = 9,
    October = 10,
    November = 11,
    December = 12
};

/**
 * @brief Класс Дата
 */
class Date
{
private:
    /**
     * @brief День месяца
     */
    uint8_t day;

    /**
     * @brief Месяц
     */
    Month month;

    /**
     * @brief Год
     */
    uint16_t year;

public:
    /**
     * @brief Конструктор даты
     * @param day день (1-31)
     * @param month месяц (1-12)
     * @param year год
     */
    Date(uint8_t day = 1, uint8_t month = 1, uint16_t year = 2000);

    /**
     * @brief Получение дня
     * @return день
     */
    uint8_t getDay() const;

    /**
     * @brief Получение месяца
     * @return месяц
     */
    Month getMonth() const;

    /**
     * @brief Получение года
     * @return год
     */
    uint16_t getYear() const;

    /**
     * @brief Оператор вывода даты
     * @param os поток вывода
     * @param date объект Date
     * @return поток вывода
     */
    friend std::ostream& operator<<(std::ostream& os, const Date& date);

    /**
     * @brief Оператор ввода даты
     * @param is поток ввода
     * @param date объект Date
     * @return поток ввода
     */
    friend std::istream& operator>>(std::istream& is, Date& date);

    /**
     * @brief Сериализация в строку
     * @return строковое представление даты
     */
    std::string toString() const;
};