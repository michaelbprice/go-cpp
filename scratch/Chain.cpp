#include "Chain.hpp"
#include "Board.hpp"
#include "Point.hpp"
#include "Stone.hpp"

#include <iterator>
#include <unordered_set>
#include <iostream>
#include <thread>
#include <chrono>

namespace Go {

Chain::Chain (Stone::Color stoneColor, const Point & startPoint, const Board & board, ConstPointSet * pointsToIgnore)
  : m_color(stoneColor)
  , m_startPoint(startPoint)
{
    if (pointsToIgnore != nullptr)
    {
        if (pointsToIgnore->find(&startPoint) != pointsToIgnore->end())
            throw 1; // TODO: make an exception type...
    }

    ConstPointSet myPointsToIgnore;

    doChainCalculation(startPoint, board, myPointsToIgnore); 

    if (pointsToIgnore != nullptr)
    {
        pointsToIgnore->insert(std::begin(myPointsToIgnore), std::end(myPointsToIgnore));
    }
}

Chain::Chain (const Point & startPoint, const Board & board, ConstPointSet * pointsToIgnore)
  : Chain(startPoint.getStoneColor(), startPoint, board, pointsToIgnore)
{
}

void Chain::doChainCalculation (const Point & point, const Board & board, ConstPointSet & pointsToIgnore)
{
//std::this_thread::sleep_for(std::chrono::seconds(1));
    
    if (pointsToIgnore.find(&point) != pointsToIgnore.end())
        return;

    pointsToIgnore.insert(&point);

    m_points.insert(&point);

    auto recurseFn = [&] (const Point & testPoint)
    {
        if ((&testPoint != &m_startPoint) && (&testPoint != &point))
        {
            if (testPoint.getStoneColor() == m_color)
            {
                doChainCalculation(testPoint, board, pointsToIgnore);
            }
            else if (testPoint.getStoneColor() == Stone::Color::NONE)
            {
                if (m_liberties.find(&testPoint) == m_liberties.end())
                {
                    m_liberties.insert(&testPoint);
                }
            }
        }
    };

    recurseFn(board.getPointAbove(point));
    recurseFn(board.getPointBelow(point));
    recurseFn(board.getPointRight(point));
    recurseFn(board.getPointLeft(point));
}

Stone::Color Chain::color ()
{
    return m_color;
}

size_t Chain::libertyCount ()
{
    return m_liberties.size();
}

size_t Chain::size ()
{
    return m_points.size();
}

} // namespace Go

