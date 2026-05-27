#include "FullName.h"
#include <stdexcept>

FullName::FullName(const std::string& surname, const std::string& name, const std::string& patronymic)
{
    if (surname.empty() || name.empty())
    {
        throw std::invalid_argument("Surname and name cannot be empty");
    }
    this->surname = surname;
    this->name = name;
    this->patronymic = patronymic;
}

std::string FullName::getSurname() const
{
    return surname;
}

std::string FullName::getName() const
{
    return name;
}

std::string FullName::getPatronymic() const
{
    return patronymic;
}

std::ostream& operator<<(std::ostream& os, const FullName& fullName)
{
    os << fullName.surname << " " << fullName.name << " " << fullName.patronymic;
    return os;
}

std::istream& operator>>(std::istream& is, FullName& fullName)
{
    std::cout << "Enter surname: ";
    is >> fullName.surname;
    std::cout << "Enter name: ";
    is >> fullName.name;
    std::cout << "Enter patronymic: ";
    is >> fullName.patronymic;
    return is;
}

std::string FullName::toString() const
{
    return surname + " " + name + " " + patronymic;
}