#ifndef __CHAIN_HPP_
#define __CHAIN_HPP_

#include <unordered_map>

// Forward declarations
//
#include "std.fwd.hpp"
#include "Board.fwd.hpp"
#include "Point.fwd.hpp"
#include "Stone.fwd.hpp"


namespace Go {

class Chain
{
 private:
    std::unordered_map<StoneColor, ConstPointSet> m_chainAndNeighbors;
    StoneColor m_color;
    const Point & m_startPoint;

 public:
    struct PointVisitedAlreadyException { };

    Chain (const Point & startPoint, const Board & board, ConstPointSet * pointsToIgnore);
    Chain (StoneColor stoneColor, const Point & startPoint, const Board & board, ConstPointSet * pointsToIgnore);

// TODO: Figure out crshing problem with moving/emplacement
    Chain (const Chain &) = default;
//    Chain (Chain && other) = default;
//    ~Chain ();

    size_t borderCountOf (StoneColor color);
    StoneColor color () const;
    bool containsPoint (const Point & point) const;
    size_t libertyCount () const;
    size_t size () const;

    template <typename Fn>
    void forEachPoint (Fn && fn)
    {
        forEachSurroundingPoint(m_color, std::forward<Fn>(fn));
    }

    template <typename Fn>
    void forEachSurroundingPoint (StoneColor color, Fn && fn)
    {
        for (auto & p : m_chainAndNeighbors[color])
            fn(*p);
    }

 private:
    void doChainCalculation (const Point & point, const Board & board, ConstPointSet & pointsToIgnore);
};

} // namespace Go

#endif // __CHAIN_HPP_
