#include "Point.hpp"
#include "Stone.hpp"
#include <utility>

namespace Go {

Stone::Color Point::getStoneColor () const
{
    if (m_stone.get() == nullptr)
        return Stone::Color::NONE;

    return m_stone->getColor();
}

void Point::playStone (std::unique_ptr<Stone> stone)
{
    m_stone = std::move(stone);
}

bool Point::canPlayStone () const
{
    return m_stone.get() == nullptr;
}

void Point::removeStone ()
{ 
    m_stone.reset();
}

} // namespace Go
