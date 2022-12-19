#include "Point.hpp"
#include "Stone.hpp"
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

namespace Go {

const std::optional<Stone> & Point::getStone () const
{
    return m_stone;
}

void Point::playStone (const Stone & stone)
{
    m_stone = stone;
}

bool Point::canPlayStone () const
{
    return !m_stone.has_value();
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

    if (point.m_stone.has_value())
        out << *point.m_stone;
    else
        out << "{null}";

    out << "}";
    return out;
}
