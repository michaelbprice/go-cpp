#ifndef __CHAIN_HPP_
#define __CHAIN_HPP_

#include <unordered_set>
#include "Point.hpp"
#include "Stone.hpp"

namespace Go {

class Point;
class Board;
//class Stone;
enum class Stone::Color : char;

class Chain
{
 private:
    ConstPointSet m_points;
    ConstPointSet m_liberties;
    Stone::Color m_color;
    const Point & m_startPoint;

 public:
    Chain (const Point & startPoint, const Board & board, ConstPointSet * pointsToIgnore);
    Chain (Stone::Color stoneColor, const Point & startPoint, const Board & board, ConstPointSet * pointsToIgnore);

    Stone::Color color ();
    size_t libertyCount ();
    size_t size ();

    template <typename Fn>
    void foreach (Fn && fn)
    {
        for (auto & p : m_points)
            fn(*p);
    }

 private:
    void doChainCalculation (const Point & point, const Board & board, ConstPointSet & pointsToIgnore);
};

} // namespace Go

#endif // __CHAIN_HPP_
