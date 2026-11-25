#include "Library.h"

/**
 * @details Если ключ не найден, index.find() возвращает end().
 * В таком случае возвращается пустой вектор — вызывающему не нужно
 * проверять специальный «не найден» флаг.
 */
std::vector<const miit::library::Book*> miit::library::Library::lookup(
    const std::map<std::string, std::vector<const Book*>>& index,
    const std::string& key)
{
    const auto found = index.find(key);
    if (found == index.end())
    {
        return {};
    }
    return found->second;
}

/**
 * @details Сначала проверяем дубликат по ID. Затем вставляем книгу в основной
 * словарь и запоминаем ссылку на неё. Именно эта ссылка попадает во все
 * остальные индексы, чтобы данные не дублировались.
 */
void miit::library::Library::addBook(const Book& book, const ShelfPlace& place)
{
    const int id = book.getId();
    if (this->booksById.find(id) != this->booksById.end())
    {
        return;
    }

    const auto inserted = this->booksById.emplace(id, book);
    const Book& storedBook = inserted.first->second;

    this->placesById.emplace(id, place);

    this->booksByTitle[storedBook.getTitle()].push_back(&storedBook);
    for (const std::string& author : storedBook.getAuthors())
    {
        this->booksByAuthor[author].push_back(&storedBook);
    }
    this->booksByTopic[storedBook.getTopic()].push_back(&storedBook);
    this->booksByPublisher[storedBook.getPublisher()].push_back(&storedBook);
}

/** @details emplace не перезапишет журнал с тем же номером */
void miit::library::Library::addMagazine(const Magazine& magazine)
{
    this->magazinesById.emplace(magazine.getId(), magazine);
}

/** @details Делегируем поиск общей функции lookup */
std::vector<const miit::library::Book*> miit::library::Library::findBooksByTitle(
    const std::string& title) const
{
    return lookup(this->booksByTitle, title);
}

/** @details Книга в соавторстве записана под каждым автором в addBook */
std::vector<const miit::library::Book*> miit::library::Library::findWorksByAuthor(
    const std::string& author) const
{
    return lookup(this->booksByAuthor, author);
}

std::vector<const miit::library::Book*> miit::library::Library::findBooksByTopic(
    const std::string& topic) const
{
    return lookup(this->booksByTopic, topic);
}

std::vector<const miit::library::Book*> miit::library::Library::findBooksByPublisher(
    const std::string& publisher) const
{
    return lookup(this->booksByPublisher, publisher);
}

/**
 * @details Находим все книги с нужным названием, затем по ID каждой книги
 * обращаемся к словарю placesById и складываем готовый текст ответа.
 */
std::string miit::library::Library::getLocationInfo(const std::string& title) const
{
    const std::vector<const Book*> found = this->findBooksByTitle(title);
    if (found.empty())
    {
        return "Книга '" + title + "' не найдена.";
    }

    std::string result;
    for (const Book* book : found)
    {
        const auto place = this->placesById.find(book->getId());
        result += book->getTitle() + " (инв. №" + std::to_string(book->getId()) + "): ";
        result += (place == this->placesById.end() ? std::string("место не указано") : place->second.toString());
        result += '\n';
    }
    return result;
}

/**
 * @details Вспомогательный метод: библиотека не печатает в cout, а только
 * подготавливает текст. Решение, выводить его или нет, остаётся за main().
 */
std::string miit::library::Library::formatBooks(const std::vector<const Book*>& books)
{
    if (books.empty())
    {
        return "Ничего не найдено.";
    }

    std::string result;
    for (const Book* book : books)
    {
        result += book->toString() + "\n";
    }
    return result;
}

const std::map<int, miit::library::Book>& miit::library::Library::getBooksById() const noexcept
{
    return this->booksById;
}

const std::map<int, miit::library::ShelfPlace>& miit::library::Library::getPlacesById() const noexcept
{
    return this->placesById;
}

const std::map<int, miit::library::Magazine>& miit::library::Library::getMagazinesById() const noexcept
{
    return this->magazinesById;
}
