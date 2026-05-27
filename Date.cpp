#include "Date.h"
#include <stdexcept>

Date::Date(uint8_t day, uint8_t month, uint16_t year)
{
    if (day < 1 || day > 31)
    {
        throw std::out_of_range("Day must be between 1 and 31");
    }
    if (month < 1 || month > 12)
    {
        throw std::out_of_range("Month must be between 1 and 12");
    }
    if (year < 1900 || year > 2100)
    {
        throw std::out_of_range("Year must be between 1900 and 2100");
    }
    this->day = day;
    this->month = static_cast<Month>(month);
    this->year = year;
}

uint8_t Date::getDay() const
{
    return day;
}

Month Date::getMonth() const
{
    return month;
}

uint16_t Date::getYear() const
{
    return year;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << (int)date.day << "." << static_cast<int>(date.month) << "." << date.year;
    return os;
}

std::istream& operator>>(std::istream& is, Date& date)
{
    int d, m, y;
    std::cout << "Enter date (day month year): ";
    is >> d >> m >> y;
    date = Date(static_cast<uint8_t>(d), static_cast<uint8_t>(m), static_cast<uint16_t>(y));
    return is;
}

std::string Date::toString() const
{
    return std::to_string(day) + "." + 
           std::to_string(static_cast<int>(month)) + "." + 
           std::to_string(year);
}