#include <iostream>
#include <vector>
#include <string>
#include "Person.h"
#include "Teacher.h"

/**
 * @brief Считывает целое значение с клавиатуры
 * @param report строка информации
 * @return считанное значение
 */
int getIntValue(const std::string& report = "");

/**
 * @brief Точка входа в программу
 * @return 0, если программа выполнена корректно
 */
int main()
{
    try
    {
        std::cout << "=== PERSON AND TEACHER MANAGEMENT SYSTEM ===" << std::endl;
        
        std::vector<Teacher> teachers;
        
        int count = getIntValue("Enter number of teachers: ");
        
        for (int i = 0; i < count; ++i)
        {
            std::cout << "\n--- Teacher #" << (i + 1) << " ---" << std::endl;
            Teacher teacher;
            std::cin >> teacher;
            teachers.push_back(teacher);
        }
        
        std::cout << "\n=== SORTING OPTIONS ===" << std::endl;
        std::cout << "1. Sort by surname (alphabetical)" << std::endl;
        std::cout << "2. Sort by position (Professor -> Associate Professor -> Senior Lecturer -> Assistant)" << std::endl;
        std::cout << "3. Sort by experience" << std::endl;
        
        int choice = getIntValue("Choose sorting option (1-3): ");
        
        std::cout << "\n=== SORTED TEACHERS ===" << std::endl;
        
        switch (choice)
        {
            case 1:
                Person::printSorted(
                    std::vector<Person>(teachers.begin(), teachers.end()),
                    [](const Person& a, const Person& b) {
                        return a.getFullName().getSurname() < b.getFullName().getSurname();
                    }
                );
                break;
                
            case 2:
                Person::printSorted(
                    std::vector<Person>(teachers.begin(), teachers.end()),
                    [](const Person& a, const Person& b) {
                        const Teacher& ta = dynamic_cast<const Teacher&>(a);
                        const Teacher& tb = dynamic_cast<const Teacher&>(b);
                        return static_cast<int>(ta.getPosition()) < static_cast<int>(tb.getPosition());
                    }
                );
                break;
                
            case 3:
                Person::printSorted(
                    std::vector<Person>(teachers.begin(), teachers.end()),
                    [](const Person& a, const Person& b) {
                        const Teacher& ta = dynamic_cast<const Teacher&>(a);
                        const Teacher& tb = dynamic_cast<const Teacher&>(b);
                        return ta.getExperience() < tb.getExperience();
                    }
                );
                break;
                
            default:
                std::cout << "Invalid option!" << std::endl;
                break;
        }
        
        std::cout << "\n=== TESTING EXCEPTIONS ===" << std::endl;
        std::cout << "Trying to create invalid date (32.13.2025)..." << std::endl;
        Date badDate(32, 13, 2025);
        
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    
    return 0;
}

int getIntValue(const std::string& report)
{
    std::cout << report;
    int value = 0;
    std::cin >> value;
    if (std::cin.fail())
    {
        std::cout << "Error: invalid input!" << std::endl;
        exit(1);
    }
    return value;
}