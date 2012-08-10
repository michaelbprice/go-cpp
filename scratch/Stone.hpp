#ifndef INCL_STONE_HPP__
#define INCL_STONE_HPP__

#include <vector>

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////

namespace Go
{
	
class Stone final
{
 public:
    static const size_t kDefaultBlackCount = 3;
    static const size_t kDefaultWhiteCount = 2;

 	enum class Color : char
 	{
                NONE,
 		BLACK,
 		WHITE
 	};

 private:
 	Color m_color;

 public:
 	Stone (Color color) : m_color(color) { }
 	~Stone () = default;

 	Stone(const Stone&) = delete;
 	Stone & operator= (const Stone&) = delete;

 	Stone(Stone && other) = default;
 	Stone & operator= (Stone && other) = default;

    Stone::Color getColor ();
};

using Stones = std::vector<std::unique_ptr<Stone>>;

Stone::Color getOpposingColor (Stone::Color color);


}

#endif /* end of include guard: INCL_STONE_HPP__ */
