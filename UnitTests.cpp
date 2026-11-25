#include "CppUnitTest.h"

#include <memory>
#include <string>
#include <vector>

#include "Book.h"
#include "Library.h"
#include "Magazine.h"
#include "Publication.h"
#include "ShelfPlace.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace miit::library;

namespace LibraryVariant12Tests
{
    /** @brief Тесты класса Book */
    TEST_CLASS(BookTests)
    {
    public:
        /** @brief Геттеры возвращают заданные значения, соавтор находится поиском */
        TEST_METHOD(GettersAndCoAuthors)
        {
            const Book book(1, "Книга", {"Автор А", "Автор Б"}, "Издательство", 2022, "Тема", "Описание");

            Assert::AreEqual(1, book.getId());
            Assert::AreEqual(std::string("Книга"), book.getTitle());
            Assert::AreEqual(std::string("Издательство"), book.getPublisher());
            Assert::AreEqual(2022, book.getPublicationYear());
            Assert::AreEqual(std::string("Тема"), book.getTopic());
            Assert::AreEqual(static_cast<std::size_t>(2), book.getAuthors().size());
            Assert::IsTrue(book.hasAuthor("Автор Б"));
            Assert::IsFalse(book.hasAuthor("Автор В"));
            Assert::AreEqual(std::string("Книга"), book.getKind());
        }

        /** @brief В строке присутствуют все основные поля */
        TEST_METHOD(ToStringContainsMainFields)
        {
            const Book book(2, "Алгебра", {"Автор А"}, "Мир", 2020, "Математика");
            const std::string info = book.toString();

            Assert::IsTrue(info.find("Алгебра") != std::string::npos);
            Assert::IsTrue(info.find("Автор А") != std::string::npos);
            Assert::IsTrue(info.find("Мир") != std::string::npos);
            Assert::IsTrue(info.find("Математика") != std::string::npos);
        }
    };

    /** @brief Тесты класса Magazine */
    TEST_CLASS(MagazineTests)
    {
    public:
        /** @brief Геттеры журнала */
        TEST_METHOD(Getters)
        {
            const Magazine magazine(10, "Вестник", "МИИТ", 2024, 5, "Наука");

            Assert::AreEqual(10, magazine.getId());
            Assert::AreEqual(5, magazine.getIssueNumber());
            Assert::AreEqual(std::string("Наука"), magazine.getTopic());
            Assert::AreEqual(std::string("Журнал"), magazine.getKind());
        }
    };

    /** @brief Тесты словарей и поиска в Library */
    TEST_CLASS(LibraryTests)
    {
    public:
        /** @brief Все словари заполняются, дубликат по ID игнорируется */
        TEST_METHOD(FiveDictionariesAreFilled)
        {
            Library library;
            const Book first(1, "Первая", {"Автор А", "Автор Б"}, "Изд-во 1", 2020, "Тема 1");
            const Book second(2, "Вторая", {"Автор А"}, "Изд-во 1", 2021, "Тема 1");

            library.addBook(first, ShelfPlace("Зал 1", 1, 1));
            library.addBook(second, ShelfPlace("Зал 1", 1, 2));
            library.addBook(first, ShelfPlace("Зал 9", 9, 9)); // дубликат по ID
            library.addMagazine(Magazine(3, "Журнал", "Изд-во 2", 2022, 1, "Тема 2"));

            Assert::AreEqual(static_cast<std::size_t>(2), library.getBooksById().size());
            Assert::AreEqual(static_cast<std::size_t>(2), library.getPlacesById().size());
            Assert::AreEqual(static_cast<std::size_t>(1), library.getMagazinesById().size());

            Assert::AreEqual(static_cast<std::size_t>(1), library.findBooksByTitle("Первая").size());
            Assert::AreEqual(static_cast<std::size_t>(2), library.findWorksByAuthor("Автор А").size());
            Assert::AreEqual(static_cast<std::size_t>(1), library.findWorksByAuthor("Автор Б").size());
            Assert::AreEqual(static_cast<std::size_t>(2), library.findBooksByTopic("Тема 1").size());
            Assert::AreEqual(static_cast<std::size_t>(2), library.findBooksByPublisher("Изд-во 1").size());
            Assert::AreEqual(static_cast<std::size_t>(0), library.findBooksByPublisher("Нет такого").size());
        }

        /** @brief Местонахождение возвращается готовой строкой */
        TEST_METHOD(LocationInfo)
        {
            Library library;
            library.addBook(Book(7, "Книга", {"Автор"}, "Изд-во", 2023, "Тема"),
                            ShelfPlace("Зал 2", 4, 6));

            const std::string info = library.getLocationInfo("Книга");
            Assert::IsTrue(info.find("Зал 2") != std::string::npos);
            Assert::IsTrue(info.find("стеллаж 4") != std::string::npos);
            Assert::IsTrue(info.find("полка 6") != std::string::npos);
            Assert::IsTrue(library.getLocationInfo("Другая").find("не найдена") != std::string::npos);
        }

        /** @brief Пустой результат имеет понятное сообщение */
        TEST_METHOD(EmptyResultFormatting)
        {
            Assert::AreEqual(std::string("Ничего не найдено."), Library::formatBooks({}));
        }
    };

    /** @brief Проверка полиморфизма через указатели на базовый класс */
    TEST_CLASS(PolymorphismTests)
    {
    public:
        /** @brief В коллекции base-указателей вызываются разные getKind() */
        TEST_METHOD(CollectionOfBaseType)
        {
            std::vector<std::unique_ptr<Publication>> collection;
            const std::vector<std::string> singleAuthor = {"Автор"};
            collection.push_back(std::make_unique<Book>(1, "Книга", singleAuthor, "Изд-во", 2020, "Тема"));
            collection.push_back(std::make_unique<Magazine>(2, "Журнал", "Изд-во", 2021, 1, "Тема"));

            Assert::AreEqual(static_cast<std::size_t>(2), collection.size());
            Assert::AreEqual(std::string("Книга"), collection[0]->getKind());
            Assert::AreEqual(std::string("Журнал"), collection[1]->getKind());
        }
    };
}
