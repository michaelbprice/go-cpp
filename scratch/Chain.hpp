#ifndef __CHAIN_HPP_
#define __CHAIN_HPP_

#include <unordered_set>
#include <unordered_map>
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
    std::unordered_map<Stone::Color, ConstPointSet> m_chainAndBorders;
    Stone::Color m_color;
    const Point & m_startPoint;

 public:
    Chain (const Point & startPoint, const Board & board, ConstPointSet * pointsToIgnore);
    Chain (Stone::Color stoneColor, const Point & startPoint, const Board & board, ConstPointSet * pointsToIgnore);

// TODO: Figure out crshing problem with moving/emplacement
    Chain (const Chain &) = default;
//    Chain (Chain && other) = default;
//    ~Chain ();

    size_t borderCountOf (Stone::Color color);
    Stone::Color color ();
    size_t libertyCount ();
    size_t size ();

    template <typename Fn>
    void foreach (Fn && fn)
    {
        for (auto & p : m_chainAndBorders[m_color])
            fn(*p);
    }

 private:
    void doChainCalculation (const Point & point, const Board & board, ConstPointSet & pointsToIgnore);
};

} // namespace Go

#endif // __CHAIN_HPP_
