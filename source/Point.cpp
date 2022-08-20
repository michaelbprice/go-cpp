#include "Point.hpp"
#include "Stone.hpp"
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

namespace Go {

StoneColor Point::getStoneColor () const
{
    if (m_stone.get() == nullptr)
        return StoneColor::NONE;

    return m_stone->getColor();
}

void Point::playStone (std::unique_ptr<Stone> stone)
{
    swap(m_stone, stone);
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

ostream & operator<< (ostream & out, const Go::PointCoords & coords)
{
    out << "[" << coords.row << "," << coords.column << "]";
    return out;
}

ostream & operator<< (ostream & out, const Go::Point & point)
{
    out << "Point: {" << point.coordinates << ", ";

    if (point.m_stone.get())
        out << *point.m_stone;
    else
        out << "{null}";

    out << "}";
    return out;
}
