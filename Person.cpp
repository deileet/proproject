#include "Person.h"
#include <algorithm>
#include <stdexcept>

Person::Person(const FullName& fullName, Gender gender, const Date& birthDate)
    : fullName(fullName), gender(gender), birthDate(birthDate) {}

FullName Person::getFullName() const
{
    return fullName;
}

Gender Person::getGender() const
{
    return gender;
}

Date Person::getBirthDate() const
{
    return birthDate;
}

std::string Person::toString() const
{
    std::string genderStr = (gender == Gender::Male) ? "Male" : "Female";
    return "Person: " + fullName.toString() + 
           ", Gender: " + genderStr + 
           ", BirthDate: " + birthDate.toString();
}

void Person::printSorted(const std::vector<Person>& persons,
                        std::function<bool(const Person&, const Person&)> comparator,
                        std::ostream& os)
{
    std::vector<Person> sorted = persons;
    std::sort(sorted.begin(), sorted.end(), comparator);
    
    for (const auto& person : sorted)
    {
        os << person << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Person& person)
{
    os << person.toString();
    return os;
}

std::istream& operator>>(std::istream& is, Person& person)
{
    std::cout << "=== Enter Person ===" << std::endl;
    FullName name;
    int genderInt;
    Date birthDate;
    
    is >> name;
    std::cout << "Enter gender (0 - Male, 1 - Female): ";
    is >> genderInt;
    Gender g = (genderInt == 1) ? Gender::Female : Gender::Male;
    is >> birthDate;
    
    person = Person(name, g, birthDate);
    return is;
}