#include "Point.hpp"

namespace Go {

void Point::playStone (Stone & stone)
{
    m_pStone = &stone;
}

bool Point::canPlayStone () const
{
    return m_pStone == nullptr;
}

} // namespace Go
