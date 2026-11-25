#include "Book.h"

#include <algorithm>

/**
 * @details Сначала вызывается конструктор базового Publication,
 * затем инициализируются собственные поля Book.
 */
miit::library::Book::Book(const int id, const std::string& title,
                          const std::vector<std::string>& authors,
                          const std::string& publisher, const int publicationYear,
                          const std::string& topic, const std::string& annotation)
    : Publication(id, title, publisher, publicationYear),
      authors(authors),
      topic(topic),
      annotation(annotation)
{
}

/** @details Возвращаем ссылку, чтобы не копировать весь вектор авторов */
const std::vector<std::string>& miit::library::Book::getAuthors() const noexcept
{
    return this->authors;
}

const std::string& miit::library::Book::getTopic() const noexcept
{
    return this->topic;
}

const std::string& miit::library::Book::getAnnotation() const noexcept
{
    return this->annotation;
}

/**
 * @details std::find ищет строку в векторе. Если она найдена,
 * итератор не равен authors.end() — значит, это автор или соавтор.
 */
bool miit::library::Book::hasAuthor(const std::string& author) const noexcept
{
    return std::find(this->authors.begin(), this->authors.end(), author) != this->authors.end();
}

std::string miit::library::Book::getKind() const
{
    return "Книга";
}

/**
 * @details Метод только складывает строки и возвращает результат.
 * Вывод в std::cout здесь не производится — библиотека не зависит от потоков.
 */
std::string miit::library::Book::toString() const
{
    std::string result = this->getKind() + " №" + std::to_string(this->getId()) +
                         ": " + this->getTitle() + "\n";
    result += "  Авторы: ";
    for (const std::string& author : this->authors)
    {
        result += author + "; ";
    }
    result += "\n  Издательство: " + this->getPublisher();
    result += " | Год: " + std::to_string(this->getPublicationYear());
    result += " | Тематика: " + this->topic;
    if (!this->annotation.empty())
    {
        result += "\n  Аннотация: " + this->annotation;
    }
    return result;
}
