#include "Publication.h"

#include <stdexcept>

/**
 * @details Поля инициализируются в объявленном порядке. Проверка id
 * выполняется уже в теле конструктора: если номер некорректный,
 * объект не будет создан.
 */
miit::library::Publication::Publication(const int id, const std::string& title,
                                        const std::string& publisher, const int publicationYear)
    : id(id),
      title(title),
      publisher(publisher),
      publicationYear(publicationYear)
{
    if (this->id <= 0)
    {
        throw std::invalid_argument("Инвентарный номер должен быть положительным");
    }
}

/** @details Метод только читает поле, поэтому помечен const noexcept */
int miit::library::Publication::getId() const noexcept
{
    return this->id;
}

/** @details Возвращается константная ссылка: копирование строки не производится */
const std::string& miit::library::Publication::getTitle() const noexcept
{
    return this->title;
}

const std::string& miit::library::Publication::getPublisher() const noexcept
{
    return this->publisher;
}

int miit::library::Publication::getPublicationYear() const noexcept
{
    return this->publicationYear;
}
