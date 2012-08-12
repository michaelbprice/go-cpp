#ifndef INCL_STONE_HPP__
#define INCL_STONE_HPP__

#include <vector>
#include <unordered_map>

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////

namespace Go
{
	
class Stone final
{
 public:
    static const size_t kDefaultBlackCount = 6;
    static const size_t kDefaultWhiteCount = 5;

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

namespace std
{
  template <> struct hash<Go::Stone::Color>
  {
    size_t operator() (const Go::Stone::Color & c) const
    {
      return hash<char>()(static_cast<char>(c));
    }
  };
}

#endif /* end of include guard: INCL_STONE_HPP__ */
