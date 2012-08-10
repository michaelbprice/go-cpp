#include "Board.hpp"
#include "Stone.hpp"

#include <memory>
#include <utility>

namespace Go {

Stone::Color Board::getStoneColorAt (size_t x, size_t y) const
{
    return m_points[x][y].getStoneColor();
}

bool Board::isOccupiedPoint (size_t x, size_t y)
{
    return !(m_points[x][y].canPlayStone());
}

bool Board::isLibertyPoint (size_t x, size_t y)
{
    return false;
}

bool Board::placeStoneAt (size_t x, size_t y, std::unique_ptr<Stone> stone)
{
    // TODO: assert this state instead...

    if (!m_points[x][y].canPlayStone())
        return false;

    m_points[x][y].playStone(std::move(stone));
    return true;
}

} // namespace Go

