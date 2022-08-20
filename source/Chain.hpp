#ifndef INCL_CHAIN_HPP__
#define INCL_CHAIN_HPP__

#include <functional>
#include <unordered_map>
#include "std.fwd.hpp"
#include "Board.fwd.hpp"
#include "Point.fwd.hpp"
#include "Stone.fwd.hpp"


namespace Go {

class Chain
{
 private:
    std::unordered_map<StoneColor, ConstPointSet> m_chainAndNeighbors;
    const Point & m_startPoint;
    StoneColor m_color; // Inline assignment would need full definition!!!

 public:
    struct PointVisitedAlreadyException { };

    // Construct a chain from the actual state of a point
    Chain (const Point & startPoint, const Board & board, ConstPointSet * pointsToIgnore);

    // Construct a chain from the potential state of a point
    Chain (StoneColor stoneColor, const Point & startPoint, const Board & board, ConstPointSet * pointsToIgnore);

    ~Chain () = default;

// TODO: Figure out crshing problem with moving/emplacement
    Chain (const Chain &) = default;
//    Chain (Chain && other) = default;

    size_t borderCountOf (StoneColor color);
    StoneColor color () const;
    bool containsPoint (const Point & point) const;

     //template <typename Fn>
    void forEachPoint (const PointVisitorFn & visitorFn)
    {
        forEachSurroundingPoint(m_color, visitorFn);
    }

    //template <typename Fn>
    void forEachSurroundingPoint (StoneColor color, const PointVisitorFn & visitorFn)
    {
        for (auto & p : m_chainAndNeighbors[color])
            visitorFn(*p);
    }

    size_t libertyCount () const;
    size_t size () const;

 private:
    void doChainCalculation (const Point & point, const Board & board, ConstPointSet & pointsToIgnore);
};

} // namespace Go

#endif /* end of include guard: INCL_CHAIN_HPP__ */
