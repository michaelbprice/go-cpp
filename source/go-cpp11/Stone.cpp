#include "Stone.hpp"

namespace Go
{

StoneColor Stone::getColor ()
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
