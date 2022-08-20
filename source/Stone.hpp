#ifndef INCL_STONE_HPP__
#define INCL_STONE_HPP__

#include <iosfwd>
#include <memory>
#include <vector>

namespace Go
{

enum class StoneColor : unsigned char
{
    NONE,
    BLACK,
    WHITE
};

StoneColor getOpposingColor (StoneColor color);
	
class Stone final
{
 public:
    static const size_t kDefaultBlackCount = 21;
    static const size_t kDefaultWhiteCount = 20;

 private:
    StoneColor m_color = StoneColor::NONE;

 public:
    Stone (StoneColor color) : m_color(color) { }
    ~Stone () = default;

    Stone(const Stone&) = delete;
    Stone & operator= (const Stone&) = delete;

    Stone(Stone && other) = default;
    Stone & operator= (Stone && other) = default;

    StoneColor getColor () const;
};

using Stones = std::vector<std::unique_ptr<Stone>>;

}

std::ostream & operator<< (std::ostream & out, const Go::Stone & stone);


#endif /* end of include guard: INCL_STONE_HPP__ */
