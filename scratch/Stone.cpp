#include "Stone.hpp"

namespace Go
{

Stone::Color Stone::getColor ()
{
    return m_color;
}

Stone::Color getOpposingColor (Stone::Color color)
{
    return (color == Stone::Color::BLACK) ? Stone::Color::WHITE : Stone::Color::BLACK;
}

}
