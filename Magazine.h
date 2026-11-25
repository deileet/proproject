#pragma once

#include <string>

#include "Publication.h"

namespace miit::library
{
    /**
     * @brief Периодическое издание (журнал)
     *
     * Второй наследник Publication. Нужен для демонстрации полиморфизма:
     * вместе с Book журнал помещается в коллекцию базового типа.
     */
    class Magazine : public Publication
    {
    private:
        /** @brief Номер выпуска */
        int issueNumber;

        /** @brief Тематика журнала */
        std::string topic;

    public:
        /**
         * @brief Конструктор журнала
         * @param id Инвентарный номер
         * @param title Название
         * @param publisher Издательство
         * @param publicationYear Год
         * @param issueNumber Номер выпуска
         * @param topic Тематика
         */
        Magazine(const int id, const std::string& title,
                 const std::string& publisher, const int publicationYear,
                 const int issueNumber, const std::string& topic);

        /** @brief Получить номер выпуска */
        int getIssueNumber() const noexcept;

        /** @brief Получить тематику */
        const std::string& getTopic() const noexcept;

        /** @brief Вернуть строку "Журнал" */
        std::string getKind() const override;

        /** @brief Сформировать информацию о журнале */
        std::string toString() const override;
    };
}
