#ifndef INCL_BOARD_HPP__
#define INCL_BOARD_HPP__

#include "Point.hpp"
#include <array>

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////

template <typename T, size_t X, size_t Y>
using multi_array = std::array<std::array<T, X>, Y>;

namespace Go
{
	
class Stone;

class Board final
{
 private:
 	static const int BOARD_SIZE = 19;

 	multi_array<Point, BOARD_SIZE, BOARD_SIZE> a;

 public:

 	bool isOccupiedPoint (size_t x, size_t y);
 	bool isLibertyPoint (size_t x, size_t y);
 	void placeStoneAt (size_t x, size_t y, const Stone & stone);

};

}

#endif /* end of include guard: INCL_BOARD_HPP__ */
