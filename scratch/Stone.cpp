#include "Stone.hpp"

namespace Go
{

Stone::Color Stone::getColor ()
{
    return m_color;
}

Stone::Color getOpposingColor (Stone::Color color)
{
    if (color == Stone::Color::NONE)
        return color;

    return (color == Stone::Color::BLACK) ? Stone::Color::WHITE : Stone::Color::BLACK;
}

}
