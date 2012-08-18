#ifndef INCL_POINT_HPP__
#define INCL_POINT_HPP__

#include <memory>
#include <unordered_set>
#include "Stone.hpp"

namespace Go {

class Point final
{
 private:
    std::unique_ptr<Stone> m_stone = nullptr;
    

 public:
    struct Coords
    {
        size_t row = 0;
        size_t column = 0;
    };

    Coords coordinates;

    StoneColor getStoneColor () const;

    void playStone (std::unique_ptr<Stone> stone);

    bool canPlayStone () const;

    void removeStone ();
};

using PointSet = std::unordered_set<Point*>;
using ConstPointSet = std::unordered_set<const Point*>;

} // namespace Go

/*
namespace std
{
  template <> struct hash<Go::Point&>
  {
    size_t operator() (const Go::Point & p) const
    {
      return hash<decltype(&p)>()(&p);
    }
  };
}

bool operator == (const Go::Point & l, const Go::Point & r)
{  return &l == &r; }
*/

#endif /* end of include guard: INCL_POINT_HPP__ */
