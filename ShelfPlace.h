#pragma once

#include <string>

namespace miit::library
{
    /**
     * @brief Местонахождение книги на полке
     *
     * Значение описывается тремя числами/строками: зал, стеллаж, полка.
     * Класс не меняется после создания, поэтому его поля объявлены const.
     */
    class ShelfPlace
    {
    private:
        /** @brief Название зала */
        const std::string hall;

        /** @brief Номер стеллажа */
        const int rack;

        /** @brief Номер полки */
        const int shelf;

    public:
        /**
         * @brief Конструктор
         * @param hall Название зала (по умолчанию пусто)
         * @param rack Номер стеллажа (по умолчанию 0)
         * @param shelf Номер полки (по умолчанию 0)
         */
        ShelfPlace(const std::string& hall = "", const int rack = 0, const int shelf = 0);

        /** @brief Получить название зала */
        const std::string& getHall() const noexcept;

        /** @brief Получить номер стеллажа */
        int getRack() const noexcept;

        /** @brief Получить номер полки */
        int getShelf() const noexcept;

        /**
         * @brief Строковое описание места
         * @return Например: "Зал 2, стеллаж 5, полка 3"
         */
        std::string toString() const;
    };
}
