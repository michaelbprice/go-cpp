#ifndef INCL_BOARD_HPP__
#define INCL_BOARD_HPP__

#include "Point.hpp"
#include "Stone.hpp"
#include <array>
#include <memory>

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////

template <typename T, size_t X, size_t Y>
using multi_array = std::array<std::array<T, X>, Y>;

namespace Go
{
	
class Board final
{
 private:
 	static const int BOARD_SIZE = 19;

 	multi_array<Point, BOARD_SIZE, BOARD_SIZE> m_points;

 public:

        Stone::Color getStoneColorAt (size_t x, size_t y) const;
 	bool isOccupiedPoint (size_t x, size_t y);
 	bool isLibertyPoint (size_t x, size_t y);
 	bool placeStoneAt (size_t x, size_t y, std::unique_ptr<Stone> stone);

};

}

#endif /* end of include guard: INCL_BOARD_HPP__ */
