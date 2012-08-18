#ifndef INCL_STONE_HPP__
#define INCL_STONE_HPP__

#include <vector>
#include <unordered_map>

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////

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
    StoneColor m_color;

 public:
    Stone (StoneColor color) : m_color(color) { }
    ~Stone () = default;

    Stone(const Stone&) = delete;
    Stone & operator= (const Stone&) = delete;

    Stone(Stone && other) = default;
    Stone & operator= (Stone && other) = default;

    StoneColor getColor ();
};

using Stones = std::vector<std::unique_ptr<Stone>>;

}

/*
namespace std
{
  template <> struct hash<Go::StoneColor>
  {
    size_t operator() (const Go::StoneColor & c) const
    {
      return hash<char>()(static_cast<char>(c));
    }
  };
}
*/

#endif /* end of include guard: INCL_STONE_HPP__ */
