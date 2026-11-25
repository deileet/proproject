#pragma once

#include <string>
#include <vector>

#include "Publication.h"

namespace miit::library
{
    /**
     * @brief Книга — издание с одним или несколькими авторами
     *
     * Список авторов хранится в векторе. Именно поэтому труд в соавторстве
     * попадает в поиск по каждому из авторов: в Library книга регистрируется
     * под каждым именем из этого списка.
     */
    class Book : public Publication
    {
    private:
        /** @brief Авторы книги, включая соавторов */
        std::vector<std::string> authors;

        /** @brief Тематика книги */
        std::string topic;

        /** @brief Краткая аннотация (может быть пустой) */
        std::string annotation;

    public:
        /**
         * @brief Конструктор книги
         * @param id Инвентарный номер
         * @param title Название
         * @param authors Список авторов
         * @param publisher Издательство
         * @param publicationYear Год издания
         * @param topic Тематика
         * @param annotation Аннотация (по умолчанию пустая)
         */
        Book(const int id, const std::string& title,
             const std::vector<std::string>& authors,
             const std::string& publisher, const int publicationYear,
             const std::string& topic, const std::string& annotation = "");

        /**
         * @brief Все авторы книги
         * @return Константная ссылка на вектор авторов
         */
        const std::vector<std::string>& getAuthors() const noexcept;

        /** @brief Получить тематику */
        const std::string& getTopic() const noexcept;

        /** @brief Получить аннотацию */
        const std::string& getAnnotation() const noexcept;

        /**
         * @brief Проверить, является ли данный человек автором или соавтором
         * @param author Имя автора
         * @return true, если имя есть в списке авторов
         */
        bool hasAuthor(const std::string& author) const noexcept;

        /** @brief Вернуть строку "Книга" */
        std::string getKind() const override;

        /** @brief Сформировать полную информацию о книге */
        std::string toString() const override;
    };
}
