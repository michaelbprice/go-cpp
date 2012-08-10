#include "Stone.hpp"

namespace Go
{

Stone::Color getOpposingColor (Stone::Color color)
{
    return (color == Stone::Color::BLACK) ? Stone::Color::WHITE : Stone::Color::BLACK;
}

}
