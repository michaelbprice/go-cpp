#ifndef INCL_BOARD_HPP__
#define INCL_BOARD_HPP__

#include <array>
#include <functional>
#include <utility>

#include "Point.hpp"

namespace Go {


// Forward declarations
//
#include "Stone.fwd.hpp"
class Chain;
	
class Board final
{
 private:

    // We will create some type aliases here to ease our typing
    //
    template <typename T, size_t X, size_t Y>
    using multi_array = std::array<std::array<T, X>, Y>;

    //
    // BONUS 1: Can you make a true-multidimensional array that has a
    // similar interface to the std::array class???
    //

    static const int BOARD_SIZE = 9;
    multi_array<Point, BOARD_SIZE, BOARD_SIZE> m_points;
    std::pair<bool, std::reference_wrapper<const Point>> m_koState;

 public:
    Board ();

    std::vector<Chain> getAllEmptyChains ();
    Stone::Color getStoneColorAt (size_t x, size_t y) const;
    bool isOccupiedPoint (size_t x, size_t y);
    bool isValidMove (Stone::Color color, size_t row, size_t column) const;
    void placeStoneAt (size_t x, size_t y, std::unique_ptr<Stone> stone);
    size_t removeCapturedStones (Stone::Color colorToCapture);

    template <typename FnOnVisit>
    void visitNeighboringPoints (const Point & point, FnOnVisit && onVisitFn) const
    {
        onVisitFn(getPointAbove(point));
        onVisitFn(getPointBelow(point));
        onVisitFn(getPointLeft(point));
        onVisitFn(getPointRight(point));
    }

 private:

    Chain calculateChain (size_t row, size_t column);
    bool doesKoRuleApply (const Chain & chain) const;
    const Point & getPointAbove (const Point & point) const;
    const Point & getPointBelow (const Point & point) const;
    const Point & getPointLeft (const Point & point) const;
    const Point & getPointRight (const Point & point) const;
};

}

#endif /* end of include guard: INCL_BOARD_HPP__ */
