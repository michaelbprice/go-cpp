#ifndef INCL_BOARD_HPP__
#define INCL_BOARD_HPP__

#include "Point.hpp"
#include "Stone.hpp"
#include "Chain.hpp"
#include <array>
#include <memory>
#include <unordered_set>

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////

template <typename T, size_t X, size_t Y>
using multi_array = std::array<std::array<T, X>, Y>;

/*
template <typename T, size_t X, size_t Y>
auto begin(multi_array<T,X,Y> & a) -> decltype(a.begin().begin())
{ return a.begin().begin(); }

template <typename T, size_t X, size_t Y>
auto begin(const multi_array<T,X,Y> & a) -> decltype(a.begin().begin())
{ return a.begin().begin(); }

template <typename T, size_t X, size_t Y>
auto end(multi_array<T,X,Y> & a) -> decltype(a.end().end())
{ return a.end().end(); }

template <typename T, size_t X, size_t Y>
auto end(const multi_array<T,X,Y> & a) -> decltype(a.end().end())
{ return a.end().end(); }
*/

namespace Go
{

	
class Board final
{
 private:
    static const int BOARD_SIZE = 19;

    multi_array<Point, BOARD_SIZE, BOARD_SIZE> m_points;

 public:
    Board ();

    const Point & getPointAbove (const Point & point) const;
    const Point & getPointBelow (const Point & point) const;
    const Point & getPointLeft (const Point & point) const;
    const Point & getPointRight (const Point & point) const;
    Stone::Color getStoneColorAt (size_t x, size_t y) const;
    bool isOccupiedPoint (size_t x, size_t y);
    bool isLibertyPoint (size_t x, size_t y);
    bool placeStoneAt (size_t x, size_t y, std::unique_ptr<Stone> stone);
    size_t removeCapturedStones ();
    bool wouldBeValidMove (Stone::Color color, size_t row, size_t column) const;

    std::vector<Chain> getAllEmptyChains ();

 private:
    Chain calculateChain (size_t row, size_t column);
};

}

#endif /* end of include guard: INCL_BOARD_HPP__ */
