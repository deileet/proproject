#include "Magazine.h"

/**
 * @details Инициализация базовой части и двух собственных полей
 */
miit::library::Magazine::Magazine(const int id, const std::string& title,
                                  const std::string& publisher, const int publicationYear,
                                  const int issueNumber, const std::string& topic)
    : Publication(id, title, publisher, publicationYear),
      issueNumber(issueNumber),
      topic(topic)
{
}

int miit::library::Magazine::getIssueNumber() const noexcept
{
    return this->issueNumber;
}

const std::string& miit::library::Magazine::getTopic() const noexcept
{
    return this->topic;
}

std::string miit::library::Magazine::getKind() const
{
    return "Журнал";
}

/** @details Аналогично Book: возврат строки, а не печать в поток */
std::string miit::library::Magazine::toString() const
{
    return this->getKind() + " №" + std::to_string(this->getId()) +
           ": " + this->getTitle() + " (выпуск " + std::to_string(this->issueNumber) + ")\n" +
           "  Издательство: " + this->getPublisher() +
           " | Год: " + std::to_string(this->getPublicationYear()) +
           " | Тематика: " + this->topic;
}
