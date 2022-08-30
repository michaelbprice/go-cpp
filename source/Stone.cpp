#include "Stone.hpp"

#include <optional>
#include <ostream>

using namespace std;

namespace Go {

StoneColor Stone::getColor () const
{
    return m_color;
}

StoneColor getOpposingColor (StoneColor color)
{
    return (color == StoneColor::BLACK) ? StoneColor::WHITE : StoneColor::BLACK;
}

}

ostream & operator<< (ostream & out, const std::optional<Go::Stone> & stone)
{
    using namespace Go;
    out << "Stone: {";

    if (stone.has_value())
    {
        switch (stone->getColor())
        {
         case StoneColor::BLACK: out << "Black"; break;
         case StoneColor::WHITE: out << "White"; break;
        }
    }
    else
    {
        out << "Empty";
    }

    out << "}";
    return out;
}
