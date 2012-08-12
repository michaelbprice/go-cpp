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
  , m_chainAndBorders({{Stone::Color::NONE, ConstPointSet{}},
                       {Stone::Color::BLACK, ConstPointSet{}},
                       {Stone::Color::WHITE, ConstPointSet{}}})
{
    if (pointsToIgnore != nullptr)
    {
        if (pointsToIgnore->find(&startPoint) != pointsToIgnore->end())
            throw 1; // TODO: make an exception type...
    }

    ConstPointSet myPointsToIgnore;

    doChainCalculation(startPoint, board, myPointsToIgnore); 


std::cout << "NONE:" << m_chainAndBorders[Stone::Color::NONE].size() << std::endl;
std::cout << "BLACK:" << m_chainAndBorders[Stone::Color::BLACK].size() << std::endl;
std::cout << "WHITE:" << m_chainAndBorders[Stone::Color::WHITE].size() << std::endl;

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
    m_chainAndBorders[m_color].insert(&point);

/*
    auto testAndInsert = [&] (Stone::Color color, const Point & thePoint)
    {
    };
*/

    auto recurseFn = [&] (const Point & testPoint)
    {
        if ((&testPoint != &m_startPoint) && (&testPoint != &point))
        {
            if (testPoint.getStoneColor() == m_color)
            {
                doChainCalculation(testPoint, board, pointsToIgnore);
            }
            else// if (testPoint.getStoneColor() == Stone::Color::NONE)
            {
                if (testPoint.getStoneColor() == Stone::Color::NONE)
                {
                    if (m_liberties.find(&testPoint) == m_liberties.end())
                    {
                        m_liberties.insert(&testPoint);
                    }
                }

                ConstPointSet & set = m_chainAndBorders[testPoint.getStoneColor()];

                if (set.find(&testPoint) == set.end())
                {
                    set.insert(&testPoint);
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
    //return m_liberties.size();
    return m_chainAndBorders[Stone::Color::NONE].size();
}

size_t Chain::size ()
{
    //return m_points.size();
    return m_chainAndBorders[m_color].size();
}

} // namespace Go

