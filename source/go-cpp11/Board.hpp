#ifndef INCL_BOARD_HPP__
#define INCL_BOARD_HPP__

#include <array>
#include <functional>
#include <memory>
#include <utility>
#include <vector>
#include "Point.hpp"
#include "Chain.fwd.hpp"
#include "Stone.fwd.hpp"


namespace Go {
	
class Board final
{
 public:
    static const int BOARD_SIZE = 9;

 private:

    // We will create some type aliases here to ease our typing
    //
    template <typename T, size_t X, size_t Y>
    using multi_array = std::array<std::array<T, X>, Y>;

    //
    // BONUS 1: Can you make a true-multidimensional array that has a
    // similar interface to the std::array class???
    //

    multi_array<Point, BOARD_SIZE, BOARD_SIZE> m_points;
    std::pair<bool, std::reference_wrapper<const Point>> m_koState;

 public:
    Board ();
    ~Board () = default;

    Board (const Board &) = delete;
    Board & operator= (const Board &) = delete;

    Board (Board &&) = delete;
    Board & operator= (Board &&) = delete;

    std::vector<Chain> getAllEmptyChains ();
    StoneColor getStoneColorAt (const PointCoords & coords) const;
    bool isOccupiedPoint (const PointCoords & coords);
    bool isValidMove (StoneColor color, const PointCoords & coords) const;
    void placeStoneAt (const PointCoords & coords, std::unique_ptr<Stone> stone);
    size_t removeCapturedStones (StoneColor colorToCapture);

    //template <typename FnOnVisit>
    void visitNeighboringPoints (const Point & point, const PointVisitorFn & visitorFn) const
    {
        visitorFn(getPointAbove(point));
        visitorFn(getPointBelow(point));
        visitorFn(getPointLeft(point));
        visitorFn(getPointRight(point));
    }

 private:

    Chain calculateChain (const PointCoords & coords);
    bool doesKoRuleApply (const Chain & chain) const;
    const Point & getPointAbove (const Point & point) const;
    const Point & getPointBelow (const Point & point) const;
    const Point & getPointLeft (const Point & point) const;
    const Point & getPointRight (const Point & point) const;
};

}

#endif /* end of include guard: INCL_BOARD_HPP__ */
