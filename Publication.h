#pragma once

#include <string>

namespace miit::library
{
    /**
     * @brief Базовое абстрактное издание библиотеки
     *
     * Хранит общие для всех изданий данные: инвентарный номер, название,
     * издательство и год. Конкретные виды изданий (книга, журнал)
     * расширяют этот класс и реализуют getKind() и toString().
     */
    class Publication
    {
    private:
        /** @brief Инвентарный номер, не меняется после создания */
        const int id;

        /** @brief Название издания */
        std::string title;

        /** @brief Издательство */
        std::string publisher;

        /** @brief Год издания */
        int publicationYear;

    public:
        /**
         * @brief Конструктор
         * @param id Инвентарный номер (должен быть больше нуля)
         * @param title Название
         * @param publisher Издательство
         * @param publicationYear Год издания
         * @throw std::invalid_argument Если id <= 0
         */
        Publication(const int id, const std::string& title,
                    const std::string& publisher, const int publicationYear);

        /** @brief Виртуальный деструктор для удаления через указатель на базу */
        virtual ~Publication() = default;

        /** @brief Получить инвентарный номер */
        int getId() const noexcept;

        /** @brief Получить название */
        const std::string& getTitle() const noexcept;

        /** @brief Получить издательство */
        const std::string& getPublisher() const noexcept;

        /** @brief Получить год издания */
        int getPublicationYear() const noexcept;

        /**
         * @brief Вид издания
         * @return "Книга", "Журнал" и т. д.
         */
        virtual std::string getKind() const = 0;

        /**
         * @brief Полная информация об издании в виде строки
         * @return Строка для вывода; сам класс в поток ничего не пишет
         */
        virtual std::string toString() const = 0;
    };
}
