#ifndef INCL_STONE_HPP__
#define INCL_STONE_HPP__

#include <iosfwd>
#include <memory>
#include <optional>
#include <vector>

namespace Go
{

enum class StoneColor : unsigned char
{
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
    StoneColor m_color;

 public:
    Stone (StoneColor color) : m_color(color) { }
    ~Stone () = default;

    Stone(const Stone&) = default;
    Stone & operator= (const Stone&) = default;

    Stone(Stone && other) = default;
    Stone & operator= (Stone && other) = default;

    StoneColor getColor () const;
};

using Stones = std::vector<Stone>;

}

std::ostream & operator<< (std::ostream & out, const std::optional<Go::Stone> & stone);


#endif /* end of include guard: INCL_STONE_HPP__ */
