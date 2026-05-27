#include "Teacher.h"
#include <stdexcept>

Teacher::Teacher(const FullName& fullName, Gender gender, const Date& birthDate,
                 Position position, uint8_t experience)
    : Person(fullName, gender, birthDate), position(position), experience(experience) {}

Position Teacher::getPosition() const
{
    return position;
}

uint8_t Teacher::getExperience() const
{
    return experience;
}

std::string Teacher::toString() const
{
    std::string positionStr;
    switch (position)
    {
        case Position::Professor:
            positionStr = "Professor";
            break;
        case Position::AssociateProfessor:
            positionStr = "Associate Professor";
            break;
        case Position::SeniorLecturer:
            positionStr = "Senior Lecturer";
            break;
        case Position::Assistant:
            positionStr = "Assistant";
            break;
    }
    
    return "Teacher: " + Person::toString() + 
           ", Position: " + positionStr + 
           ", Experience: " + std::to_string(experience) + " years";
}

std::ostream& operator<<(std::ostream& os, const Teacher& teacher)
{
    os << teacher.toString();
    return os;
}

std::istream& operator>>(std::istream& is, Teacher& teacher)
{
    std::cout << "=== Enter Teacher ===" << std::endl;
    FullName name;
    int genderInt, positionInt;
    uint8_t experience;
    Date birthDate;
    
    is >> name;
    std::cout << "Enter gender (0 - Male, 1 - Female): ";
    is >> genderInt;
    Gender g = (genderInt == 1) ? Gender::Female : Gender::Male;
    
    std::cout << "Enter position (0 - Professor, 1 - Associate Professor, 2 - Senior Lecturer, 3 - Assistant): ";
    is >> positionInt;
    Position p = static_cast<Position>(positionInt);
    
    std::cout << "Enter experience (years): ";
    is >> experience;
    
    is >> birthDate;
    
    teacher = Teacher(name, g, birthDate, p, experience);
    return is;
}