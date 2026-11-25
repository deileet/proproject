#pragma once

#include <map>
#include <string>
#include <vector>

#include "Book.h"
#include "Magazine.h"
#include "ShelfPlace.h"

namespace miit::library
{
    /**
     * @brief Библиотека с набором ассоциативных контейнеров для поиска
     *
     * Основное хранилище — booksById (словарь «номер -> книга»).
     * Остальные словари — это индексы: они хранят указатели на книги
     * из основного хранилища. std::map не аннулирует ссылки при вставке,
     * поэтому указатели остаются корректными при добавлении новых книг.
     */
    class Library
    {
    private:
        /** @brief Основное хранилище книг по инвентарному номеру */
        std::map<int, Book> booksById;

        /** @brief Хранилище журналов по инвентарному номеру */
        std::map<int, Magazine> magazinesById;

        /** @brief Местонахождение книги по её инвентарному номеру */
        std::map<int, ShelfPlace> placesById;

        /** @brief Индекс: название -> список книг с этим названием */
        std::map<std::string, std::vector<const Book*>> booksByTitle;

        /** @brief Индекс: автор -> список его трудов (включая соавторство) */
        std::map<std::string, std::vector<const Book*>> booksByAuthor;

        /** @brief Индекс: тематика -> список книг */
        std::map<std::string, std::vector<const Book*>> booksByTopic;

        /** @brief Индекс: издательство -> список книг */
        std::map<std::string, std::vector<const Book*>> booksByPublisher;

        /**
         * @brief Безопасный поиск в индексном словаре
         * @param index Словарь, где ищем
         * @param key Ключ поиска
         * @return Вектор найденных книг или пустой вектор
         */
        static std::vector<const Book*> lookup(
            const std::map<std::string, std::vector<const Book*>>& index,
            const std::string& key);

    public:
        /** @brief Конструктор по умолчанию: все словари пусты */
        Library() = default;

        /**
         * @brief Добавить книгу и записать её место на полке
         * @param book Книга
         * @param place Местонахождение
         * @details Если книга с таким инвентарным номером уже есть, добавление игнорируется
         */
        void addBook(const Book& book, const ShelfPlace& place);

        /**
         * @brief Добавить журнал
         * @param magazine Журнал
         */
        void addMagazine(const Magazine& magazine);

        /**
         * @brief Выдать книги по названию
         * @param title Искомое название
         * @return Вектор указателей на найденные книги
         */
        std::vector<const Book*> findBooksByTitle(const std::string& title) const;

        /**
         * @brief Выдать все труды автора
         * @param author Имя автора
         * @return Книги, где он указан в том числе соавтором
         */
        std::vector<const Book*> findWorksByAuthor(const std::string& author) const;

        /**
         * @brief Выдать книги по тематике
         * @param topic Тематика
         * @return Вектор указателей на найденные книги
         */
        std::vector<const Book*> findBooksByTopic(const std::string& topic) const;

        /**
         * @brief Выдать книги издательства
         * @param publisher Издательство
         * @return Вектор указателей на найденные книги
         */
        std::vector<const Book*> findBooksByPublisher(const std::string& publisher) const;

        /**
         * @brief Выдать местонахождение книги по названию
         * @param title Название книги
         * @return Готовый текст ответа (без вывода в поток)
         */
        std::string getLocationInfo(const std::string& title) const;

        /**
         * @brief Форматировать список книг в одну строку
         * @param books Книги, которые нужно показать
         * @return Текст со всеми книгами или сообщение «Ничего не найдено.»
         */
        static std::string formatBooks(const std::vector<const Book*>& books);

        /** @brief Доступ к словарю книг только для чтения */
        const std::map<int, Book>& getBooksById() const noexcept;

        /** @brief Доступ к словарю местоположений только для чтения */
        const std::map<int, ShelfPlace>& getPlacesById() const noexcept;

        /** @brief Доступ к словарю журналов только для чтения */
        const std::map<int, Magazine>& getMagazinesById() const noexcept;
    };
}
