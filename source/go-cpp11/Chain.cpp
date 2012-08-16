#include <cassert>
#include <iostream>
#include <iterator>
#include <unordered_set>

#include "Chain.hpp"
#include "Board.hpp"
#include "Logger.hpp"
#include "Point.hpp"
#include "Stone.hpp"

namespace Go {

using namespace std;

Chain::Chain (Stone::Color stoneColor, const Point & startPoint, const Board & board, ConstPointSet * pointsToIgnore)
  : m_color(stoneColor)
  , m_startPoint(startPoint)
  , m_chainAndNeighbors({{Stone::Color::NONE,  ConstPointSet{}},
                         {Stone::Color::BLACK, ConstPointSet{}},
                         {Stone::Color::WHITE, ConstPointSet{}}})
{
    LOG_FUNCTION(cout, "Chain::Chain(Stone::Color,...");
 
    if (pointsToIgnore != nullptr)
    {
        if (pointsToIgnore->find(&startPoint) != pointsToIgnore->end())
            throw PointVisitedAlreadyException();
    }

    ConstPointSet myPointsToIgnore;

    doChainCalculation(startPoint, board, myPointsToIgnore); 

    if (pointsToIgnore != nullptr)
    {
        pointsToIgnore->insert(begin(myPointsToIgnore), end(myPointsToIgnore));
    }
}

Chain::Chain (const Point & startPoint, const Board & board, ConstPointSet * pointsToIgnore)
  : Chain(startPoint.getStoneColor(), startPoint, board, pointsToIgnore)
{
    LOG_FUNCTION(cout, "Chain::Chain(...)");
}

/*
Chain::~Chain ()
{
cout << "Destruction" << endl;
}
*/

void Chain::doChainCalculation (const Point & point, const Board & board, ConstPointSet & pointsToIgnore)
{
    LOG_FUNCTION(cout, "Chain::doChainCalculation");
 
    if (pointsToIgnore.find(&point) != pointsToIgnore.end())
        return;

    pointsToIgnore.insert(&point);

    m_chainAndNeighbors[m_color].insert(&point);


    board.visitNeighboringPoints(point, [&] (const Point & testPoint)
    {
        if ((&testPoint != &m_startPoint) && (&testPoint != &point))
        {
            if (testPoint.getStoneColor() == m_color)
            {
                doChainCalculation(testPoint, board, pointsToIgnore);
            }
            else
            {
                ConstPointSet & set = m_chainAndNeighbors[testPoint.getStoneColor()];

                if (set.find(&testPoint) == set.end())
                {
                    set.insert(&testPoint);
                }
            }
        }
    });
}

size_t Chain::borderCountOf (Stone::Color color)
{
    LOG_FUNCTION(cout, "Chain::borderCountOf");
 
    assert(color != m_color);

    return m_chainAndNeighbors[color].size();
}

Stone::Color Chain::color () const
{
    LOG_FUNCTION(cout, "Chain::color");
 
    return m_color;
}

size_t Chain::libertyCount () const
{
    LOG_FUNCTION(cout, "Chain::libertyCount");
 
    return m_chainAndNeighbors.at(Stone::Color::NONE).size();
}

size_t Chain::size () const
{
    LOG_FUNCTION(cout, "Chain::size");
 
    return m_chainAndNeighbors.at(m_color).size();
}

bool Chain::containsPoint (const Point & point) const
{
    LOG_FUNCTION(cout, "Chain::containsPoint");
 
    const ConstPointSet & theChain = m_chainAndNeighbors.at(m_color);
    return (theChain.find(&point) != theChain.end());
}

} // namespace Go

