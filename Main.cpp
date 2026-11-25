#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

#include "Book.h"
#include "Library.h"
#include "Magazine.h"
#include "Publication.h"
#include "ShelfPlace.h"

using namespace miit::library;

/**
 * @brief Точка входа в демонстрационную программу
 * @return 0 при успешном завершении
 * @details Сначала создаются данные, затем коллекция базового типа для
 * демонстрации полиморфизма, после чего показываются все 5 заданий варианта
 */
int main()
{
    /** @brief Тестовые книги: у первой книги два автора (соавторство) */
    const std::vector<Book> books =
    {
        Book(101, "Математический анализ",
             {"Иванов И. И.", "Петров П. П."}, "Высшая школа", 2021, "Математика",
             "Курс математического анализа для технических вузов"),
        Book(102, "Линейная алгебра",
             {"Иванов И. И."}, "Высшая школа", 2020, "Математика"),
        Book(103, "Основы программирования",
             {"Сидоров С. С."}, "Питер", 2023, "Информатика"),
        Book(104, "История России",
             {"Кузнецова К. К."}, "Просвещение", 2019, "История")
    };

    /** @brief Тестовые журналы — второй тип-наследник Publication */
    const std::vector<Magazine> magazines =
    {
        Magazine(201, "Научный вестник", "МИИТ", 2024, 3, "Математика"),
        Magazine(202, "Технологии и мы", "Питер", 2025, 7, "Информатика")
    };

    // Коллекция базового типа, заполненная объектами типов-наследников.
    // unique_ptr нужен, потому что Publication абстрактный и хранить объекты
    // напрямую нельзя; указатель обеспечивает виртуальный вызов методов.
    std::vector<std::unique_ptr<Publication>> publications;
    for (const Book& book : books)
    {
        publications.push_back(std::make_unique<Book>(book));
    }
    for (const Magazine& magazine : magazines)
    {
        publications.push_back(std::make_unique<Magazine>(magazine));
    }

    std::cout << "=== Коллекция объектов базового типа Publication ===\n";
    for (const std::unique_ptr<Publication>& item : publications)
    {
        std::cout << item->getKind() << ": " << item->getTitle()
                  << " (" << item->getPublisher() << ", " << item->getPublicationYear() << ")\n";
    }

    /** @brief Библиотека и места на полке для каждой из четырёх книг */
    Library library;
    const std::vector<ShelfPlace> places =
    {
        ShelfPlace("Зал 1", 3, 2),
        ShelfPlace("Зал 1", 3, 4),
        ShelfPlace("Зал 2", 1, 1),
        ShelfPlace("Зал 2", 5, 3)
    };

    for (std::size_t i = 0; i < books.size(); ++i)
    {
        library.addBook(books[i], places[i]);
    }
    for (const Magazine& magazine : magazines)
    {
        library.addMagazine(magazine);
    }

    // Пять заданий варианта 12
    std::cout << "\n=== Задание 1. Книги по названию ===\n";
    std::cout << Library::formatBooks(library.findBooksByTitle("Линейная алгебра"));

    std::cout << "\n=== Задание 2. Труды автора (включая соавторство) ===\n";
    std::cout << Library::formatBooks(library.findWorksByAuthor("Иванов И. И."));

    std::cout << "\n=== Задание 3. Книги по тематике ===\n";
    std::cout << Library::formatBooks(library.findBooksByTopic("Математика"));

    std::cout << "\n=== Задание 4. Книги издательства ===\n";
    std::cout << Library::formatBooks(library.findBooksByPublisher("Высшая школа"));

    std::cout << "\n=== Задание 5. Местонахождение книги ===\n";
    std::cout << library.getLocationInfo("История России");
    std::cout << library.getLocationInfo("Неизвестная книга");

    std::cout << "\nСловарь книг по инвентарному номеру: " << library.getBooksById().size() << "\n";
    std::cout << "Словарь местонахождений: " << library.getPlacesById().size() << "\n";
    std::cout << "Словарь журналов: " << library.getMagazinesById().size() << "\n";

    return 0;
}
