#include "ShelfPlace.h"

/**
 * @details Все три поля константны, поэтому доступна только
 * инициализация в списке инициализации конструктора.
 */
miit::library::ShelfPlace::ShelfPlace(const std::string& hall, const int rack, const int shelf)
    : hall(hall),
      rack(rack),
      shelf(shelf)
{
}

const std::string& miit::library::ShelfPlace::getHall() const noexcept
{
    return this->hall;
}

int miit::library::ShelfPlace::getRack() const noexcept
{
    return this->rack;
}

int miit::library::ShelfPlace::getShelf() const noexcept
{
    return this->shelf;
}

std::string miit::library::ShelfPlace::toString() const
{
    return this->hall + ", стеллаж " + std::to_string(this->rack) +
           ", полка " + std::to_string(this->shelf);
}
