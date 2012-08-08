#ifndef INCL_BOARD_HPP__
#define INCL_BOARD_HPP__

///////////////////////////////////////////////////////////////////////////////

template <typename T, int N>
class array {};

///////////////////////////////////////////////////////////////////////////////

template <typename T, int X, int Y>
using multi_array = array<array<T, X>, Y>;

namespace Go
{
	
class Point;
class Stone;

class Board final
{
 private:
 	static const int BOARD_SIZE = 19;

 	multi_array<Point, BOARD_SIZE, BOARD_SIZE> a;

 public:

 	bool isOccupiedPoint (int x, int y);
 	bool isLibertyPoint (int x, int y);
 	void placeStoneAt (int x, int y, const Stone & stone);

};

}

#endif /* end of include guard: INCL_BOARD_HPP__ */