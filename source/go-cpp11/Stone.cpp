#include "Stone.hpp"

#include <ostream>

using namespace std;

namespace Go {

StoneColor Stone::getColor () const
{
    return m_color;
}

StoneColor getOpposingColor (StoneColor color)
{
    if (color == StoneColor::NONE)
        return color;

    return (color == StoneColor::BLACK) ? StoneColor::WHITE : StoneColor::BLACK;
}

}

ostream & operator<< (ostream & out, const Go::Stone & stone)
{
    using namespace Go;
    out << "Stone: {";

    switch (stone.getColor())
    {
     case StoneColor::NONE: out << "Empty"; break;
     case StoneColor::BLACK: out << "Black"; break;
     case StoneColor::WHITE: out << "White"; break;
    }

    out << "}";
    return out;
}
