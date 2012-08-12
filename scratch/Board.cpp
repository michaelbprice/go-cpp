#include "Board.hpp"
#include "Stone.hpp"

#include <functional>
#include <memory>
#include <utility>
#include <unordered_set>
#include <cassert>

#include <iostream>

namespace Go {

Board::Board ()
{
    for (size_t row = 0; row < BOARD_SIZE; ++row)
    {
        for (size_t column =0; column < BOARD_SIZE; ++column)
        {
            m_points[row][column].coordinates.row = row; 
            m_points[row][column].coordinates.column = column; 
        }
    }
}

const Point & Board::getPointAbove (const Point & point) const
{
    if (point.coordinates.row - 1 < BOARD_SIZE)
        return m_points[point.coordinates.row - 1][point.coordinates.column];

    return point;
}

const Point & Board::getPointBelow (const Point & point) const
{
    if (point.coordinates.row + 1 < BOARD_SIZE)
        return m_points[point.coordinates.row + 1][point.coordinates.column];

    return point;
}

const Point & Board::getPointLeft (const Point & point) const
{
    if (point.coordinates.column - 1 < BOARD_SIZE)
        return m_points[point.coordinates.row][point.coordinates.column - 1];

    return point;
}

const Point & Board::getPointRight (const Point & point) const
{
    if (point.coordinates.column + 1 < BOARD_SIZE)
        return m_points[point.coordinates.row][point.coordinates.column + 1];

    return point;
}

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
    assert(stone.get() != nullptr);

    m_points[x][y].playStone(std::move(stone));
    return true;
}

void Board::removeCapturedStones ()
{
    ConstPointSet alreadyVisited;

    for (size_t row = 0; row < m_points.size(); ++row)
    {
        for (size_t column = 0; column < m_points[row].size(); ++column)
        {
            try
            {
                Chain currentChain {m_points[row][column], *this, &alreadyVisited};

                if (currentChain.color() != Stone::Color::NONE && currentChain.libertyCount() == 0)
                {
                    currentChain.foreach([this](const Point & point)
                    {
                        m_points[point.coordinates.row][point.coordinates.column].removeStone();
                    }); 
                }
            }
            catch (int)
            {
//std::cout << "Already visited as part of another chain [" << row << "," << column << "]" << std::endl;
            }
        }
    }
}

bool Board::wouldBeValidMove (Stone::Color stoneColor, size_t row, size_t column) const
{
    if (!m_points[row][column].canPlayStone())
    {
        return false;
    }

    //std::vector<Chain> newChains = calculateChains();

    Chain potentialChain {stoneColor, m_points[row][column], *this, nullptr};

    if (potentialChain.libertyCount() == 0)
    {
        return false;
    }

    return true;
}

} // namespace Go

